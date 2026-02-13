# Event-Driven Trading Engine (C++)

A high-performance event-driven trading simulator built with modern C++20 for modeling electronic markets, execution behavior, and real-time risk controls.

This project emphasizes systems engineering principles such as modular architecture, concurrency, deterministic replay, and configurable runtime behavior.

---

## Overview

The engine simulates a realistic electronic trading environment including:

- Limit order book mechanics  
- Strategy-driven order placement  
- Inventory-aware pricing  
- Latency modeling  
- Event-based execution flow  
- Real-time risk evaluation  
- Automated kill switch  

The goal is to focus on infrastructure and engine design rather than simplistic backtesting approaches.

---

## Architecture

The system follows a modular event-driven pipeline:

```
Config → Market Engine → Order Book → Strategy
            ↓
        Execution
            ↓
     Position Manager
            ↓
        Risk Engine
            ↓
        Kill Switch
```

Each module is isolated and communicates through clearly defined interfaces.

---

## Project Structure

```
event-driven-trading-engine/
│
├── include/              # Header files
│   ├── config.h
│   ├── thread_pool.h
│   ├── order.h
│   ├── order_book.h
│   ├── position.h
│   ├── market.h
│   ├── strategy.h
│   ├── risk_engine.h
│   ├── kill_switch.h
│   └── event.h
│
├── src/                  # Source files
│   ├── main.cpp
│   ├── config.cpp
│   ├── thread_pool.cpp
│   ├── order_book.cpp
│   ├── market.cpp
│   ├── strategy.cpp
│   └── risk_engine.cpp
│
├── config.json           # Runtime configuration
├── CMakeLists.txt
└── README.md
```

---

## Requirements

- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- CMake 3.16+
- nlohmann/json

### Install JSON Library

**Linux**
```bash
sudo apt install nlohmann-json3-dev
```

**Mac**
```bash
brew install nlohmann-json
```

**Windows**

Download the single header from:

https://github.com/nlohmann/json

---

## Build Instructions

```bash
git clone https://github.com/<your-username>/event-driven-trading-engine.git
cd event-driven-trading-engine

mkdir build
cd build

cmake ..
make

./simulator
```

---

## Configuration

Runtime behavior is controlled entirely through `config.json`.

Example:

```json
{
  "market": {
    "start_price": 100.0,
    "volatility": 0.02,
    "stress": false
  },
  "strategy": {
    "spread": 0.02,
    "gamma": 0.05
  },
  "risk": {
    "monte_carlo_paths": 20000,
    "var_limit": 2000.0
  },
  "latency": {
    "min_us": 5,
    "max_us": 50
  },
  "simulation": {
    "events": 50000
  }
}
```

Modify parameters without recompiling the engine.

---

## What This Engine Models

- Electronic limit order book dynamics  
- Strategy quoting behavior  
- Inventory exposure  
- Execution latency  
- Adverse price movement  
- Tail-risk scenarios  
- Automated shutdown under excessive risk  

This provides a controlled environment for experimenting with trading system behavior.

---

## Key Design Principles

- Event-driven execution (no naive time loops)
- Multithreaded risk computation
- Deterministic seeded randomness for reproducibility
- Modular header/source separation
- Config-driven runtime control
- Minimal allocations in critical paths

---

## Example Output

```
VaR=1843.21 ES=2310.44 PnL=512.87
VaR=2055.90 ES=2891.02 PnL=430.11

KILL SWITCH TRIGGERED

FINAL PnL: 418.32
Inventory: -20
```

---

## Future Improvements

- Historical market data replay  
- Pluggable strategy framework  
- Lock-free data structures  
- Performance benchmarking  
- Metrics export (CSV / Parquet)  
- Visualization dashboards  
- Distributed simulations  

---


## Contributions

Pull requests and experimentation are welcome.

This repository is intended as a systems-focused exploration of trading infrastructure design.
