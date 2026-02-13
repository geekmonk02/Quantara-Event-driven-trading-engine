#include "thread_pool.h"

ThreadPool::ThreadPool(size_t n){

    n = std::max<size_t>(1,n);

    for(size_t i=0;i<n;i++){
        workers.emplace_back([this]{

            while(true){

                std::function<void()> task;

                {
                    std::unique_lock lock(m);

                    cv.wait(lock,[this]{
                        return stop || !tasks.empty();
                    });

                    if(stop && tasks.empty())
                        return;

                    task = std::move(tasks.front());
                    tasks.pop();
                }

                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task){

    {
        std::lock_guard lock(m);
        tasks.emplace(std::move(task));
    }

    cv.notify_one();
}

ThreadPool::~ThreadPool(){

    {
        std::lock_guard lock(m);
        stop=true;
    }

    cv.notify_all();

    for(auto &t: workers)
        t.join();
}
