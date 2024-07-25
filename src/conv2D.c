#include <stdio.h>
#include <stdlib.h> // Needed for malloc and free

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080
#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3

// Uncomment the following line to enable verbose output
//#define VERBOSE

// Function to initialize a matrix with pseudo-random numbers
void initMatrix(int width, int height, int **matrix) {
    unsigned int seed = 12345;  // Simple seed for pseudo-random generator
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            seed = seed * 1103515245 + 12345;
            matrix[i][j] = (seed / 65536) % 256;
        }
    }
}

// Function to perform 2D convolution with boundary checking and zero padding
void convolve(int imageHeight, int imageWidth, int **image,
              int kernelHeight, int kernelWidth, int **kernel,
              int outputHeight, int outputWidth, int **output,
              long *multiplications, long *accumulations) {
    int paddedHeight = imageHeight + kernelHeight - 1;
    int paddedWidth = imageWidth + kernelWidth - 1;
    int **paddedImage = malloc(paddedHeight * sizeof(int *));
    for (int i = 0; i < paddedHeight; i++) {
        paddedImage[i] = calloc(paddedWidth, sizeof(int)); // Allocates and zeroes out
    }

    for (int i = 0; i < imageHeight; i++) {
        for (int j = 0; j < imageWidth; j++) {
            paddedImage[i + (kernelHeight / 2)][j + (kernelWidth / 2)] = image[i][j];
        }
    }

#ifdef VERBOSE
    *multiplications = 0;
    *accumulations = 0;
#endif

    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            int sum = 0;
            for (int m = 0; m < kernelHeight; m++) {
                for (int n = 0; n < kernelWidth; n++) {
                    int x = i + m;
                    int y = j + n;
                    sum += paddedImage[x][y] * kernel[m][n];
#ifdef VERBOSE
                    (*multiplications)++;
                    if (m > 0 || n > 0) (*accumulations)++;
#endif
                }
            }
            output[i][j] = sum;
        }
    }

    for (int i = 0; i < paddedHeight; i++) {
        free(paddedImage[i]);
    }
    free(paddedImage);
}

int main() {
    int **image = malloc(IMAGE_HEIGHT * sizeof(int *));
    int **kernel = malloc(KERNEL_HEIGHT * sizeof(int *));
    int **output = malloc(IMAGE_HEIGHT * sizeof(int *));
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        image[i] = malloc(IMAGE_WIDTH * sizeof(int));
        output[i] = malloc(IMAGE_WIDTH * sizeof(int));
    }
    for (int i = 0; i < KERNEL_HEIGHT; i++) {
        kernel[i] = malloc(KERNEL_WIDTH * sizeof(int));
    }

    long multiplications = 0, accumulations = 0;

    initMatrix(IMAGE_WIDTH, IMAGE_HEIGHT, image);
    initMatrix(KERNEL_WIDTH, KERNEL_HEIGHT, kernel);

    convolve(IMAGE_HEIGHT, IMAGE_WIDTH, image, KERNEL_HEIGHT, KERNEL_WIDTH, kernel,
             IMAGE_HEIGHT, IMAGE_WIDTH, output, &multiplications, &accumulations);

#ifdef VERBOSE
    printf("Total multiplications: %ld\n", multiplications);
    printf("Total accumulations: %ld\n", accumulations);
#endif

    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        free(image[i]);
        free(output[i]);
    }
    for (int i = 0; i < KERNEL_HEIGHT; i++) {
        free(kernel[i]);
    }
    free(image);
    free(kernel);
    free(output);

    return 0;
}
