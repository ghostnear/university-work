#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Use Eratosthenes's sieve to determine all prime numbers less than a given integer.
// No functions

int main(int argc, char* argv[])
{
    int number = 0;
    printf("Give a number to print the smaller primes than it (should have max 6 digits): ");
    scanf("%d", &number);
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
    memset(sieve, true, sizeof(bool) * (number + 1));
    sieve[0] = sieve[1] = false;
    for(size_t index = 2 * 2; index <= number; index += 2)
        sieve[index] = false;
    for(size_t index = 3; index * index <= number; index += 2)
        for(size_t indexMultiple = index * index; indexMultiple <= number; indexMultiple += index)
            sieve[indexMultiple] = false;
        
    printf("All of the prime numbers smaller than the given number are:\n");
    if(number > 1)
        printf("2 ");
    for(size_t index = 3; index <= number; index += 2)
        if(sieve[index] == true)
            printf("%zu ", index);
    return 0;
}