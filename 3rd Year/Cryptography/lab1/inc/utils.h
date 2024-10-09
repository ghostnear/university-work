#pragma once

#include <time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define UNUSED(X) (void)(X)

void start_timing(void);
void end_timing(void);
clock_t get_passed_time_clocks(void);
double get_passed_time_secs(void);
