#include "strategy.h"

MarketMaker::MarketMaker(double s,double g)
    :spread(s),gamma(g){}

std::pair<double,double>
MarketMaker::quotes(double mid,int inventory){

    double reservation =
        mid - inventory*gamma*0.02;

    return {
        reservation - spread/2,
        reservation + spread/2
    };
}
