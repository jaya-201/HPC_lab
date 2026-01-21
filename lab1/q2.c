#include <stdio.h>
#include <omp.h>

int main() {
    int n;

    printf("Enter number of threads: ");
    scanf("%d", &n);

    // Basic sanity check (optional but prevents dumb mistakes)
    if (n <= 0) {
        printf("Invalid thread count.\n");
        return 1;
    }

    // Parallel region with runtime thread count
    #pragma omp parallel num_threads(n)
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();

        printf("Hello World from Thread %d of %d\n", id, total);
    }

    return 0;
}
