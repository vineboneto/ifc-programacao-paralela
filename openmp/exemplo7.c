#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TOTAL 1000

int A[TOTAL][TOTAL];
int B[TOTAL][TOTAL];
int C[TOTAL][TOTAL];

int main(void) {
  int i, j, k;

  for (i = 0; i < TOTAL; i++) {
    for (j = 0; j < TOTAL; j++) {
      A[i][j] = 2;
      B[i][j] = 3;
    }
  }


  double start_parallel = omp_get_wtime();
  #pragma omp parallel for private(i, j, k) num_threads(16) shared(A,B,C)
    for (i = 0; i < TOTAL; i++) {
      for (j = 0; j < TOTAL; j++) {
        for (k = 0; k < TOTAL; k++) {
          C[i][j] = A[i][k] * B[k][j]; 
        }
      }
    }
  double end_parallel = omp_get_wtime();


  for (int i = 0; i < TOTAL;i++) {
    for (int j = 0; j < TOTAL; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }

  printf("Parallel: %f seconds\n", end_parallel - start_parallel);

  return 0;
}