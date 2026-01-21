// #include <stdio.h>
// #include <omp.h>

// int main() {
//     int id; // DELIBERATELY SHARED → RACE CONDITION

//     #pragma omp parallel
//     {
//         id = omp_get_thread_num();

//         // Heavy dummy loop to create delay
//         for (long long i = 0; i < 500000000; i++);

//         printf("Hello World from Thread %d\n", id);
//     }

//     return 0;
// }

#include <stdio.h>
#include <omp.h>

int main() {
    int id;

    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();  // Each thread gets its own copy

        // Same artificial delay
        for (long long i = 0; i < 500000000; i++);

        printf("Hello World from Thread %d\n", id);
    }

    return 0;
}
