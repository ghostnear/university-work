#include <stdio.h>

// Being given the values of the diagonals of a diamond shape (romb), compute the area and perimeter of the diamond shape.

int main(int argc, char* argv[])
{
    int d1, d2;
    scanf("%d %d", &d1, &d2);
    printf("The area of the diamond shape with the specified diagonals is: %f", d1 * d2 / 2.0);
}