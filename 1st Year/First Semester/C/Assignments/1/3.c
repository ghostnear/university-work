#include <stdio.h>

// Write a program that computes out the largest and smallest values of 5 numbers read from the input.

int main(int argc, char* argv[])
{
    int minimum, currentNumber;
    scanf("%d", &minimum);
    for(size_t i = 0; i < 4; i++)
    {
        scanf("%d", &currentNumber);
        if(currentNumber < minimum)
            minimum = currentNumber;
    }
    printf("The minimum of the numbers you inputed is %d.", minimum);
}