#include "market.h"
#include <cmath>

Market::Market(double p,double v,bool s)
    :rng(42),normal(0,1),price(p),vol(v),stress(s){}

double Market::next(){

    double v = stress ? vol*3 : vol;

    double shock = v * normal(rng);

    price *= std::exp(shock*0.01);

    return price;
}
