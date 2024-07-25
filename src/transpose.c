#include <stdio.h>
#include <stdlib.h>

#define N 1024

void transpose(double **matrix, double **result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

double** allocateMatrix(int size) {
    double** matrix = (double**) malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*) malloc(size * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    double **matrix = allocateMatrix(N);
    double **result = allocateMatrix(N);

    // Initialize the matrix with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = i + j;
        }
    }

    transpose(matrix, result, N);

    // Optionally print the transposed matrix
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         printf("%lf ", result[i][j]);
    //     }
    //     printf("\n");
    // }

    freeMatrix(matrix, N);
    freeMatrix(result, N);

    return 0;
}

