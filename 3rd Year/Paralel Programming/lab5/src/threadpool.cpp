#include "threadpool.hpp"
#include <thread>

using namespace std::chrono;

ThreadPool::ThreadPool(size_t num_threads) : stop(false)
{
    active_tasks = 0;
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
        ++active_tasks;
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
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            --active_tasks;
            if (tasks.empty() && active_tasks == 0) {
                wait_condition.notify_all();
            }
        }
    }
}

void ThreadPool::wait()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    wait_condition.wait(lock, [this] { return tasks.empty() && active_tasks == 0; });
}