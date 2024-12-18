#include <stdlib.h>
#include "consumidor.h"

float consome(float quantiaProduto) {
  // Define a quantidade a ser consumida
  float consumo = 5; 

  // Consome o produto
  quantiaProduto -= consumo;

  // Se a quantia total for negativa, termina o programa
  if (quantiaProduto < 0) {
    exit(1);
  }

  return quantiaProduto;
}