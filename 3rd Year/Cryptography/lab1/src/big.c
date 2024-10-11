#include "big.h"

#include <stdlib.h>

BigNumber* create_number(uint32_t size)
{
    BigNumber* result = calloc(1, sizeof(BigNumber));
    result->size = size;
    result->digits = calloc(size, sizeof(int8_t));
    return result;
}

BigNumber* random_number(uint32_t size)
{
    BigNumber* result = create_number(size);
    for(register uint32_t index = 0; index < size; index++)
    {
        result->digits[index] = (int8_t)(rand() % 9) + 1;
        result->digits[index] = (int8_t)((result->digits[index] > 0) ? result->digits[index] : -result->digits[index]);
    }
    return result;
}

// This assumes first is greater than second.
void subtract_number(BigNumber* first, BigNumber* second)
{
    int8_t t = 0;
    register uint32_t index = 1;
    for(; index <= second->size; index++)
    {
        int8_t result = (int8_t)(first->digits[index] - second->digits[index] - t);
        if(result < 0)
        {
            result += 10;
            t = 1;
        }
        else
            t = 0;
        first->digits[index] = result;
    }

    for(; index < first->size && t; index++)
    {
        int8_t result = (int8_t)(first->digits[index] - t);
        if(result < 0)
        {
            result += 10;
            t = 1;
        }
        else
            t = 0;
        first->digits[index] = result;
    }

    while(first->digits[first->size - 1] == 0)
        first->size--;
}

bool equal_number(BigNumber* first, BigNumber* second)
{
    if(first->size != second->size)
        return false;

    for(register uint32_t index = first->size - 1; index; index--)
        if(first->digits[index] != second->digits[index])
            return false;

    return true;
}

bool compare_number(BigNumber* first, BigNumber* second)
{
    if(first->size > second->size)
        return true;
    if(second->size > first->size)
        return false;

    for(register uint32_t index = first->size - 1; index; index--)
        if(first->digits[index] > second->digits[index])
            return true;

    return false;
}

void print_number(BigNumber* number, FILE* output)
{
    if(number->size == 0)
        return;

    for(register uint32_t index = number->size - 1; index; index--)
        fprintf(output, "%d", number->digits[index]);
}

void free_number(BigNumber* number)
{
    free(number->digits);
    free(number);
}
