#pragma once
#include <utility>

class MarketMaker {

    double spread;
    double gamma;

public:

    MarketMaker(double s,double g);

    std::pair<double,double>
    quotes(double mid,int inventory);
};
