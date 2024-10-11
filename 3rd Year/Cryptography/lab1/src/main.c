#include "big.h"
#include "gcd.h"
#include "utils.h"

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_SIZE 5000
#define SAMPLE_COUNT 100
#define MAX_NUMBER 1000

uint32_t first_number[SAMPLE_SIZE], second_number[SAMPLE_SIZE];
BigNumber* first_number_big[SAMPLE_SIZE], *second_number_big[SAMPLE_SIZE], *results_big[SAMPLE_SIZE];
uint32_t results[SAMPLE_SIZE][GCDS_COUNT - 1];
double result_secs[SAMPLE_COUNT + 1][GCDS_COUNT];

int main(int argc, char* argv[])
{
    srand((uint32_t)time(NULL));

    UNUSED(argc);
    UNUSED(argv);

    uint32_t sample = SAMPLE_COUNT;
    while(sample--)
    {
        register uint32_t index = SAMPLE_SIZE;
        while(index--)
        {
            first_number[index] = (uint32_t) rand() % MAX_NUMBER;
            second_number[index] = (uint32_t) rand() % MAX_NUMBER;

            if(first_number_big[index] != NULL)
                free_number(first_number_big[index]);
            first_number_big[index] = random_number(3);
            if(second_number_big[index] != NULL)
                free_number(second_number_big[index]);
            second_number_big[index] = random_number(2);
        }

        start_timing();
        index = SAMPLE_SIZE;
        while(index--)
            results[index][0] = binary_gcd(first_number[index], second_number[index]);
        end_timing();
        result_secs[sample][0] = get_passed_time_secs();
        result_secs[SAMPLE_COUNT][0] = (result_secs[SAMPLE_COUNT][0] < result_secs[sample][0]) ? result_secs[sample][0] : result_secs[SAMPLE_COUNT][0];

        start_timing();
        index = SAMPLE_SIZE;
        while(index--)
            results[index][1] = binary_gcd(first_number[index], second_number[index]);
        end_timing();
        result_secs[sample][1] = get_passed_time_secs();
        result_secs[SAMPLE_COUNT][1] = (result_secs[SAMPLE_COUNT][1] < result_secs[sample][1]) ? result_secs[sample][1] : result_secs[SAMPLE_COUNT][1];

        // Vibe check.
        index = SAMPLE_SIZE;
        while(index--)
            assert(results[index][0] == results[index][1]);

        start_timing();
        index = SAMPLE_SIZE;
        while(index--)
        {
            results_big[index] = big_gcd(first_number_big[index], second_number_big[index]);
            free_number(first_number_big[index]);
            first_number_big[index] = NULL;
            free_number(second_number_big[index]);
            second_number_big[index] = NULL;
        }
            
        end_timing();
        result_secs[sample][2] = get_passed_time_secs();
        result_secs[SAMPLE_COUNT][2] = (result_secs[SAMPLE_COUNT][2] < result_secs[sample][2]) ? result_secs[sample][2] : result_secs[SAMPLE_COUNT][2];
    }

    printf("Binary max secs: %fs.\n", result_secs[SAMPLE_COUNT][0]);
    printf("Euclid max secs: %fs.\n", result_secs[SAMPLE_COUNT][1]);
    printf("Big number max secs: %fs.\n", result_secs[SAMPLE_COUNT][2]);

    register uint32_t index = SAMPLE_SIZE;
    while(index--)
    {
        if(first_number_big[index] != NULL)
            free_number(first_number_big[index]);
        if(second_number_big[index] != NULL)
            free_number(second_number_big[index]);
    }

    return EXIT_SUCCESS;
}
