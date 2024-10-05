#include <stdio.h>
#include <stdlib.h>

// Write a program to read a set of integers and print the maximum and minimum value.
// No functions

int main(int argc, char* argv[])
{
    int size = 0;
    printf("Input the size of the set: ");
    scanf("%d", &size);
    if(size <= 0)
    {
        printf("Size can't be negative or null!");
        return -1;
    }
    
    int* array = (int*)(malloc(size * sizeof(int)));

    printf("Input the set of integers: ");
    for(size_t index = 0; index < size; index++)
        scanf("%d", &array[index]);

    int minimum = array[0];
    for(size_t i = 1; i < size; i++)
        if(minimum > array[i])
            minimum = array[i];
    printf("The minimum of the set is %d.\n", minimum);

    int maximum = array[0];
    for(size_t i = 1; i < size; i++)
        if(maximum < array[i])
            maximum = array[i];
    printf("The maximum of the set is %d.\n", maximum);

    return 0;
}