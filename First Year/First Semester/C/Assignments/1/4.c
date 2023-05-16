#include <stdio.h>

// Given as input a floating number of centimeters, print the corresponding number of feet (integer) and inches (floating, 1 decimal), with the inches given to an accuracy of one decimal place.
// Assume 2.54 centimeters per inch, and 12 inches per foot. 

int main(int argc, char* argv[])
{
    float centimeters;
    printf("Input a floating number of centimeters: ");
    scanf("%f", &centimeters);
    float inches = centimeters / 2.54;
    int feet = 0;
    while(inches > 12)
        feet++, inches -= 12;
    printf("The result is %d\' %.1f\"", feet, inches);
}