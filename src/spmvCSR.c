#include <stdio.h>
#include <stdlib.h>

// Matrix size definitions
#define SMALL 1
#define MEDIUM 2
#define LARGE 3

// Define matrix size level here
#ifndef MATRIX_SIZE
#define MATRIX_SIZE LARGE
#endif

#if MATRIX_SIZE == SMALL
    #define ROWS 100
    #define COLS 100
#elif MATRIX_SIZE == MEDIUM
    #define ROWS 1000
    #define COLS 1000
#elif MATRIX_SIZE == LARGE
    #define ROWS 5000
    #define COLS 5000
#else
    #define ROWS 10   // Default case or an error message
    #define COLS 10
#endif
// Can give gcc -D MATRIX_SIZE=MEDIUM at compile time to override

typedef struct {
    int *rowPtr;
    int *colIndex;
    double *values;
    int numRows;
    int numCols;
    int numNonZeros;
} CSRMatrix;

CSRMatrix *createCSRMatrix(double **denseMatrix, int rows, int cols);
void spmvCSR(CSRMatrix *mat, double *vec, double *result);
void freeCSRMatrix(CSRMatrix *mat);
double **allocateDenseMatrix(int rows, int cols);
void freeDenseMatrix(double **matrix, int rows);

int main() {
    double **denseMatrix = allocateDenseMatrix(ROWS, COLS);
    double *vector = malloc(COLS * sizeof(double));
    double *result = malloc(ROWS * sizeof(double));

    // Initialize matrix and vector with some example values
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            denseMatrix[i][j] = (i == j) ? i + 1.0 : 0.0; // Diagonal dominance
        }
    }
    for (int i = 0; i < COLS; i++) {
        vector[i] = 1.0; // Example vector
    }

    CSRMatrix *csrMatrix = createCSRMatrix(denseMatrix, ROWS, COLS);
    spmvCSR(csrMatrix, vector, result);

/*
    printf("Result of SpMV:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%lf\n", result[i]);
    }
*/
    freeCSRMatrix(csrMatrix);
    freeDenseMatrix(denseMatrix, ROWS);
    free(vector);
    free(result);

    return 0;
}

CSRMatrix *createCSRMatrix(double **denseMatrix, int rows, int cols) {
    int nonZeros = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (denseMatrix[i][j] != 0.0) {
                nonZeros++;
            }
        }
    }

    CSRMatrix *mat = malloc(sizeof(CSRMatrix));
    mat->numRows = rows;
    mat->numCols = cols;
    mat->numNonZeros = nonZeros;
    mat->rowPtr = malloc((rows + 1) * sizeof(int));
    mat->colIndex = malloc(nonZeros * sizeof(int));
    mat->values = malloc(nonZeros * sizeof(double));

    int count = 0;
    for (int i = 0; i < rows; i++) {
        mat->rowPtr[i] = count;
        for (int j = 0; j < cols; j++) {
            if (denseMatrix[i][j] != 0.0) {
                mat->values[count] = denseMatrix[i][j];
                mat->colIndex[count] = j;
                count++;
            }
        }
    }
    mat->rowPtr[rows] = count;

    return mat;
}

void spmvCSR(CSRMatrix *mat, double *vec, double *result) {
    for (int i = 0; i < mat->numRows; i++) {
        result[i] = 0.0;
        for (int j = mat->rowPtr[i]; j < mat->rowPtr[i + 1]; j++) {
            result[i] += mat->values[j] * vec[mat->colIndex[j]];
        }
    }
}

void freeCSRMatrix(CSRMatrix *mat) {
    free(mat->rowPtr);
    free(mat->colIndex);
    free(mat->values);
    free(mat);
}

double **allocateDenseMatrix(int rows, int cols) {
    double **matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
    }
    return matrix;
}

void freeDenseMatrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
