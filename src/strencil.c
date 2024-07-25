#include <stdio.h>
#include <stdlib.h>

#define N 100

void stencil3D(double ***input, double ***output, int size) {
    for (int i = 1; i < size - 1; i++) {
        for (int j = 1; j < size - 1; j++) {
            for (int k = 1; k < size - 1; k++) {
                output[i][j][k] = (input[i-1][j][k] + input[i+1][j][k] + 
                                   input[i][j-1][k] + input[i][j+1][k] + 
                                   input[i][j][k-1] + input[i][j][k+1]) / 6.0;
            }
        }
    }
}

double*** allocate3DMatrix(int size) {
    double*** matrix = (double***) malloc(size * sizeof(double**));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double**) malloc(size * sizeof(double*));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double*) malloc(size * sizeof(double));
        }
    }
    return matrix;
}

void free3DMatrix(double*** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    double ***input = allocate3DMatrix(N);
    double ***output = allocate3DMatrix(N);

    // Initialize the 3D matrix with some values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                input[i][j][k] = i + j + k;
            }
        }
    }

    stencil3D(input, output, N);

    free3DMatrix(input, N);
    free3DMatrix(output, N);

    return 0;
}

