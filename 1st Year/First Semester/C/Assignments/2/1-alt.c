#include <stdio.h>
#include <stdlib.h>

// Write a program to read a set of integers and print the maximum and minimum value.
// Functions

void readInteger(int* inputLocation, char* message)
{
    if(message)
        printf("%s", message);

    scanf("%d", inputLocation);
}

void readIntegerArray(int* inputLocation, int inputSize, char* message)
{
    if(message)
        printf("%s", message);
    
    for(size_t index = 0; index < inputSize; index++)
        scanf("%d", &inputLocation[index]);
}

int getMinimum(int* array, int arraySize)
{
    if(arraySize == 1)
        return array[0];

    int previousMinimum = getMinimum(array, arraySize - 1);

    return ((previousMinimum < array[arraySize - 1]) ? previousMinimum : array[arraySize - 1]);
}

int getMaximum(int* array, int arraySize)
{
    if(arraySize == 1)
        return array[0];

    int previousMaxmimum = getMaximum(array, arraySize - 1);

    return ((previousMaxmimum > array[arraySize - 1]) ? previousMaxmimum : array[arraySize - 1]);
}

int main(int argc, char* argv[])
{
    int size = 0;
    readInteger(&size, "Input the size of the set: ");
    if(size <= 0)
    {
        printf("Size can't be negative or null!");
        return -1;
    }
    
    int* array = (int*)(malloc(size * sizeof(int)));

    readIntegerArray(array, size, "Input the set of integers: ");

    printf("The minimum of the set is %d.\n", getMinimum(array, size));

    printf("The maximum of the set is %d.\n", getMaximum(array, size));

    return 0;
}