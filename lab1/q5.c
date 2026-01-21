#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    int *A = (int*)malloc(SIZE * sizeof(int));
    if (!A) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        A[i] = rand();   // Random integers
    }

    int global_max = -1;   // Start low

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(max:global_max)
    for (int i = 0; i < SIZE; i++) {
        if (A[i] > global_max) {
            global_max = A[i];
        }
    }

    double end = omp_get_wtime();

    printf("Maximum Value: %d\n", global_max);
    printf("Parallel Reduction Time: %f seconds\n", end - start);

    free(A);
    return 0;
}