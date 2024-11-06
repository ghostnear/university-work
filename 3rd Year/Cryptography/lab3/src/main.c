#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int64_t gcd(int64_t a, int64_t b)
{
    while (b != 0)
    {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t labs(int64_t n)
{
    return (n < 0) ? -n : n;
}

int64_t pollards_rho(int64_t n, int64_t (*f)(int64_t, int64_t))
{
    if (n % 2 == 0) return 2;

    int64_t x = rand() % n;
    int64_t y = x;
    int64_t d = 1;

    while (d == 1)
    {
        x = f(x, n);
        y = f(f(y, n), n);
        d = gcd(labs(x - y), n);
    }

    return (d == n) ? -1 : d;
}

// (x^2 + 1) % n
int64_t default_function(int64_t x, int64_t n) { return (x * x + 1) % n; }

// Custom function goes here.
int64_t other_function(int64_t x, int64_t n) { return (x * x + x + 1) % n; }

// Function pointer.
int64_t (*custom_function)(int64_t, int64_t) = NULL;

int main(void)
{
    srand(time(NULL));

    int64_t n;
    printf("Enter a number to factorize: ");
    scanf("%ld", &n);

    // Uncomment to change custom function here.
    custom_function = other_function;

    // Use custom function if provided, otherwise use default.
    int64_t factor = pollards_rho(n, custom_function ? custom_function : default_function);

    if (factor == -1)
        printf("Failed to find a factor.\n");
    else
        printf("A non-trivial factor of %ld is %ld.\n", n, factor);

    return 0;
}
