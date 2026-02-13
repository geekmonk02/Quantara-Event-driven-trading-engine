#include "order_book.h"

void OrderBook::addOrder(const Order& o){

    if(o.side==Side::BUY)
        bids[o.price].push_back(o);
    else
        asks[o.price].push_back(o);
}

double OrderBook::bestBid() const {
    return bids.empty()?0:bids.begin()->first;
}

double OrderBook::bestAsk() const {
    return asks.empty()?0:asks.begin()->first;
}

double OrderBook::mid() const {
    if(bids.empty() || asks.empty()) return 0;
    return (bestBid()+bestAsk())/2;
}

std::vector<Order> OrderBook::match(int volume){

    std::vector<Order> fills;

    while(volume>0 && !bids.empty()){

        auto &q = bids.begin()->second;
        auto &o = q.front();

        int traded = std::min(o.qty,volume);

        Order filled=o;
        filled.qty=traded;

        fills.push_back(filled);

        o.qty-=traded;
        volume-=traded;

        if(o.qty==0)
            q.pop_front();

        if(q.empty())
            bids.erase(bids.begin());
    }

    return fills;
}
