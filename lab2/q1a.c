#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Thread %d: doing some work\n", id);

        // Implicit barrier here before exit of parallel block
        printf("Thread %d: passed the implicit barrier\n", id);
    }
    return 0;
}