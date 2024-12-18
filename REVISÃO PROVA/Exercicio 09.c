/*Crie um programa que simula um jogo simples de cartas, onde o objetivo é atingir ou se aproximar do valor 21 sem ultrapassá-lo. 
A cada rodada, um número entre 1 e 12 é sorteado e somado ao total do jogador. 
O usuário decide se quer continuar jogando ou parar. O jogo termina quando o jogador atinge ou ultrapassa 21, ou opta por parar.*/

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
        printf("Você recebeu %d pontos. Seu total é %d.\n", sorteado, total);
        if (total > 21) {
            printf("Você ultrapassou 21 e perdeu!\n");
            break;
            }
            printf("Deseja continuar? (1) Sim, (2) Não\n");
            scanf("%d", &continuar);
            if (continuar == 2) {
                printf("Você parou e seu total é %d.\n", total);
                break;
                }
                }
                return 0;
}