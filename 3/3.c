#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* func(int n, int** B, int* X)
{
    int *A = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n - 1; i++)
    {
        A[i] = 0;
        for (int j = 1; j < n - 1; j++)
        {
            A[i] += 0.33 * (B[i][j] * X[j]);
        }
    }
    return A;
}

int main()
{
    int n = 4000;

    int **B = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        B[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++)
            B[i][j] = rand() % 100;
    }

    int *X = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        X[i] = rand() % 100;

    int *A = func(n, B, X);

    for (int i = 0; i < n; i++)
    {
        free(B[i]);
    }
    free(A);
    free(B);
    free(X);
}
