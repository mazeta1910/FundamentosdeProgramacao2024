#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
  // Semente para o gerador de n�meros aleat�rios
  srand(time(NULL));

  // Gera um n�mero aleat�rio entre 0 e 1
  double numero_aleatorio = (double)rand() / RAND_MAX;

  // Ajusta o intervalo para -1 a 1
  numero_aleatorio = numero_aleatorio * 2 - 1;

  printf("N�mero aleat�rio entre -1 e 1: %f\n", numero_aleatorio);

  return 0;
}
