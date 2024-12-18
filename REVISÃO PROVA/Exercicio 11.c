/*Escreva um programa que desenha um retângulo usando o caractere "#" com dimensões pré-definidas de 5x20. 
Utilizando dois laços for, o programa imprime uma linha completa de símbolos para cada linha do retângulo. 
Após imprimir todos os caracteres de uma linha, o programa quebra a linha para iniciar a próxima, repetindo o processo até formar o retângulo completo.
Refaça o programa da questão anterior, desta vez sorteando um valor 0 ou 1, para imprimir ? ? ou ?#? de acordo com o numero sorteado.
*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int i, j, num, cont = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 20; j++) {
            num = rand() % 2;
            if (num == 0) {
                printf(" ");
                } else {
                    printf("#");
                    cont++;
                    }
                    }
                    printf("\n");
                    }
                    return 0;
                    }