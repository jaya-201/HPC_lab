#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int N = 2000;

    double **A = malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
        A[i] = malloc(N * sizeof(double));

    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0;
        for (int j = 0; j < N; j++)
            A[i][j] = 1.0;
    }

    double start = omp_get_wtime();

    // ------------ ROW-WISE ----------------
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++)
            sum += A[i][j] * x[j];
        y[i] = sum;
    }

    double end = omp_get_wtime();
    printf("Row-wise Time = %lf sec\n", end - start);

    free(x);
    free(y);
    for (int i = 0; i < N; i++) free(A[i]);
    free(A);

    return 0;
}