#include <omp.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

  printf("\nOla 1 - Fora região paralela.... \n\n");
  /**
   * Diretiva para definir número de threads entre as threads que não possui um número de threads
   * já estabelecido;
   */

  // omp_set_num_threads(3);

  /**
   * Diretiva OpenMP de compilação
   * Cada thread terá esse código sedo executado;
   */
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("Sou a thread %d de um total %d \n", id, nt);
  }

  printf("\n Olá 2 - Fora da região paralela....\n\n");

  #pragma omp parallel num_threads(16)
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("Sou a thread %d de um total %d \n", id, nt);
  }

  printf("\n Olá 3 - Fora da região paralela....\n\n");

  return 0;
}