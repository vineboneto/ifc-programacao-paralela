#include <omp.h>
#include <stdio.h>

/**
 * Soma de vetores
 * vetor 1[i] + vetor 2[i] = vetor3[i]
 */

#define SIZE 2048

/**
 * Desvantagem definir onde o trabalho começa e termina de cada threads
 */

int main(void)
{

  /**
   * Versão serial
   */

  float A[SIZE];
  float B[SIZE];
  float C[SIZE];

  for (int i = 0; i < SIZE; i++) {
    A[i] = 2;
    B[i] = 3;
  }

  /**
   * Versão paralela
   */

  #pragma omp parallel num_threads(8)
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    /** O tamanho para cada thread */
    int size = (int)SIZE / nt;
    int ini = id * size;
    int fim = ini + size - 1;
    for (int i = ini; i <= fim; i++) {
      C[i] = A[i] + B[i];
    }
  }

  /**
   * Volta versão serial
   */

  for (int i = 0; i < SIZE; i++) {
    printf("C[%d] = %f\n", i, C[i]);
  }
  return 0;
}