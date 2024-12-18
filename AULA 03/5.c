/*Alguns caracteres especiais estão disponíveis, tanto em ASCII,
quanto no formato Unicode. Escreva um código com dois laços
aninhado (um seguido do outro), que sorteie um número
aleatório e imprima um caractere especial. Ao final do primeiro
laço, imprima o \n. Um exemplo de impressão usando caracteres
unicodes é: printf("\u2551");*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>

int main (){
    int i, j, r;
    srand(time(NULL));

    for (j=0;j<8;j++){
        for(i=0;i<8;i++){
            r = rand()%4;
            switch(r){
                case 0:
                printf("\u2551");
                break;
                case 1:
                printf("\u2550");
                case 2:
            }
            printf("%c", 109);
        }
        printf("\n");

        return 0;
    }
}