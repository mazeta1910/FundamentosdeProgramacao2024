/*Escreva um c�digo utilizando dois la�os aninhados que imprima o seguinte padr�o:*
#
##
###
####
#####*/
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    char caractere = '#';
    for (int i = 1; i <= 5; i++){
        for (int j = 1; j <= i; j++){
            printf("%c", caractere);
            }
            printf("\n");
            }
            return 0;
}