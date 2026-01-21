#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    double *A = (double*)malloc(SIZE * sizeof(double));
    double *B = (double*)malloc(SIZE * sizeof(double));
    double *C = (double*)malloc(SIZE * sizeof(double));

    for (int i = 0; i < SIZE; i++) {
        A[i] = i * 1.0;
        B[i] = (SIZE - i) * 1.0;
    }

    double start_seq = omp_get_wtime();

    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }
    //sequential : Runs on a single core
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    double start_par = omp_get_wtime();
    //parallel : Runs on multiple cores
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    printf("Sequential Time: %f seconds\n", time_seq);
    printf("Parallel   Time: %f seconds\n", time_par);

    if (time_par > 0)
        printf("Speedup: %.2fx\n", time_seq / time_par);

    free(A);
    free(B);
    free(C);
    return 0;
}
