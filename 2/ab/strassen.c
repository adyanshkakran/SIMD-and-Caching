#include <stdio.h>
#include <stdlib.h>

int** matrix_add(int** a, int** b, int n, int mul) {
    int** c = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        c[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + (mul*b[i][j]);
        }
    }
    return c;
}

int*** divide_into_4(int** a, int n){
    int*** a_sub = (int***)malloc(4 * sizeof(int**));
    for (int i = 0; i < 4; i++) {
        a_sub[i] = (int**)malloc((n / 2) * sizeof(int*));
        for (int j = 0; j < n / 2; j++) {
            a_sub[i][j] = (int*)malloc((n / 2) * sizeof(int));
            for(int k = 0; k < n / 2; k++){
                if(i == 0){
                    a_sub[i][j][k] = a[j][k];
                }
                else if(i == 1){
                    a_sub[i][j][k] = a[j][k + n / 2];
                }
                else if(i == 2){
                    a_sub[i][j][k] = a[j + n / 2][k];
                }
                else{
                    a_sub[i][j][k] = a[j + n / 2][k + n / 2];
                }
            }
        }
    }
    return a_sub;
}

void free_temp(int** temp, int n){
    for(int i = 0; i < n; i++){
        free(temp[i]);
    }
    free(temp);
}

int** strassen_multiply(int** a, int** b, int n) {
    if(n == 1){
        int** c = (int**)malloc(sizeof(int*));
        c[0] = (int*)malloc(sizeof(int));
        c[0][0] = a[0][0] * b[0][0];
        return c;
    }
    int*** a_sub = divide_into_4(a, n);
    int*** b_sub = divide_into_4(b, n);
    int** c = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        c[i] = (int*)malloc(n * sizeof(int));
    }
    int*** c_sub = (int***)malloc(4 * sizeof(int**));
    int **temp, **temp2;

    temp = matrix_add(b_sub[1], b_sub[3], n / 2, -1);
    int** m1 = strassen_multiply(a_sub[0], temp, n / 2); // m3
    free_temp(temp, n / 2);

    temp = matrix_add(a_sub[0], a_sub[1], n / 2, 1);
    int** m2 = strassen_multiply(temp, b_sub[3], n / 2); // m5
    free_temp(temp, n / 2);

    temp = matrix_add(a_sub[2], a_sub[3], n / 2, 1);
    int** m3 = strassen_multiply(temp, b_sub[0], n / 2); // m2
    free_temp(temp, n / 2);

    temp = matrix_add(b_sub[2], b_sub[0], n / 2, -1);
    int** m4 = strassen_multiply(a_sub[3], temp, n / 2); // m4
    free_temp(temp, n / 2);

    temp = matrix_add(a_sub[0], a_sub[3], n / 2, 1);
    temp2 = matrix_add(b_sub[0], b_sub[3], n / 2, 1);
    int** m5 = strassen_multiply(temp, temp2, n / 2); // m1
    free_temp(temp, n / 2);
    free_temp(temp2, n / 2);

    temp = matrix_add(a_sub[1], a_sub[3], n / 2, -1);
    temp2 = matrix_add(b_sub[2], b_sub[3], n / 2, 1);
    int** m6 = strassen_multiply(temp, temp2, n / 2); // m7
    free_temp(temp, n / 2);
    free_temp(temp2, n / 2);

    temp = matrix_add(a_sub[2], a_sub[0], n / 2, -1);
    temp2 = matrix_add(b_sub[0], b_sub[1], n / 2, 1);
    int** m7 = strassen_multiply(temp, temp2, n / 2); // m6
    free_temp(temp, n / 2);
    free_temp(temp2, n / 2);


    temp = matrix_add(m5, m4, n / 2, 1);
    temp2 = matrix_add(m6, m2, n / 2, -1);
    c_sub[0] = matrix_add(temp, temp2, n / 2, 1);
    free_temp(temp, n / 2);
    free_temp(temp2, n / 2);

    c_sub[1] = matrix_add(m1, m2, n / 2, 1);
    c_sub[2] = matrix_add(m3, m4, n / 2, 1);

    temp = matrix_add(m5, m1, n / 2, 1);
    temp2 = matrix_add(m3, m7, n / 2, -1);
    c_sub[3] = matrix_add(temp, temp2, n / 2, -1);
    free_temp(temp, n / 2);
    free_temp(temp2, n / 2);

    for(int i = 0; i < n / 2; i++){
        for(int j = 0; j < n / 2; j++){
            c[i][j] = c_sub[0][i][j];
            c[i][j + n / 2] = c_sub[1][i][j];
            c[i + n / 2][j] = c_sub[2][i][j];
            c[i + n / 2][j + n / 2] = c_sub[3][i][j];
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < n / 2; j++){
            free(a_sub[i][j]);
            free(b_sub[i][j]);
            free(c_sub[i][j]);
        }
        free(a_sub[i]);
        free(b_sub[i]);
        free(c_sub[i]);
    }
    free(a_sub);
    free(b_sub);
    free(c_sub);

    for(int i = 0; i < n / 2; i++){
        free(m1[i]);
        free(m2[i]);
        free(m3[i]);
        free(m4[i]);
        free(m5[i]);
        free(m6[i]);
        free(m7[i]);
    }
    free(m1);
    free(m2);
    free(m3);
    free(m4);
    free(m5);
    free(m6);
    free(m7);

    return c;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./strassen <n>\n");
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
    int** c_st = strassen_multiply(a, b, n);
    for(int i = 0; i < n; i++){
        free(a[i]);
        free(b[i]);
        free(c_st[i]);
    }
    free(a);
    free(b);
    free(c_st);
    return 0;
}