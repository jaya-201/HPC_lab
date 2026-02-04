#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Thread %d: Before barrier\n", id);

        #pragma omp barrier   // Manual synchronization point

        printf("Thread %d: After barrier\n", id);
    }
    return 0;
}