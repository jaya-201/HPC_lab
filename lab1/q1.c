#include <stdio.h>
#include <omp.h>

int main() {

    // Parallel region: multiple threads execute this block
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();      // Get thread ID
        int total_threads = omp_get_num_threads(); // Get total number of threads

        printf("Hello World from Thread %d of %d\n", thread_id, total_threads);
    }

    return 0;
}