#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

int main() {
  setlocale(LC_ALL, "Portuguese");
  int numero, soma_pares = 0, contador_impares = 0;
  bool par; 

  printf("Digite um número inteiro positivo: ");
  scanf("%d", &numero);

  for (int i = 1; i < numero; i++) {
    if (i % 2 == 0) {
      par = true; 
      soma_pares += i;
    } else {
      par = false;
      contador_impares++;
    }

    printf("O número %d é ", i);
    if (par) {
      printf("par.\n");
    } else {
      printf("ímpar.\n");
    }

    switch (i) {
      case 5:
        printf("Chegamos no número 5!\n");
        break;
      case 10:
        printf("Chegamos no número 10!\n");
        break;
    }
  }

  printf("Soma dos números pares: %d\n", soma_pares);
  printf("Quantidade de números ímpares: %d\n", contador_impares);

  return 0;
}