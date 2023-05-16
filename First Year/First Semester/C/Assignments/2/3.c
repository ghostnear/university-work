#include <stdio.h>
#include <stdlib.h>

// Write a program to read an integer with max 3 digits and print the value in words.
// No functions

// Auxiliary data
char* digitsAsString[10] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};
char* tensAsString[10] = {
    "null",
    "null",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety"
};
char* underTwentyAsString[10] = {
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"
};

int main(int argc, char* argv[])
{
    int number = 0;
    printf("Input a three digit integer: ");
    scanf("%d", &number);
    if(number >= 1000 || -number >= 1000)
    {
        printf("The number is out of the specified range!");
        return -1;
    }
    printf("The number you inputed is ");
    if(number < 0)
    {
        printf("minus ");
        number = -number;
    }
    if(number == 0)
    {
        printf("zero");
        return 0;
    }
    if(number >= 100)
    {
        size_t hundredsCount = number / 100;
        number %= 100;
        printf("%s hundred ", digitsAsString[hundredsCount]);
    }
    if(number >= 20)
    {
        size_t tensCount = number / 10;
        number %= 10;
        if(number > 0)
            printf("%s %s", tensAsString[tensCount], digitsAsString[number]);
        else
            printf("%s", tensAsString[tensCount]);
    }
    else {
        if(number >= 10)
            printf("%s", underTwentyAsString[number - 10]);
        else if(number > 0)
            printf("%s", digitsAsString[number]);
    }
    return 0;
}