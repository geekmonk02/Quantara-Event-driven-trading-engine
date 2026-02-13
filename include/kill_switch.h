#pragma once
#include <atomic>

class KillSwitch {

    std::atomic<bool> enabled{true};

public:

    bool allowed() const{
        return enabled;
    }

    void trigger(){
        enabled=false;
    }
};
