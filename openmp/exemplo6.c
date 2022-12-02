#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define TOTAL 2000000

int main(void) {
  time_t t;
  srand((unsigned) time(&t));

  int A[TOTAL];
  int sum_parallel = 0;


  for (int i = 0; i < TOTAL; i++) {
    A[i] = (int) rand() % 50;
  }


  double start_parallel = omp_get_wtime();
  #pragma omp parallel for reduction(+:sum_parallel)  num_threads(16)
    for (int i = 0; i < TOTAL; i++) {
      // #pragma omp critical
      sum_parallel += (int) A[i];
    }
  double end_parallel = omp_get_wtime();

  
  int sum_serial = 0;
  clock_t start_serial = clock();
  for (int i = 0; i < TOTAL; i++) {
    sum_serial += (int) A[i];
  }
  clock_t end_serial = clock();
  

  printf("Parallel: %f seconds\n", end_parallel - start_parallel);
  printf("Serial: %f seconds\n", (double)(end_serial - start_serial) / CLOCKS_PER_SEC);
  printf("total parallel %d\n", sum_parallel);
  printf("total serial %d\n", sum_serial);
  printf("is equals %s\n", sum_parallel == sum_serial ? "true" : "false");

  return 0;
}