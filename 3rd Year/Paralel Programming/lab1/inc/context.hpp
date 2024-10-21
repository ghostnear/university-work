#pragma once

#include "utils.hpp"

#define GRANULAR_LOCK
const auto RANDOM_SEED = 42u;
const auto CLIENTS_COUNT = 500u;
const auto TRANSACTIONS_PER_THREAD = 200000u;
const auto MAX_TRANSACTION_AMMOUNT = 100u;
const auto THREAD_COUNT = std::thread::hardware_concurrency();

void print_context_info();
