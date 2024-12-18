#include <stdlib.h>
#include <time.h>
#include "produtor.h"

float produz(float probabilidade, float quantiaProduto) {
  // Gera um número aleatório entre 0 e 1
  float random = (float)rand() / RAND_MAX;

  // Se o número aleatório for menor que a probabilidade, produz
  if (random < probabilidade) {
    // Produz uma quantidade aleatória entre 1 e 10
    quantiaProduto += (rand() % 10) + 1;
  }

  return quantiaProduto;
}