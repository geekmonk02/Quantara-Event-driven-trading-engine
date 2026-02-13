#include "config.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config Config::load(const std::string& file){

    std::ifstream f(file);

    if(!f)
        throw std::runtime_error("Cannot open config");

    json j;
    f >> j;

    Config c;

    c.start_price = j["market"].value("start_price",100.0);
    c.volatility = j["market"].value("volatility",0.02);
    c.stress = j["market"].value("stress",false);

    c.spread = j["strategy"].value("spread",0.02);
    c.gamma = j["strategy"].value("gamma",0.05);

    c.mc_paths = j["risk"].value("monte_carlo_paths",20000);
    c.var_limit = j["risk"].value("var_limit",2000.0);

    c.latency_min = j["latency"].value("min_us",5);
    c.latency_max = j["latency"].value("max_us",50);

    c.events = j["simulation"].value("events",50000);

    return c;
}
