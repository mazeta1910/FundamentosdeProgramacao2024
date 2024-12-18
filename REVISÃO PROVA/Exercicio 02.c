/*Escreva um código que contenha uma função, e imprima o valor recebido.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int funcao (int x){
    printf("O numero digitado foi: %d", x);
    return x;
}

int main (){
    int x;
    printf("Insira o valor: ");
    scanf("%d", &x);
    funcao(x);
    return 0;
}
