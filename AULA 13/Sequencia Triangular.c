/*Escreva uma função, que calcula o número de pontos em um triângulo, conforme o diagrama. Onde,
o número de pontos é dado por: d(n) = n*(n+1)/2*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int pontos(int n){
    int pontos = n*(n+1)/2;
    return pontos;
}
int main(){
    setlocale(LC_ALL, "Portuguese");
    int n;
    printf("Digite o número de pontos: ");
    scanf("%d", &n);
    printf("O número de pontos é: %d", pontos(n));
    return 0;
}
