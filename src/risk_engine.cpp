#include "risk_engine.h"
#include <vector>
#include <random>
#include <atomic>
#include <algorithm>
#include <condition_variable>

RiskEngine::RiskEngine(int p)
    :pool(std::thread::hardware_concurrency()),
     paths(p){}

RiskEngine::Result
RiskEngine::compute(double price,
                    int inventory,
                    double vol){

    std::vector<double> losses(paths);

    int workers =
        std::max(1u,
        std::thread::hardware_concurrency());

    std::atomic<int> finished{0};
    std::mutex m;
    std::condition_variable cv;

    int chunk = paths/workers;

    for(int w=0; w<workers; w++){

        pool.enqueue([&,w]{

            std::mt19937 rng(42+w);
            std::normal_distribution<> normal(0,1);

            int start = w*chunk;
            int end =
                (w==workers-1)
                ? paths
                : start+chunk;

            for(int i=start;i<end;i++){

                double future =
                    price * std::exp(vol*normal(rng));

                double pnl =
                    inventory*(future-price);

                losses[i] = -pnl;
            }

            finished++;
            cv.notify_one();
        });
    }

    std::unique_lock lock(m);
    cv.wait(lock,[&]{
        return finished==workers;
    });

    std::sort(losses.begin(),losses.end());

    int cutoff = paths*0.99;

    double var = losses[cutoff];

    double es=0;
    for(int i=cutoff;i<paths;i++)
        es+=losses[i];

    es /= (paths-cutoff);

    return {var,es};
}
