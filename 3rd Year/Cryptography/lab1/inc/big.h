#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint32_t size;
    int8_t* digits;
} BigNumber;

BigNumber* create_number(uint32_t);
BigNumber* random_number(uint32_t);
void subtract_number(BigNumber*, BigNumber*);
bool equal_number(BigNumber*, BigNumber*);
bool compare_number(BigNumber*, BigNumber*);
void print_number(BigNumber*, FILE*);
void free_number(BigNumber*);
