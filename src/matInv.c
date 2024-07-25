#include <stdio.h>
#include <stdlib.h>

#define N 3  // Size of the matrix (must be a square matrix)

void matrixInverse(double A[N][N], double invA[N][N]) {
    int i, j, k;
    double ratio;
    double augmented[N][2 * N];

    // Create augmented matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            augmented[i][j] = A[i][j];
        }
        for (j = N; j < 2 * N; j++) {
            if (i == (j - N))
                augmented[i][j] = 1.0;
            else
                augmented[i][j] = 0.0;
        }
    }

    // Perform Gaussian elimination
    for (i = 0; i < N; i++) {
        if (augmented[i][i] == 0.0) {
            printf("Mathematical Error!\n");
            return;
        }
        for (j = 0; j < N; j++) {
            if (i != j) {
                ratio = augmented[j][i] / augmented[i][i];
                for (k = 0; k < 2 * N; k++) {
                    augmented[j][k] -= ratio * augmented[i][k];
                }
            }
        }
    }

    // Row operation to make principal diagonal element to 1
    for (i = 0; i < N; i++) {
        for (j = N; j < 2 * N; j++) {
            augmented[i][j] /= augmented[i][i];
        }
    }

    // Extract inverse matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            invA[i][j] = augmented[i][j + N];
        }
    }
}

int main() {
    double A[N][N] = {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    double invA[N][N];

    matrixInverse(A, invA);

    // Optionally print the inverse matrix
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         printf("%lf ", invA[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}

