#pragma once

#include <mutex>
#include <vector>
#include <cstdint>

struct Operation
{
    uint32_t id;
    uint32_t other;
    int32_t difference;

    static uint32_t get_next_id();

private:
    static uint32_t CURRENT_INDEX;
    static std::mutex CURRENT_INDEX_MUTEX;
};

struct ClientData
{
    int32_t balance = 0;
#ifdef GRANULAR_LOCK
    std::mutex mutex;
#endif
    std::vector<Operation> log;
};
