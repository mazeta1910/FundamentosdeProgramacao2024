#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

int main() {
  setlocale(LC_ALL, "Portuguese");
  int numero, soma_pares = 0, contador_impares = 0;
  bool par; 

  printf("Digite um n�mero inteiro positivo: ");
  scanf("%d", &numero);

  for (int i = 1; i < numero; i++) {
    if (i % 2 == 0) {
      par = true; 
      soma_pares += i;
    } else {
      par = false;
      contador_impares++;
    }

    printf("O n�mero %d � ", i);
    if (par) {
      printf("par.\n");
    } else {
      printf("�mpar.\n");
    }

    switch (i) {
      case 5:
        printf("Chegamos no n�mero 5!\n");
        break;
      case 10:
        printf("Chegamos no n�mero 10!\n");
        break;
    }
  }

  printf("Soma dos n�meros pares: %d\n", soma_pares);
  printf("Quantidade de n�meros �mpares: %d\n", contador_impares);

  return 0;
}