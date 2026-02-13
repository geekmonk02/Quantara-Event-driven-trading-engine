#pragma once
#include <atomic>
#include "order.h"

struct Position {

    std::atomic<int> inventory{0};
    std::atomic<double> cash{0};

    void onFill(const Order& o){

        if(o.side==Side::BUY){
            inventory += o.qty;
            cash -= o.qty*o.price;
        }else{
            inventory -= o.qty;
            cash += o.qty*o.price;
        }
    }

    double pnl(double mid){
        return cash + inventory*mid;
    }
};
