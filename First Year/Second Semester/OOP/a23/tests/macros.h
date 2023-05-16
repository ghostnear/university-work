#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>

#define RUN_TEST(test_function) \
    printf("\nRunning %s:\n", #test_function); \
    if(test_function()) { \
        printf("\nTesting failed!\n\n"); \
        return EXIT_FAILURE; \
    } \
    printf("    Test successful.\n");

#endif

