/*Escreva um código que receba como entrada um valor inteiro e imprima um valor float*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>


int main (){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int num;
    printf("Digite um valor inteiro: ");
    scanf("%d", &num);
    printf("O valor float é: %f", (float)num);
    return 0;
}