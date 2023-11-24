#include <stdio.h>
#include <time.h>

int main (int argc, char** argv)
{
    volatile float a = 1.0;
    volatile float b = 2.0;
    volatile float c;

    const int iter = 1000000;

    clock_t start = clock();
    for (float i = 0; i < iter; ++i)
    {
        c = a + b;
    }
    clock_t end = clock();
    double t = (double) (end - start) / CLOCKS_PER_SEC;

    printf("%f GFLOPS\n", (iter * 2) / t / (1024 * 1024 * 1024));

  return 0;
}