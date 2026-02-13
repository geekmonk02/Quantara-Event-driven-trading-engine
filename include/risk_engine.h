#pragma once
#include "thread_pool.h"

class RiskEngine {

    ThreadPool pool;
    int paths;

public:

    struct Result{
        double var;
        double es;
    };

    RiskEngine(int p);

    Result compute(double price,
                   int inventory,
                   double vol);
};
