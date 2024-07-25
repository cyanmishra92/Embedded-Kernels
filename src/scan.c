#include <stdio.h>
#include <stdlib.h>

#define N 1000000

void prefixSum(double *input, double *output, int size) {
    output[0] = input[0];
    for (int i = 1; i < size; i++) {
        output[i] = output[i - 1] + input[i];
    }
}

int main() {
    double *input = (double *) malloc(N * sizeof(double));
    double *output = (double *) malloc(N * sizeof(double));

    // Initialize the input array with some values
    for (int i = 0; i < N; i++) {
        input[i] = i + 1.0;
    }

    prefixSum(input, output, N);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("%lf\n", output[i]);
    // }

    free(input);
    free(output);

    return 0;
}

