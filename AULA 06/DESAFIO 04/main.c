#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "produtor.h"
#include "consumidor.h"

int main() {
  // Inicializa a semente do gerador de números aleatórios
  srand(time(NULL));

  // Define a quantidade inicial do produto
  float quantiaProduto = QUANTIA_INICIAL;

  // Define a probabilidade de produção
  float probabilidade = 0.5; 

  // Loop infinito para produzir e consumir o produto
  while (1) {
    // Produz o produto
    quantiaProduto = produz(probabilidade, quantiaProduto);

    // Consome o produto
    quantiaProduto = consome(quantiaProduto);

    // Imprime a quantidade atual do produto (opcional)
    printf("Quantidade do produto: %.2f\n", quantiaProduto);
  }

  return 0;
}