/*Escreva um programa que desenha um ret�ngulo usando o caractere "#" com dimens�es pr�-definidas de 5x20. 
Utilizando dois la�os for, o programa imprime uma linha completa de s�mbolos para cada linha do ret�ngulo. 
Ap�s imprimir todos os caracteres de uma linha, o programa quebra a linha para iniciar a pr�xima, repetindo o processo at� formar o ret�ngulo completo.*/

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