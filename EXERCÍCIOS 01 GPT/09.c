/*Exerc�cio: Treinamento de Alde�es no Age of Empires 2
No Age of Empires 2, a cria��o de alde�es leva tempo.  Vamos simular o treinamento de alde�es em um Centro Urbano, considerando que cada alde�o leva 25 segundos para ser criado.
Objetivo:
Crie um programa que simule o treinamento de alde�es em um Centro Urbano. O programa deve:
Perguntar ao usu�rio quantos alde�es ele deseja criar. Considerar o custo de 50 de comida para cria��o de alde�es. 
Perguntar ao usu�rio se ele quer o desconto dos alde�es hindust�nis (5 de comida por alde�o).
Um alde�o � criado em 25 segundos.
Acumular o tempo total de cria��o.
Exibir o tempo total em segundos e em minutos.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    int qtd_aldeoes, tempo_total, i, escolha_civ, custo_total, desconto_total, aldeoes_extra;
    printf("Qual a quantidade de alde�es que voc� deseja simular a cria��o? ");
    scanf("%d", &qtd_aldeoes);

    for (i=0; i<qtd_aldeoes; i++){
        printf("Voc� deseja o desconto dos alde�es da civiliza��o Hindustani? (1 - Sim / 0 - N�o): ");
        scanf("%d", &escolha_civ);
        if (escolha_civ == 1){
            tempo_total = 25*qtd_aldeoes;
            custo_total = 50*qtd_aldeoes;
            int custo_totalh = 45*qtd_aldeoes;
            desconto_total = custo_total - custo_totalh;
            aldeoes_extra = desconto_total/45;
            printf("O tempo total de cria��o dos %d alde�es: %d segundos\n", qtd_aldeoes, tempo_total);
            printf("O tempo total de cria��o dos %d alde�es: %d minutos\n", qtd_aldeoes, tempo_total/60);
            printf("Voc� gastou %d de comida para criar os %d alde�es.\n", custo_totalh, qtd_aldeoes);
            printf("Voc� teve um desconto de 5 de comida por alde�o. Totalizando um desconto de %d de comida, o que resulta em %d alde�es extras.\n", desconto_total, aldeoes_extra);
        } else {
            tempo_total = 25*qtd_aldeoes;
            custo_total = 50*qtd_aldeoes;
            printf("O tempo total de cria��o dos %d alde�es em segundos: %d\n", qtd_aldeoes,tempo_total);
            printf("O tempo total de cria��o dos %d alde�es em minutos: %d\n", qtd_aldeoes, tempo_total/60);
            printf("Voc� gastou %d de comida para criar os %d alde�es.\n", custo_total, qtd_aldeoes);
        } return 0;
    }
    
}