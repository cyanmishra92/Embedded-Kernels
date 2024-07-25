#include <stdio.h>
#include <stdlib.h>

#define N 500
#define ITERATIONS 1000

void jacobi(double **A, double *b, double *x, double *x_new, int size, int iterations) {
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < size; i++) {
            double sum = 0.0;
            for (int j = 0; j < size; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        for (int i = 0; i < size; i++) {
            x[i] = x_new[i];
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
    double **A = allocateMatrix(N);
    double *b = (double *) malloc(N * sizeof(double));
    double *x = (double *) malloc(N * sizeof(double));
    double *x_new = (double *) malloc(N * sizeof(double));

    // Initialize the matrix A and vector b
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i == j) ? 2.0 : 1.0;
        }
        b[i] = N + 1;
        x[i] = 0.0;
    }

    jacobi(A, b, x, x_new, N, ITERATIONS);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("%lf\n", x[i]);
    // }

    freeMatrix(A, N);
    free(b);
    free(x);
    free(x_new);

    return 0;
}

