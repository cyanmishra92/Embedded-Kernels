#include <stdio.h>
#include <stdlib.h>

#define N 1024  // Dimensions of the square matrices
#define BLOCK_SIZE 64  // Size of each tile/block

// Uncomment the following line to enable verbose output
//#define VERBOSE

// Function to allocate a matrix dynamically
double** allocateMatrix(int size) {
    double** matrix = (double**) malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*) malloc(size * sizeof(double));
    }
    return matrix;
}

// Function to initialize matrix with random values
void initMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;  // Random values between 0 and 99
        }
    }
}

// Function to multiply two matrices using matrix tiling
void multiplyMatrices(double** A, double** B, double** C, int size, long* multiplications, long* accumulations) {
    int i, j, k, ii, jj, kk;

    for (ii = 0; ii < size; ii += BLOCK_SIZE) {
        for (jj = 0; jj < size; jj += BLOCK_SIZE) {
            for (kk = 0; kk < size; kk += BLOCK_SIZE) {
                for (i = ii; i < ii + BLOCK_SIZE; i++) {
                    for (j = jj; j < jj + BLOCK_SIZE; j++) {
                        double sum = C[i][j];
                        for (k = kk; k < kk + BLOCK_SIZE; k++) {
                            sum += A[i][k] * B[k][j];
#ifdef VERBOSE
                            (*multiplications)++;
                            (*accumulations)++;
#endif
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

// Function to free dynamically allocated matrix
void freeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    double **A = allocateMatrix(N);
    double **B = allocateMatrix(N);
    double **C = allocateMatrix(N);
    long multiplications = 0, accumulations = 0;

    initMatrix(A, N);
    initMatrix(B, N);
    initMatrix(C, N);

    multiplyMatrices(A, B, C, N, &multiplications, &accumulations);

#ifdef VERBOSE
    // Optionally print the result matrix C and operation counts
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lf ", C[i][j]);
        }
        printf("\n");
    }
    printf("Total multiplications: %ld\n", multiplications);
    printf("Total accumulations: %ld\n", accumulations);
#endif

    // Free the matrices
    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(C, N);

    return 0;
}
