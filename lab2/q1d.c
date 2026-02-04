#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    printf("SINGLE WITH IMPLICIT BARRIER\n");
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp single
        {
            printf("[single] Executed by thread %d\n", id);
        }   // implicit barrier here

        printf("Thread %d continues after implicit barrier\n", id);
    }

    printf("\nSINGLE WITH NOWAIT\n");
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp single nowait
        {
            printf("[single-nowait] Executed by thread %d\n", id);
        }

        // Here threads DO NOT WAIT
        printf("Thread %d didn't wait\n", id);
    }

    return 0;
}