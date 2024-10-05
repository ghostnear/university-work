#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Use Eratosthenes's sieve to determine all prime numbers less than a given integer.
// Functions

void readInteger(int* inputLocation, char* message)
{
    if(message)
        printf("%s", message);

    scanf("%d", inputLocation);
}

void printPrimesUsingSieve(bool* sieve, size_t sieveSize)
{
    if(sieveSize > 1)
        printf("2 ");
    for(size_t index = 3; index <= sieveSize; index += 2)
        if(sieve[index] == true)
            printf("%zu ", index);
}

void generateSieveOfEratostenes(bool* sieve, size_t sieveSize)
{
    memset(sieve, true, sizeof(bool) * sieveSize);
    sieve[0] = sieve[1] = false;
    for(size_t index = 2 * 2; index < sieveSize; index += 2)
        sieve[index] = false;
    for(size_t index = 3; index * index < sieveSize; index += 2)
        for(size_t indexMultiple = index * index; indexMultiple < sieveSize; indexMultiple += index)
            sieve[indexMultiple] = false;
}

int main(int argc, char* argv[])
{
    int number = 0;
    readInteger(&number, "Give a number to print the smaller primes than it (should have max 6 digits): ");
    if(number >= 1000000)
    {
        printf("Number is too big!");
        return -1;
    }
    if(number < 0)
    {
        printf("Number can't be negative!");
        return -1;
    }

    bool* sieve = (bool*)(malloc((number + 1) * sizeof(bool)));
    generateSieveOfEratostenes(sieve, number + 1);
        
    printf("All of the prime numbers smaller than the given number are:\n");
    printPrimesUsingSieve(sieve, number);
    return 0;
}