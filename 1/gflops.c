#include <stdio.h>
#include <time.h>

int main (int argc, char** argv)
{
    volatile float a = 1.0;
    volatile float b = 2.0;
    volatile float c;

    const int iter = 10000000;

    clock_t start = clock();
    for (float i = 0; i < iter; ++i)
    {
        c = a + b;
    }
    clock_t end = clock();

    printf("%f GFLOPS\n", 2.0 / ((end - start) / ((double) CLOCKS_PER_SEC * iter * 2)) / (1024 * 1024 * 1024));

  return 0;
}