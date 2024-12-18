#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int numero_aleatorio, escolha_jogador, aposta, saldo;
    srand(time(NULL));

    printf("Insira o saldo do jogador: ");
    scanf("%d", &saldo);

    while (saldo > 0) {
        printf("Insira o valor da aposta: ");
        scanf("%d", &aposta);

        if (aposta > saldo) {
            printf("Voce nao tem saldo suficiente para fazer essa aposta.\n");
        } else if (aposta <= 0) {
            printf("O valor da aposta deve ser maior que zero.\n");
        } else {
            numero_aleatorio = rand() % 37;
            printf("Escolha qual o numero que voce quer apostar: ");
            scanf("%d", &escolha_jogador);

            if (escolha_jogador == numero_aleatorio) {
                saldo = saldo + aposta * 36;
                printf("Parabens, voce ganhou!\n");
                printf("Seu novo saldo e: %d\n", saldo);
            } else {
                saldo = saldo - aposta;
                printf("O numero sorteado foi: %d\n",  numero_aleatorio);
                printf("Que pena, voce perdeu!\n");
                printf("Seu saldo atual eh: R$%d\n", saldo);

            }
        }
    }

    return 0;
}