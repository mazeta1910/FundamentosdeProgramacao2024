/*Escreva um código que recebe os valores de altura (A) e largura (L) de um triângulo retângulo e retorne o valor da diagonal (D).
Lembrando da regra de Pitágoras: D = sqrt(A²+L²)*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    float A, L, D;
    printf("Digite o valor da altura do triângulo: ");
    scanf("%f", &A);
    printf("Digite o valor da largura do triângulo: ");
    scanf("%f", &L);
    D = sqrt(A*A + L*L);
    printf("O valor da diagonal do triângulo é: %.3f", D);
    return 0;
}