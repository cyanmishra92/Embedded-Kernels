#include <stdio.h>
#include <stdlib.h>

#define N 1024  // Number of data points
#define K 4     // Number of clusters
#define DIM 2   // Dimensionality of data points

double euclidean_distance(double *point1, double *point2, int dim) {
    double dist = 0.0;
    for (int i = 0; i < dim; i++) {
        double diff = point1[i] - point2[i];
        dist += diff * diff;
    }
    return dist;  // No sqrt for efficiency
}

void kmeans(double data[N][DIM], double centroids[K][DIM], int labels[N], int iterations) {
    for (int iter = 0; iter < iterations; iter++) {
        // Assign clusters
        for (int i = 0; i < N; i++) {
            double min_dist = euclidean_distance(data[i], centroids[0], DIM);
            labels[i] = 0;
            for (int j = 1; j < K; j++) {
                double dist = euclidean_distance(data[i], centroids[j], DIM);
                if (dist < min_dist) {
                    min_dist = dist;
                    labels[i] = j;
                }
            }
        }
        // Update centroids
        double new_centroids[K][DIM] = {0};
        int counts[K] = {0};
        for (int i = 0; i < N; i++) {
            for (int d = 0; d < DIM; d++) {
                new_centroids[labels[i]][d] += data[i][d];
            }
            counts[labels[i]]++;
        }
        for (int j = 0; j < K; j++) {
            for (int d = 0; d < DIM; d++) {
                centroids[j][d] = (counts[j] > 0) ? new_centroids[j][d] / counts[j] : centroids[j][d];
            }
        }
    }
}

int main() {
    double data[N][DIM];
    double centroids[K][DIM] = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
    int labels[N];

    // Initialize the data points
    for (int i = 0; i < N; i++) {
        for (int d = 0; d < DIM; d++) {
            data[i][d] = (double)(rand() % 100) / 100.0;
        }
    }

    kmeans(data, centroids, labels, 10);

    // Optionally print the result
    // for (int i = 0; i < N; i++) {
    //     printf("Data point %d is in cluster %d\n", i, labels[i]);
    // }

    return 0;
}

