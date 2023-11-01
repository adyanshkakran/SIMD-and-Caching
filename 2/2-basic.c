#include <stdio.h>
#include <stdlib.h>

int** basic_multiply(int** a, int** b, int n) {
    int**c = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        c[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./basic <n>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int** a = (int**)malloc(n * sizeof(int*));
    int** b = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
        }
    }
    int** c_ba = basic_multiply(a, b, n);
    for(int i = 0; i < n; i++){
        free(a[i]);
        free(b[i]);
        free(c_ba[i]);
    }
    free(a);
    free(b);
    free(c_ba);
    return 0;
}