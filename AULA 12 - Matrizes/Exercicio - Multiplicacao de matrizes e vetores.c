/*Exerc�cio - Multiplica��o de matrizes e vetores
A multiplica��o de matrizes e vetores � fundamental em diversas �reas, como a computa��o gr�fica,
simula��o num�rica. Considere o exemplo*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

int main (){
  int matriz1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int matriz2[3][1] = {{1}, {2}, {3}};
  int resultado[3][1];

  // Multiplica��o das matrizes
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 1; j++) {
      resultado[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        resultado[i][j] += matriz1[i][k] * matriz2[k][j];
      }
    }
  }

  // Impress�o da matriz resultante
  printf("Matriz Resultante:\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 1; j++) {
      printf("%d\n", resultado[i][j]);
    }
  }

  return 0;
}