/*Escreva um c�digo que receba como entrada um valor inteiro e imprima um valor float*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main ()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    int numero;
    printf("Informe um n�mero inteiro: ");
    scanf("%d", &numero);
    printf("O valor float �: %f", (float)numero);
    return 0;
}