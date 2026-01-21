#include <stdio.h>
#include <omp.h>
void main()
{
  int num, id;
    #pragma omp parallel
    {
      num = omp_get_num_threads();
      id = omp_get_thread_num();
      printf("Hello World. thread %d of %d\n", id, num);
    }
}