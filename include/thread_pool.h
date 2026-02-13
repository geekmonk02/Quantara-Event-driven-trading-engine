#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex m;
    std::condition_variable cv;
    bool stop=false;

public:

    ThreadPool(size_t n);
    void enqueue(std::function<void()> task);
    ~ThreadPool();
};
