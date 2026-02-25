#include <stdio.h>
#include <omp.h>

long fib(int n) {
    if (n <= 1)
        return n;

    long x, y;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait

    return x + y;
}

int main() {
    int n = 10;
    long result;

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    printf("Fib(%d) = %ld\n", n, result);
    return 0;
}