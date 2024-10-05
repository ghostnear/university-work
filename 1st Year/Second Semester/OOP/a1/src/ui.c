#include "ui.h"

int* readArray(int* size)
{
    readInteger(size, "Size of the array = ");
    int* result = malloc(sizeof(int) * (*size));

    for(int index = 0; index < *size; index++)
    {
        printf("array[%d] = ", index);
        scanf("%d", (result + index));
    }

    return result;
}

void printMenu(void)
{
    printf("\nMake a choice:\n");
    printf("1. Generate the first n prime numbers.\n");
    printf("2. Given a vector of numbers, find the longest contiguous subsequence such that any two consecutive elements are relatively prime.\n");
    printf("3. Exit.\n");
}

void readInteger(int* where, char* message)
{
    if(message)
        printf("%s", message);
    scanf("%d", where);
}

void readCharacter(char* where, char* message)
{
    if(message)
        printf("%s", message);
    scanf("%c", where);
}

void printArray(int* what, int size)
{
    for(int index = 0; index < size; index++)
        printf("%d ", what[index]);
}
