/*Escreva um código que recebe os valores de altura (A) e largura (L) de um triângulo retângulo e retorne o valor da diagonal (D).
Lembrando da regra de Pitágoras: D = sqrt(A²+L²)*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    double A, L, D;
    printf("Digite a altura do triângulo retângulo (em cm): ");
    scanf("%lf", &A);
    printf("Digite a largura do triângulo retângulo (em cm): ");
    scanf("%lf", &L);
    D = sqrt(pow(A, 2) + pow(L, 2));
    printf("A diagonal do triângulo fornecido é de: %.2f cm", D);
    return 0;
    
}