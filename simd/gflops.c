#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 1e-6;
}

int main() {
    int matrix_size = 1000;
    
    float *a = (float *)malloc(matrix_size * matrix_size * sizeof(float));
    float *b = (float *)malloc(matrix_size * matrix_size * sizeof(float));
    float *v = (float *)malloc(matrix_size * matrix_size * sizeof(float));

    for (int i = 0; i < matrix_size * matrix_size; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    double start_time = get_time();

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                v[i * matrix_size + j] += a[i * matrix_size + k] * b[k * matrix_size + j];
            }
        }
    }

    double end_time = get_time();
    double elapsed_time = end_time - start_time;

    double num_flops = 2.0 * matrix_size * matrix_size * matrix_size;

    double gflops = num_flops / (elapsed_time * 1e9);

    printf("Matrix size: %d x %d\n", matrix_size, matrix_size);
    printf("Elapsed time: %f seconds\n", elapsed_time);
    printf("Peak GFLOPS: %f\n", gflops);

    free(a);
    free(b);
    free(v);

    return 0;
}
