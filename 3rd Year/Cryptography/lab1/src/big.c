#include "big.h"

#include <stdlib.h>

BigNumber* create_number(uint32_t size)
{
    BigNumber* result = calloc(1, sizeof(BigNumber));
    result->digits = calloc(size, sizeof(int8_t));
    return result;
}

BigNumber* random_number(uint32_t size)
{
    BigNumber* result = create_number(size);
    for(register uint32_t index = 0; index < size - 1; index++)
    {
        result->digits[index] = (int8_t)rand() % 10;
        result->digits[index] = (int8_t)((result->digits[index] > 0) ? result->digits[index] : -result->digits[index]);
    }
    result->digits[size - 1] = 1;
    return result;
}

// This assumes first is greater than second.
void subtract_number(BigNumber* first, BigNumber* second)
{
    int8_t t = 0;
    for(register uint32_t index = 0; index < second->size; index++)
    {
        first->digits[index] -= (int8_t)(second->digits[index] + t);
        t = 0;
        if(first->digits[index] < 0)
            first->digits[index] += 10, t = 1;
    }
    if(first->digits[first->size - 1] == 0)
        first->size--;
}

bool compare_number(BigNumber* first, BigNumber* second)
{
    if(first->size > second->size)
        return true;
    if(second->size > first->size)
        return false;

    for(register uint32_t index = first->size; index > 0; index--)
        if(first->digits[index] > second->digits[index])
            return true;

    return false;
}

void free_number(BigNumber* number)
{
    free(number->digits);
    free(number);
}
