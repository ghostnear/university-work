#pragma once

#include "big.h"
#include <stdint.h>

enum GCDs
{
    BINARY = 0,
    EUCLID,
    BIG,
    GCDS_COUNT
};

uint32_t binary_gcd(uint32_t, uint32_t);
uint32_t euclid_gcd(uint32_t, uint32_t);
BigNumber* big_gcd(BigNumber*, BigNumber*);
