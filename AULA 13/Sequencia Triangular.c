/*Escreva uma fun��o, que calcula o n�mero de pontos em um tri�ngulo, conforme o diagrama. Onde,
o n�mero de pontos � dado por: d(n) = n*(n+1)/2*/

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
    printf("Digite o n�mero de pontos: ");
    scanf("%d", &n);
    printf("O n�mero de pontos �: %d", pontos(n));
    return 0;
}
