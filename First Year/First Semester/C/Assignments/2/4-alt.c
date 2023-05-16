#include <stdio.h>
#include <stdlib.h>

// Write a program that, given an integer n, computes the first n values from the Fibonacci Series.
// Functions

void readInteger(int* inputLocation, char* message)
{
    if(message)
        printf("%s", message);

    scanf("%d", inputLocation);
}

void printFibonnaciSequence(int length)
{
    if(length == 1)
        printf("1");
    else if(length == 2)
        printf("1 1");
    else
    {
        int a = 1, b = 1;
        printf("1 1 ");
        while(length > 2)
        {
            printf("%d ", a + b);
            b += a;
            a = b - a;
            length--;
        }
    }
}

int main(int argc, char* argv[])
{
    int length = 0;
    readInteger(&length, "Give a number to print the ammount of numbers from Fibonnaci Series: ");
    if(length <= 0)
    {
        printf("Size can't be negative or null!");
        return -1;
    }
    printFibonnaciSequence(length);
}