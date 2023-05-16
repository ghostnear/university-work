#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ui.h"

bool isPrime(int* fromWhere, int size, int what)
{
    for(int index = 0; index < size; index++)
        if(what % fromWhere[index] == 0)
            return false;
    return true;
}

int* generateFirstPrimes(int howMany)
{
    int* result = malloc(sizeof(int) * howMany);
    result[0] = 2;

    int currentNumber = 3, index = 0;
    while(index < howMany - 1)
    {
        while(!isPrime(result, index + 1, currentNumber))
            currentNumber += 2;
        result[++index] = currentNumber;
    }

    return result;
}

int greatest_common_divider(int first, int second)
{
    if(first == 0)
        return second;
    return greatest_common_divider(second % first, first);
}

int main(void)
{
    static bool exited = false;
    static int choice, count;
    static int *result;

    while(!exited)
    {
        printMenu();
        readInteger(&choice, "\nAction > ");

        switch(choice)
        {

        case 1:
        {
            readInteger(&count, "\nn = ");
            result = generateFirstPrimes(count);

            printf("The first n (%d) primes are:\n", count);
            printArray(result, count);
            printf("\n");

            free(result);
            break;
        }

        case 2:
        {
            printf("\n");
            result = readArray(&count);

            int left = 0, right = 0, maxleft = 0, maxright = 0;

            for(int index = 1; index < count; index++)
            {
                if(greatest_common_divider(result[index], result[index - 1]) == 1)
                    right++;
                else if(maxright - maxleft <= right - left)
                {
                    maxright = right;
                    maxleft = left;
                    left = right = index;
                }
            }
            
            if(maxright - maxleft <= right - left)
            {
                maxright = right;
                maxleft = left;
            }

            printf(
                "\nThe longest sequence starts at index %d, ends at %d and has length %d.\n",
                left, right, right - left + 1
            );
            printArray(result + left, right - left + 1);
            printf("\n");

            free(result);
            break;
        }

        case 3:
            exited = true;
            break;

        default:
            printf("You are a dumbass, try again.");
            break;
        }
    }
    return 0;
}
