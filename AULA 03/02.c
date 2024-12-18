/*Exerc�cio 2 - Dilema do prisioneiro
O dilema do prisioneiro � uma das bases da teoria de jogos, que tem
implica��es em diversas �reas como ecologia. Neste dilema dois
indiv�duos (A e B) s�o acusados de cometer algum crime, contudo devido a
falta de provas, a pol�cia prop�e um acordo:*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    int escolhajogador, escolhacomputador;
    srand(time(NULL));

    escolhacomputador = rand()%2;
        printf("Voce eh o prisioneiro. Escolha um alternativa\n");
        printf("0 - Negar\n1 - Delatar\n");
        scanf("%d", &escolhajogador);
        printf("\n");
        printf("Escolha do jogador: %d\n", escolhajogador);
        printf("Escolha do computador: %d\n", escolhacomputador);
        // 0 negar 1 delatar ||
        if (escolhajogador == 0 && escolhacomputador == 0){
            printf("\nAmbos foram condenados a 6 meses.\n");}
        else if (escolhajogador == 1 && escolhacomputador == 0){
            printf("\nVoce saiu livre. O computador foi condenado a 10 anos.");}
        else if (escolhajogador == 0 && escolhacomputador == 1){
            printf("\nVoce foi condenado a 10 anos. O computador saiu livre.");}
        else if (escolhajogador == 1 && escolhacomputador ==1 ){
            printf("\nAmbos foram condenados a 5 anos.");}  

    return 0;
}
