#include <stdlib.h>
#include <time.h>
#include "produtor.h"

float produz(float probabilidade, float quantiaProduto) {
  // Gera um n�mero aleat�rio entre 0 e 1
  float random = (float)rand() / RAND_MAX;

  // Se o n�mero aleat�rio for menor que a probabilidade, produz
  if (random < probabilidade) {
    // Produz uma quantidade aleat�ria entre 1 e 10
    quantiaProduto += (rand() % 10) + 1;
  }

  return quantiaProduto;
}