#include <stdio.h>
#include <stdlib.h>

// Write a program that, given an integer n, computes the first n values from the Fibonacci Series.
// No functions

int main(int argc, char* argv[])
{
    int length = 0;
    printf("Give a number to print the ammount of numbers from Fibonnaci Series: ");
    scanf("%d", &length);
    if(length <= 0)
    {
        printf("Size can't be negative or null!");
        return -1;
    }

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