#include <stdio.h>
#include <omp.h>

int main() {

    int x = 10;

    #pragma omp parallel num_threads(2)
    {
        #pragma omp single
        {
            printf("Parent thread %d: x = %d\n", omp_get_thread_num(), x);

            // SHARED
            #pragma omp task shared(x)
            {
                x += 5;
                printf("Task(shared) thread %d: x = %d\n",
                       omp_get_thread_num(), x);
            }

            // PRIVATE
            #pragma omp task private(x)
            {
                x = 50;
                printf("Task(private) thread %d: x = %d\n",
                       omp_get_thread_num(), x);
            }

            // FIRSTPRIVATE
            #pragma omp task firstprivate(x)
            {
                x += 20;
                printf("Task(firstprivate) thread %d: x = %d\n",
                       omp_get_thread_num(), x);
            }

            #pragma omp taskwait
        }
    }

    printf("After tasks, Parent x = %d\n", x);

    return 0;
}