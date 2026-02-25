#include <stdio.h>
#include <omp.h>

int parallel_sum(int arr[], int start, int end) {
    if (start == end)
        return arr[start];

    int mid = (start + end) / 2;
    int left = 0, right = 0;

    #pragma omp task shared(left)
    {
        printf("Thread %d processing [%d,%d]\n",
               omp_get_thread_num(), start, mid);
        left = parallel_sum(arr, start, mid);
    }

    #pragma omp task shared(right)
    {
        printf("Thread %d processing [%d,%d]\n",
               omp_get_thread_num(), mid+1, end);
        right = parallel_sum(arr, mid+1, end);
    }

    #pragma omp taskwait

    return left + right;
}

int main() {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int result = 0;

    #pragma omp parallel
    {
        #pragma omp single
        result = parallel_sum(arr, 0, 9);
    }

    printf("Sum: %d\n", result);
    return 0;
}