#ifndef MACROS_HPP
#define MACROS_HPP

#include <cstdio>
#include <cstdlib>

#define RUN_TEST(test_function) \
    printf("\nRunning %s:\n", #test_function); \
    /* LCOV_EXCL_LINE */ \
    if(test_function()) { \
        printf("\nTesting failed!\n\n"); \
        return EXIT_FAILURE; \
    } \
    printf("    Test successful.\n");

#endif