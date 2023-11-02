#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE (1024 * 1024 * 256) // Adjust the size as needed (e.g., 256 MB)

int main() {
    int *array = (int *)malloc(sizeof(int) * ARRAY_SIZE);
    if (array == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Initialize the array (optional)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // Measure read bandwidth
    long sum = 0;
    clock_t start_time = clock();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    clock_t end_time = clock();
    double read_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Measure write bandwidth
    start_time = clock();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i+1;
    }
    end_time = clock();
    double write_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate memory bandwidth in GB/s
    double read_bandwidth = (double)(ARRAY_SIZE * sizeof(int)) / (1024 * 1024 * 1024) / read_time;
    double write_bandwidth = (double)(ARRAY_SIZE * sizeof(int)) / (1024 * 1024 * 1024) / write_time;

    printf("Read Bandwidth: %.2f GB/s\n", read_bandwidth);
    printf("Write Bandwidth: %.2f GB/s\n", write_bandwidth);

    // Free allocated memory
    free(array);

    return 0;
}
