#include <stdio.h>
#include <stdlib.h>

#define N 1024

void fft(double *real, double *imag, int n) {
    int i, j, k, m;
    int mmax, istep;
    double wr, wi, wpr, wpi, theta;
    double tempr, tempi;

    j = 0;
    for (i = 0; i < n; i++) {
        if (j > i) {
            tempr = real[j];
            tempi = imag[j];
            real[j] = real[i];
            imag[j] = imag[i];
            real[i] = tempr;
            imag[i] = tempi;
        }
        m = n / 2;
        while (m >= 1 && j >= m) {
            j -= m;
            m /= 2;
        }
        j += m;
    }

    mmax = 1;
    while (n > mmax) {
        istep = mmax * 2;
        theta = -6.283185307179586476925286766559 / mmax;  // -2.0 * PI / mmax
        wpr = -2.0 * (1.0 - cos(theta));  // Calculate once instead of inside loop
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m = 0; m < mmax; m++) {
            for (i = m; i < n; i += istep) {
                j = i + mmax;
                tempr = wr * real[j] - wi * imag[j];
                tempi = wr * imag[j] + wi * real[j];
                real[j] = real[i] - tempr;
                imag[j] = imag[i] - tempi;
                real[i] += tempr;
                imag[i] += tempi;
            }
            wr = (wpr * wr - wpi * wi) + wr;  // Update wr and wi without using sin/cos
            wi = (wpi * wr + wpr * wi) + wi;
        }
        mmax = istep;
    }
}

int main() {
    double *real = (double *) malloc(N * sizeof(double));
    double *imag = (double *) malloc(N * sizeof(double));

    // Initialize the input signal
    for (int i = 0; i < N; i++) {
        real[i] = i % 256;
        imag[i] = 0.0;
    }

    fft(real, imag, N);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("%lf + %lfi\n", real[i], imag[i]);
    // }

    free(real);
    free(imag);

    return 0;
}

