#include <stdio.h>
#include <stdlib.h>

// 1. Multiply 2 matrices of integers.

struct Matrix
{
    int size_x;
    int size_y;
    int** data;
};

void readInteger(int* who, char* message)
{
    if(message != NULL)
        printf("%s", message);
    scanf("%d", who);
}

void readMatrix(struct Matrix *self)
{
    printf("Input the size of the matrix:\n");
    readInteger(&self -> size_x, "Width: ");
    readInteger(&self -> size_y, "Height: ");

    printf("Input the elements:\n");
    self -> data = malloc(self -> size_y * sizeof(int));
    for(int row = 0; row < self -> size_y; row++)
    {
        self -> data[row] = malloc(self -> size_x * sizeof(int));
        for(int col = 0; col < self -> size_x; col++)
            readInteger(&self -> data[row][col], NULL);
    }
}

int getValueInMultiplication(struct Matrix* first, struct Matrix* second, int x, int y)
{
    int result = 0;

    // first -> size_x == second -> size_y
    for(int index = 0; index < first -> size_x; index++)
        result += first -> data[y][index] * second -> data[index][x];

    return result;
}

struct Matrix* multiplyMatrix(struct Matrix *first, struct Matrix *second)
{
    // The number of rows of the first matrix should be equal to the number of columns of the second matrix
    if(first -> size_x != second -> size_y)
        return NULL;

    struct Matrix *result = malloc(sizeof(struct Matrix));
    result -> size_x = second -> size_x;
    result -> size_y = first -> size_y;
    result -> data = malloc(result -> size_y * sizeof(int));
    for(int row = 0; row < result -> size_y; row++)
    {
        result -> data[row] = malloc(result -> size_x * sizeof(int));
        for(int col = 0; col < result -> size_x; col++)
            result -> data[row][col] = getValueInMultiplication(first, second, col, row);
    }
    return result;
}

void printMatrix(struct Matrix *self)
{
    if(self == NULL)
    {
        printf("Error: Empty matrix printed.\n");
        return;
    }

    for(int col = 0; col < self -> size_y; col++)
    {
        for(int row = 0; row < self -> size_x; row++)
            printf("%d ", self -> data[col][row]);
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    struct Matrix first, second, *result = NULL;
    
    readMatrix(&first);
    readMatrix(&second);

    result = multiplyMatrix(&first, &second);
    if(result == NULL)
    {
        printf("The number of rows of the first matrix should be equal to the number of columns of the second matrix!\n");
        return -1;
    }

    printf("The result of the multiplication is:\n");
    printMatrix(result);
    return 0;
}