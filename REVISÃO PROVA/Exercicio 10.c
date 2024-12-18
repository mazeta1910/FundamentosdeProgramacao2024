/*Escreva um programa que desenha um retângulo usando o caractere "#" com dimensões pré-definidas de 5x20. 
Utilizando dois laços for, o programa imprime uma linha completa de símbolos para cada linha do retângulo. 
Após imprimir todos os caracteres de uma linha, o programa quebra a linha para iniciar a próxima, repetindo o processo até formar o retângulo completo.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    int i, j, n = 5, m = 20;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("#");
            }
            printf("\n");
            }
            return 0;
}