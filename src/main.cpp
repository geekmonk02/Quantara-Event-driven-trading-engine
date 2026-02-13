#include <iostream>
#include <queue>
#include <random>

#include "config.h"
#include "order_book.h"
#include "position.h"
#include "market.h"
#include "strategy.h"
#include "risk_engine.h"
#include "kill_switch.h"
#include "event.h"

int main(){

    Config cfg = Config::load("config.json");

    OrderBook book;
    Position pos;
    Market market(
        cfg.start_price,
        cfg.volatility,
        cfg.stress);

    MarketMaker mm(
        cfg.spread,
        cfg.gamma);

    RiskEngine risk(cfg.mc_paths);
    KillSwitch ks;

    std::priority_queue<
        Event,
        std::vector<Event>,
        std::greater<>
    > events;

    for(int i=0;i<cfg.events;i+=10)
        events.push({EventType::PRICE,(uint64_t)i});

    events.push({EventType::RISK,100});

    std::mt19937 rng(42);

    std::uniform_int_distribution<>
        latency(cfg.latency_min,
                cfg.latency_max);

    std::uniform_int_distribution<>
        flow(1,20);

    while(!events.empty() && ks.allowed()){

        auto ev = events.top();
        events.pop();

        if(ev.type==EventType::PRICE){

            double p = market.next();

            auto [bid,ask] =
                mm.quotes(
                    p,
                    pos.inventory);

            book.addOrder({
                ev.ts,
                Side::BUY,
                bid,
                10});

            book.addOrder({
                ev.ts+1,
                Side::SELL,
                ask,
                10});

            auto fills =
                book.match(flow(rng));

            for(auto &f:fills)
                pos.onFill(f);

            events.push({
                EventType::RISK,
                ev.ts+latency(rng)});
        }

        else if(ev.type==EventType::RISK){

            auto r =
                risk.compute(
                    market.price,
                    pos.inventory,
                    cfg.volatility);

            std::cout<<"VaR="<<r.var
                     <<" ES="<<r.es
                     <<" PnL="<<pos.pnl(market.price)
                     <<std::endl;

            if(r.var > cfg.var_limit){
                std::cout<<"\nKILL SWITCH TRIGGERED\n";
                ks.trigger();
            }
        }
    }

    std::cout<<"\nFINAL PnL: "
             <<pos.pnl(market.price)
             <<"\nInventory: "
             <<pos.inventory
             <<std::endl;
}
