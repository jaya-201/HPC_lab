#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp master
        {
            printf("[master] Executed ONLY by thread %d\n", id);
        }  // no barrier here

        printf("Thread %d continues without waiting\n", id);
    }
    return 0;
}