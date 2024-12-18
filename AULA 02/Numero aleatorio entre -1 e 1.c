#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
  // Semente para o gerador de números aleatórios
  srand(time(NULL));

  // Gera um número aleatório entre 0 e 1
  double numero_aleatorio = (double)rand() / RAND_MAX;

  // Ajusta o intervalo para -1 a 1
  numero_aleatorio = numero_aleatorio * 2 - 1;

  printf("Número aleatório entre -1 e 1: %f\n", numero_aleatorio);

  return 0;
}
