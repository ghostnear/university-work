#include "threadpool.hpp"

ThreadPool::ThreadPool(size_t num_threads) : stop(false)
{
    for (auto index = 0u; index < num_threads; index++)
        workers.emplace_back(&ThreadPool::worker_thread, this);
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(task);
    }
    condition.notify_one();
}

void ThreadPool::worker_thread()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this]{ return stop || !tasks.empty(); });
            if (stop && tasks.empty())
                return;
            task = tasks.front();
            tasks.pop();
        }
        task();
    }
}