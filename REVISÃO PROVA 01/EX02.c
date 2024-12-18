/*Escreva um código que contenha uma função, e imprima o valor recebido.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int funcao (int x)
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    printf("O numero digitado foi: %d", x);
    return x;
}

int main (){

    int x;
    printf("Digite um valor: ");
    scanf("%d", &x);
    funcao(x);
    return 0;
}