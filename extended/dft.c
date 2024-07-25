#include <stdio.h>
#include <stdlib.h>

#define N 1024  // Length of the input signal

void dft(double *input, double *real_output, double *imag_output, int length) {
    for (int k = 0; k < length; k++) {
        real_output[k] = 0.0;
        imag_output[k] = 0.0;
        for (int n = 0; n < length; n++) {
            double angle = 6.283185307179586476925286766559 * k * n / length;  // 2.0 * PI * k * n / length
            real_output[k] += input[n] * cos(angle);
            imag_output[k] -= input[n] * sin(angle);
        }
    }
}

// Implementing basic cosine and sine functions without using math.h
double cos(double x) {
    double res = 1, term = 1;
    for (int i = 1; i <= 10; i++) {
        term *= -x * x / (2 * i * (2 * i - 1));
        res += term;
    }
    return res;
}

double sin(double x) {
    double res = x, term = x;
    for (int i = 1; i <= 10; i++) {
        term *= -x * x / (2 * i * (2 * i + 1));
        res += term;
    }
    return res;
}

int main() {
    double *input = (double *) malloc(N * sizeof(double));
    double *real_output = (double *) malloc(N * sizeof(double));
    double *imag_output = (double *) malloc(N * sizeof(double));

    // Initialize the input signal
    for (int i = 0; i < N; i++) {
        input[i] = i % 256;
    }

    dft(input, real_output, imag_output, N);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("%lf + %lfi\n", real_output[i], imag_output[i]);
    // }

    free(input);
    free(real_output);
    free(imag_output);

    return 0;
}

