cmake_minimum_required(VERSION 3.16)
project(HFTSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)

include_directories(include)

add_executable(simulator
    src/main.cpp
    src/config.cpp
    src/thread_pool.cpp
    src/order_book.cpp
    src/market.cpp
    src/strategy.cpp
    src/risk_engine.cpp
)

target_link_libraries(simulator
    nlohmann_json::nlohmann_json
)
