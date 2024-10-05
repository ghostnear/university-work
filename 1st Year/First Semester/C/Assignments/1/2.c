#include <stdio.h>

// Read two integers and compute their sum, average and sum of the squares of the numbers.

int main(int argc, char* argv[])
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf(
        "The sum of the numbers is %d, their average is %lf and the sum of their squares is %d.",
        a + b,
        (a + b) / 2.0,
        a * a + b * b
    );
}