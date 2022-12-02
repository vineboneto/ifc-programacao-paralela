#include <omp.h>
#include <stdio.h>

/**
 * Soma de vetores
 * vetor 1[i] + vetor 2[i] = vetor3[i]
 */

#define SIZE 2048

int main(void)
{

  /**
   * Versão serial
   */

  float A[SIZE];
  float B[SIZE];
  float C[SIZE];

  for (int i = 0; i < SIZE; i++)
  {
    A[i] = 2;
    B[i] = 3;
  }

  /**
   * Versão paralela
   */

  #pragma omp parallel num_threads(8)
  {
  /**
  * Essa diretiva diz ao compilador que o trabalhador a seguinte interação deve ser dividido
  * entre as threads
  */
    #pragma omp for
      for (int i = 0; i < SIZE; i++) {
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