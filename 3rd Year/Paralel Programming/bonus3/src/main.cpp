#include "threadpool.hpp"

#include <sstream>
#include <chrono>
using namespace std::chrono;

void example_task(int number)
{
    std::stringstream message;
    message << "Processing task " << number << " in thread " << std::this_thread::get_id() << std::endl;
    std::cout << message.str();
    std::this_thread::sleep_for(5ms);
}

int main()
{
    ThreadPool pool(std::thread::hardware_concurrency());

    for (auto index = 0u; index < std::thread::hardware_concurrency() * 2; index++)
        pool.enqueue([index] { example_task(index); });

    return 0;
}
