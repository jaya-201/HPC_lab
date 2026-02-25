#include <stdio.h>
#include <omp.h>

int main() {
    int arr[10];
    int sum = 0;

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < 10; i++) {
            arr[i] = i + 1;
        }

        /* Incorrect synchronization */
        #pragma omp single
        {
            #pragma omp taskwait
            for (int i = 0; i < 10; i++)
                sum += arr[i];
        }
    }

    printf("Sum: %d\n", sum);
    return 0;
}