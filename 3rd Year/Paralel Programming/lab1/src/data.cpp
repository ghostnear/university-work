#include "data.hpp"

uint32_t Operation::CURRENT_INDEX = 0;
std::mutex Operation::CURRENT_INDEX_MUTEX = std::mutex();

uint32_t Operation::get_next_id()
{
    Operation::CURRENT_INDEX_MUTEX.lock();
    Operation::CURRENT_INDEX++;
    uint32_t result = Operation::CURRENT_INDEX - 1;
    Operation::CURRENT_INDEX_MUTEX.unlock();
    return result;
}