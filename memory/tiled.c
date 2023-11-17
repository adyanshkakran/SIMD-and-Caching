#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 16

int** tiled_multiply(int** a, int** b, int n) {
    int** c = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        c[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
        }
    }
    
    for(int i = 0; i < n; i += TILE_SIZE){
        for(int j = 0; j < n; j += TILE_SIZE){
            for(int k = 0; k < n; k += TILE_SIZE){
                for(int ii = i; ii < i + TILE_SIZE && ii < n; ii++){
                    for(int jj = j; jj < j + TILE_SIZE && jj < n; jj++){
                        for(int kk = k; kk < k + TILE_SIZE && kk < n; kk++){
                            c[ii][jj] += a[ii][kk] * b[kk][jj];
                        }
                    }
                }
            }
        }
    }
    return c;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./tiled <n>\n");
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
    int** c = tiled_multiply(a, b, n);
    for(int i = 0; i < n; i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}