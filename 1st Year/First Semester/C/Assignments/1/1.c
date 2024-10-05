#include <stdio.h>

#define M_PI (float)(3.14159)

// Write a program to read a number of units of length (a float) and print out the area of a circle with that radius.
// Assume that the value of pi is 3.14159.
// Afterthat, change the type to double and compare the results.

int main(int argc, char* argv[])
{
    float radius;
    scanf("%f", &radius);
    double dradius = radius;
    printf("The area of a circle with the specified radius is: %f units.\n", radius * radius * M_PI);
    printf("The area of a circle with the specified radius is: %lf units but using double.", dradius * dradius * M_PI);
}