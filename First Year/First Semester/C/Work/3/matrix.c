#include <stdio.h>
#include <stdlib.h>

int** a, n;

void readMatrix(int* a[], int size)
{
    printf("Input the matrix (separated by spaces):\n");
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            scanf("%d", &a[i][j]);
}

int maxValInMatrix(int* a[], int size)
{
    int max = a[0][0];
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            max = (max < a[i][j]) ? a[i][j] : max;
    return max;
}

int main(int argc, char* argv[])
{
    printf("Input the size of the matrix (max 10): ");
    scanf("%d", &n);
    a = malloc(n * n * sizeof(int));
    readMatrix(a, n);
    printf("The maximum value is: %d.", maxValInMatrix(a, n));
    return 0;
}