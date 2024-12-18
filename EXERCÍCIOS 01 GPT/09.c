/*Exercício: Treinamento de Aldeões no Age of Empires 2
No Age of Empires 2, a criação de aldeões leva tempo.  Vamos simular o treinamento de aldeões em um Centro Urbano, considerando que cada aldeão leva 25 segundos para ser criado.
Objetivo:
Crie um programa que simule o treinamento de aldeões em um Centro Urbano. O programa deve:
Perguntar ao usuário quantos aldeões ele deseja criar. Considerar o custo de 50 de comida para criação de aldeões. 
Perguntar ao usuário se ele quer o desconto dos aldeões hindustânis (5 de comida por aldeão).
Um aldeão é criado em 25 segundos.
Acumular o tempo total de criação.
Exibir o tempo total em segundos e em minutos.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    int qtd_aldeoes, tempo_total, i, escolha_civ, custo_total, desconto_total, aldeoes_extra;
    printf("Qual a quantidade de aldeões que você deseja simular a criação? ");
    scanf("%d", &qtd_aldeoes);

    for (i=0; i<qtd_aldeoes; i++){
        printf("Você deseja o desconto dos aldeões da civilização Hindustani? (1 - Sim / 0 - Não): ");
        scanf("%d", &escolha_civ);
        if (escolha_civ == 1){
            tempo_total = 25*qtd_aldeoes;
            custo_total = 50*qtd_aldeoes;
            int custo_totalh = 45*qtd_aldeoes;
            desconto_total = custo_total - custo_totalh;
            aldeoes_extra = desconto_total/45;
            printf("O tempo total de criação dos %d aldeões: %d segundos\n", qtd_aldeoes, tempo_total);
            printf("O tempo total de criação dos %d aldeões: %d minutos\n", qtd_aldeoes, tempo_total/60);
            printf("Você gastou %d de comida para criar os %d aldeões.\n", custo_totalh, qtd_aldeoes);
            printf("Você teve um desconto de 5 de comida por aldeão. Totalizando um desconto de %d de comida, o que resulta em %d aldeões extras.\n", desconto_total, aldeoes_extra);
        } else {
            tempo_total = 25*qtd_aldeoes;
            custo_total = 50*qtd_aldeoes;
            printf("O tempo total de criação dos %d aldeões em segundos: %d\n", qtd_aldeoes,tempo_total);
            printf("O tempo total de criação dos %d aldeões em minutos: %d\n", qtd_aldeoes, tempo_total/60);
            printf("Você gastou %d de comida para criar os %d aldeões.\n", custo_total, qtd_aldeoes);
        } return 0;
    }
    
}