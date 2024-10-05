#include <stdio.h>

// Knowing that we have coins of 1, 2 and 5 units, determine the minimum number of coins to pay a given amount. 

int main(int argc, char* argv[])
{
    int ammount;
    scanf("%d", &ammount);
    printf("Minimum number of coins to pay is: %d.", ammount / 5 + (ammount % 5) / 2 + (ammount % 5) % 2);
}