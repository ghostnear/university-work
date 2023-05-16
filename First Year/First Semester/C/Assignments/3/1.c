#include <stdio.h>
#include <stdlib.h>

// 3. Write a program that reverses a string entered by the user.

char* readString(char* message)
{
    // Maximum of 100 chars.
    char* newArray = malloc(sizeof(char) * 100);

    printf("%s", message);
    scanf("%s", newArray);

    return newArray;
}

size_t lengthOfString(char* string)
{
    size_t r = 0;
    while(*(string + (r++)) != 0);
    return r - 1;
}

void swapChars(char* string, size_t indexLeft, size_t indexRight)
{
    char aux = *(string + indexLeft);
    *(string + indexLeft) = *(string + indexRight);
    *(string + indexRight) = aux;
}

void reverseString(char* string)
{
    size_t stringSize = lengthOfString(string);
    for(size_t index = 0; 2 * index < stringSize; index++)
        swapChars(string, index, stringSize - index - 1);
}

void printString(char* string)
{
    printf("The reversed string is: %s\n", string);
}

void freeString(char* string)
{
    free(string);
}

int main(int argc, char* argv[])
{
    char* str = readString("Input the string to be reversed (100 ch. max): ");
    reverseString(str);
    printString(str);
    freeString(str);
    return 0;
}