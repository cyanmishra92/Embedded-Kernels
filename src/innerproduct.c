#include <stdio.h>
#include <stdlib.h>

#define N 1000000

double dotProduct(double *a, double *b, int size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

int main() {
    double *a = (double *) malloc(N * sizeof(double));
    double *b = (double *) malloc(N * sizeof(double));

    // Initialize the vectors with some values
    for (int i = 0; i < N; i++) {
        a[i] = i + 1.0;
        b[i] = (i + 1.0) / 2.0;
    }

    double result = dotProduct(a, b, N);

    printf("Dot Product: %lf\n", result);

    free(a);
    free(b);

    return 0;
}

