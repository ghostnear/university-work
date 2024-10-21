#include "context.hpp"

void print_context_info()
{
    std::cout << "Context info:\n";
    std::cout << "\tUsing " << THREAD_COUNT << " worker threads.\n";
    std::cout << "\tThe simulated bank has " << CLIENTS_COUNT << " clients.\n";
    std::cout << "\tThere will be " << TRANSACTIONS_PER_THREAD << " transactions done per thread with a maximum value of ";
    std::cout << MAX_TRANSACTION_AMMOUNT << ".\n";
    std::cout << "\tThe random seed used is " << RANDOM_SEED << ".\n";
#ifdef GRANULAR_LOCK
    std::cout << "\tUsing granular lock (i.e there is a mutex for each element instead of one for all).\n";
#endif
}
