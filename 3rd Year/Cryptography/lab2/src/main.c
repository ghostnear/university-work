#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int is_generator(int n, int generator)
{
    // gcd is not 1, can't be generator
    return (gcd(n, generator) == 1);
}

void print_generators(int n)
{
    printf("Generators of Z%d: ", n);
    for (int generator = 1; generator < n; generator++)
        if (is_generator(n, generator) == 1)
            printf("%d ", generator);
    printf("\n");
}

int main(void)
{
    int n;
    printf("Enter a natural number (n >= 2): ");
    scanf("%d", &n);
    if (n < 2) {
        printf("The value of n should be at least 2.\n");
        return 1;
    }
    print_generators(n);
    return 0;
}
