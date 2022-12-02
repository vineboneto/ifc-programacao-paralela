#include <stdio.h>
#include <omp.h>

int main(void) {

  printf("\n Ola 1 - Fora da região paralela....\n\n");

  /** Região crítica */
  int id, nt = 0;

  /**
   * Cria um diretiva private definindo para que cada execução em thread tenha sua própria cópia
   * da variável definida
   */
  #pragma omp parallel num_threads(8)
  {
    // #pragma omp critical
    // {
    id = omp_get_thread_num();
    nt = omp_get_num_threads();
    printf("Sou a thread %d de um total de %d\n", id, nt);
    // }
  }

  printf("\n Ola 2 - Fora da região paralela....\n\n");

  return 0;
}