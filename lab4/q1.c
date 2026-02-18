#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 600
#define STEP_SIZE 100

int main() {
    int arr[SIZE];
    int sum = 0;

    // Initialize array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 1;   // simple predictable result: sum should be 600
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < SIZE; i += STEP_SIZE) {

                int start = i;
                int end = i + STEP_SIZE;
                if (end > SIZE) end = SIZE;

                printf("Generator Thread %d created task for range [%d - %d)\n",
                       omp_get_thread_num(), start, end);

                #pragma omp task firstprivate(start, end)
                {
                    int psum = 0;

                    printf("  Task executing on Thread %d for range [%d - %d)\n",
                           omp_get_thread_num(), start, end);

                    for (int j = start; j < end; j++)
                        psum += arr[j];

                    #pragma omp critical
                    {
                        sum += psum;
                    }
                }
            }
        }
    }

    printf("\nFinal Sum = %d\n", sum);
    return 0;
}