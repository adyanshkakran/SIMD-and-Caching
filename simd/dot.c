#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dot(int* a, int* b, int n){
    int c = 0;
    for(int i = 0; i < n; i++){
        c += a[i] * b[i];
    }
    return c;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./dot <n>\n");
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
    int c = dot(a, b, n);
    time = clock() - time;
    printf("Time: %d\n", time);
    free(a);
    free(b);
    return 0;
}