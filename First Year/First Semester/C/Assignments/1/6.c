#include <stdio.h>

// Given the natural number h and m, that represent the current time expressed in hours and minutes, compute the time after x hours and y minutes.

int main(int argc, char* argv[])
{
    int h, m, x, y;
    scanf("%d:%d", &h, &m);
    scanf("%d:%d", &x, &y);
    printf(
        "The time is: %d:%d",
        (h + x + (m + y) / 60) % 24,
        (m + y) % 60
    );
}