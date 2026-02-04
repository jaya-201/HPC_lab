#include <stdio.h>
#include <omp.h>

int counter = 0;
#pragma omp threadprivate(counter)

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        counter = id * 10;
        printf("Region 1: Thread %d counter = %d\n", id, counter);
    }

    // New parallel region -> counter retains values (persistant)
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Region 2: Thread %d counter = %d\n", id, counter);
    }

    return 0;
}