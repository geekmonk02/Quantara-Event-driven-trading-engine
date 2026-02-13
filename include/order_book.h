#pragma once
#include <map>
#include <deque>
#include <vector>
#include "order.h"

class OrderBook {

    std::map<double,std::deque<Order>,std::greater<>> bids;
    std::map<double,std::deque<Order>> asks;

public:

    void addOrder(const Order& o);
    double bestBid() const;
    double bestAsk() const;
    double mid() const;

    std::vector<Order> match(int volume);
};
