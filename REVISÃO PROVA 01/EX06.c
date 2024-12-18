/*Escreva um c�digo que recebe os valores de altura (A) e largura (L) de um tri�ngulo ret�ngulo e retorne o valor da diagonal (D).
Lembrando da regra de Pit�goras: D = sqrt(A�+L�)*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    double A, L, D;
    printf("Digite a altura do tri�ngulo ret�ngulo (em cm): ");
    scanf("%lf", &A);
    printf("Digite a largura do tri�ngulo ret�ngulo (em cm): ");
    scanf("%lf", &L);
    D = sqrt(pow(A, 2) + pow(L, 2));
    printf("A diagonal do tri�ngulo fornecido � de: %.2f cm", D);
    return 0;
    
}