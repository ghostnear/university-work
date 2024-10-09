#include "utils.h"

// This is not thread safe, do not try at home.
static clock_t start_time = -1;
static clock_t last_time = 0;

void start_timing(void)
{
    start_time = clock();
}

void end_timing(void)
{
    clock_t current_time = clock();
    last_time = current_time - start_time;
    start_time = -1;
}

clock_t get_passed_time_clocks(void)
{
    return last_time;
}

double get_passed_time_secs(void)
{
    return (double)last_time / CLOCKS_PER_SEC;
}
