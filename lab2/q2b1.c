#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 10000000;
    long long sum = 0;

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        #pragma omp critical
        sum += i;
    }

    double end = omp_get_wtime();

    printf("Parallel Sum with CRITICAL = %lld\n", sum);
    printf("Time = %f seconds\n", end - start);

    return 0;
}