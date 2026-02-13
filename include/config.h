#pragma once
#include <string>

struct Config {

    double start_price;
    double volatility;
    bool stress;

    double spread;
    double gamma;

    int mc_paths;
    double var_limit;

    int latency_min;
    int latency_max;

    int events;

    static Config load(const std::string& file);
};
