#include "context.hpp"
#include "data.hpp"

#include <chrono>
#include <cstdlib>
using namespace std::chrono;
#include <random>
#include <barrier>

std::barrier start_barrier = std::barrier(THREAD_COUNT);
#ifndef GRANULAR_LOCK
std::mutex data_mutex;
#endif

void simulate_operations(uint32_t thread_index, uint32_t operation_count, std::vector<ClientData>& data)
{
    start_barrier.arrive_and_wait();

    // C++ random shenanigans.
    using random_engine = std::mt19937;  
    random_engine random(RANDOM_SEED * thread_index * thread_index);
    std::uniform_int_distribution<uint32_t> client_distribution(0, CLIENTS_COUNT - 1);
    std::uniform_int_distribution<uint32_t> cash_distribution(1, MAX_TRANSACTION_AMMOUNT);
    #define RANDOM_CLIENT (client_distribution(random))
    #define RANDOM_MONEY  (cash_distribution(random))

    for(auto index = 0u; index < operation_count; index++)
    {
        uint32_t sender_index = RANDOM_CLIENT;
        uint32_t reciever_index = RANDOM_CLIENT;
        while(reciever_index == sender_index) reciever_index = RANDOM_CLIENT;
        int32_t transaction_value = RANDOM_MONEY;
        uint32_t transaction_id = Operation::get_next_id();
        if(sender_index > reciever_index)
        {
            std::swap(sender_index, reciever_index);
            transaction_value = -transaction_value;
        }

#ifndef GRANULAR_LOCK
        data_mutex.lock();
#else
        data[sender_index].mutex.lock();
#endif
        data[sender_index].balance -= transaction_value;
        data[sender_index].log.push_back(Operation{
            .id = transaction_id,
            .other = reciever_index,
            .difference = -transaction_value
        });

#ifdef GRANULAR_LOCK
        data[reciever_index].mutex.lock();
        data[sender_index].mutex.unlock();
#endif

        data[reciever_index].balance += transaction_value;
        data[reciever_index].log.push_back(Operation{
            .id = transaction_id,
            .other = sender_index,
            .difference = transaction_value
        });
#ifndef GRANULAR_LOCK
        data_mutex.unlock();
#else
        data[reciever_index].mutex.unlock();
#endif
    }
}

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    std::cout << "\n";

    print_context_info();

    std::vector<ClientData> data(CLIENTS_COUNT);
    std::vector<std::thread> threads(THREAD_COUNT);
    for(auto index = 0u; index < THREAD_COUNT; index++)
        threads[index] = std::thread(simulate_operations, index, TRANSACTIONS_PER_THREAD, std::ref(data));
    
    auto start = high_resolution_clock::now();
    for(auto index = 0u; index < THREAD_COUNT; index++)
        threads[index].join();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    std::cout << "Simulating the transactions took " << duration << ".\n";

    // Final consistency check.
    for(auto index = 0u; index < CLIENTS_COUNT; index++)
    {
        int32_t balance = 0;
        for(auto logIndex = 0u; logIndex < data[index].log.size(); logIndex++)
        {
            const auto& logEntry = data[index].log[logIndex];
            balance += logEntry.difference;
            
            bool found = false;
            const auto& other = data[logEntry.other];
            for(auto otherIndex = 0u; otherIndex < other.log.size() && !found; otherIndex++)
                if(other.log[otherIndex].other == index && other.log[otherIndex].id == logEntry.id && other.log[otherIndex].difference == -logEntry.difference)
                    found = true;
            
            if(!found)
            {
                std::cout << "ERROR: Mismatch in logs has been found! Missing transaction.\n\n";
                return EXIT_FAILURE;
            }
        }
        
        if(balance != data[index].balance)
        {
            std::cout << "ERROR: Mismatch in logs has been found! Wrong balance at the end of the transactions.\n\n";
            return EXIT_FAILURE;
        }
    }

    std::cout << "All the transactions have been checked successfully!\n\n";
    return EXIT_SUCCESS;
}