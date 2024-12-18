/*Escreva um c�digo que recebe os valores de altura (A) e largura (L) de um tri�ngulo ret�ngulo e retorne o valor da diagonal (D).
Lembrando da regra de Pit�goras: D = sqrt(A�+L�)*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    float A, L, D;
    printf("Digite o valor da altura do tri�ngulo: ");
    scanf("%f", &A);
    printf("Digite o valor da largura do tri�ngulo: ");
    scanf("%f", &L);
    D = sqrt(A*A + L*L);
    printf("O valor da diagonal do tri�ngulo �: %.3f", D);
    return 0;
}