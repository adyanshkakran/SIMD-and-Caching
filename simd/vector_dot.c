#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>

int vector_dot(int* a, int* b, int n){
    int simd_size = 8;
    int remainder = n % simd_size;

    __m256i sum = _mm256_setzero_si256();
    for(int i = 0; i < n - remainder; i += simd_size){
        __m256i a_vec = _mm256_loadu_si256((__m256i*)&a[i]);
        __m256i b_vec = _mm256_loadu_si256((__m256i*)&b[i]);
        __m256i prod = _mm256_mullo_epi32(a_vec, b_vec);
        sum = _mm256_add_epi32(sum, prod);
    }

    int* sum_arr = (int*)&sum;
    int c = 0;
    for(int i = 0; i < simd_size; i++){
        c += sum_arr[i];
    }
    for(int i = n - remainder; i < n; i++){
        c += a[i] * b[i];
    }
    return c;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./vector <n>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }
    int time = clock();
    int simd_c = vector_dot(a, b, n);
    time = clock() - time;
    printf("Time: %d\n", time);
    free(a);
    free(b);
    return 0;
}