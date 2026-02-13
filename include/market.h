#pragma once
#include <random>

class Market {

    std::mt19937 rng;
    std::normal_distribution<> normal;

public:

    double price;
    double vol;
    bool stress;

    Market(double p,double v,bool s);

    double next();
};
