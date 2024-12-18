/*Escreva um código que contenha uma função, e imprima a soma de dois valores recebidos.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int soma (int a, int b){
    setlocale(LC_ALL, "Portuguese_Brazil");
    printf("A soma dos números fornecidos é: %d", a+b);
    return a+b;
}

int main (){
    int a, b;
    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    printf("Digite o segundo valor: ");
    scanf("%d", &b);
    soma(a, b);
    return 0;
}