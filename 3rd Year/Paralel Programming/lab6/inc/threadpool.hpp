#pragma once

#include "utils.hpp"

class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();

    void enqueue(std::function<void()> task);
    void wait();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::condition_variable wait_condition;
    bool stop;
    size_t active_tasks;

    void worker_thread();
};
