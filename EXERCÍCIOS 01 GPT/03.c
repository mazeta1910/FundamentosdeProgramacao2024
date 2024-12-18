/*Crie um programa em C que simule uma corrida entre dois jogadores, cada um lançando um dado de 6 faces. 
O programa deve gerar números aleatórios entre 1 e 6 para cada jogador, representando o resultado do lançamento do dado. 
A cada rodada, o programa deve exibir o resultado dos dados de cada jogador e quem está ganhando a corrida. 
O jogo termina quando um dos jogadores atingir um total de 20 pontos.
Dicas:
•	Utilize a função rand() para gerar os números aleatórios.
•	Utilize um laço while para simular as rodadas da corrida, até que um jogador atinja 20 pontos.
•	Utilize estruturas condicionais (if, else if, else) para comparar os resultados dos dados e determinar o vencedor da rodada.
•	Utilize variáveis para acumular a pontuação de cada jogador.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (){
    srand(time(NULL));
    int rodjogador1 = 0, rodjogador2 = 0, rodada = 1;
    int dado1, dado2, vitjog1 = 0, vitjog2 = 0;

    while (rodjogador1 < 20 && rodjogador2 < 20){
        printf("\nRodada %d:\n", rodada);
        dado1 = (rand() % 6) + 1;
        dado2 = (rand() % 6) + 1;
        printf("Jogador 1: %d\n", dado1);
        printf("Jogador 2: %d\n", dado2);
        if (dado1 > dado2){
            printf("O jogador 1 venceu!\n");
            vitjog1++;}
        else if (dado2 > dado1){
            printf("O jogador 2 venceu!\n");
            vitjog2++;}
        else {
            printf("Empate!\n");
            }

            rodjogador1 += dado1;
            rodjogador2 += dado2;

            printf("Pontuacao atual: Jogador 1 - %d, Jogador 2 - %d",  rodjogador1, rodjogador2);

            if (rodjogador1 == 20){
                printf("\nO jogador 1 venceu a corrida!\n");
                break;}
            else if (rodjogador2 == 20){
                printf("\nO jogador 2 venceu a corrida!\n");
                break;}
            
            rodada++;
    } 
    return 0;
}

