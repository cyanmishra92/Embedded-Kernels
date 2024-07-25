#include <stdio.h>
#include <stdlib.h>

#define N 1024  // Length of the input signal
#define TAPS 64  // Number of filter coefficients

void fir_filter(double *input, double *output, double *coefficients, int length, int taps) {
    for (int i = 0; i < length; i++) {
        output[i] = 0.0;
        for (int j = 0; j < taps; j++) {
            if (i - j >= 0) {
                output[i] += coefficients[j] * input[i - j];
            }
        }
    }
}

int main() {
    double *input = (double *) malloc(N * sizeof(double));
    double *output = (double *) malloc(N * sizeof(double));
    double *coefficients = (double *) malloc(TAPS * sizeof(double));

    // Initialize the input signal and filter coefficients
    for (int i = 0; i < N; i++) {
        input[i] = i % 256;
    }
    for (int i = 0; i < TAPS; i++) {
        coefficients[i] = 0.1;  // Simple average filter
    }

    fir_filter(input, output, coefficients, N, TAPS);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("%lf\n", output[i]);
    // }

    free(input);
    free(output);
    free(coefficients);

    return 0;
}

