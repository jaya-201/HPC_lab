#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long N = 100000000;   // Large vector
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));

    for (long i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    double sum = 0.0;
    double start, end;

    // -------- STATIC SCHEDULING ----------
    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (long i = 0; i < N; i++) {
        sum += A[i] * B[i];
    }

    end = omp_get_wtime();
    printf("Static Schedule Result = %lf, Time = %lf sec\n", sum, end - start);

    // -------- DYNAMIC SCHEDULING ----------
    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) reduction(+:sum)
    for (long i = 0; i < N; i++) {
        sum += A[i] * B[i];
    }

    end = omp_get_wtime();
    printf("Dynamic Schedule Result = %lf, Time = %lf sec\n", sum, end - start);

    free(A);
    free(B);
    return 0;
}
