#pragma once
#include <cstdint>

enum class EventType {
    PRICE,
    RISK
};

struct Event{

    EventType type;
    uint64_t ts;

    bool operator>(const Event& e) const{
        return ts>e.ts;
    }
};
