#include <stdio.h>
#include <omp.h>

int main() {

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            for (int i = 0; i < 8; i++) {

                int creator = omp_get_thread_num();
                int index = i;

                #pragma omp task firstprivate(index, creator)
                {
                    printf("Hello World | Loop Index: %d | Created by Thread: %d | Executed by Thread: %d\n",
                           index,
                           creator,
                           omp_get_thread_num());
                }
            }
        }
    }

    return 0;
}