/*Crie um programa que simula um jogo simples de cartas, onde o objetivo � atingir ou se aproximar do valor 21 sem ultrapass�-lo. 
A cada rodada, um n�mero entre 1 e 12 � sorteado e somado ao total do jogador. 
O usu�rio decide se quer continuar jogando ou parar. O jogo termina quando o jogador atinge ou ultrapassa 21, ou opta por parar.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int total = 0, sorteado, continuar = 1;
    while (continuar == 1) {
        sorteado = (rand() % 12) + 1;
        total += sorteado;
        printf("Voc� recebeu %d pontos. Seu total � %d.\n", sorteado, total);
        if (total > 21) {
            printf("Voc� ultrapassou 21 e perdeu!\n");
            break;
            }
            printf("Deseja continuar? (1) Sim, (2) N�o\n");
            scanf("%d", &continuar);
            if (continuar == 2) {
                printf("Voc� parou e seu total � %d.\n", total);
                break;
                }
                }
                return 0;
}