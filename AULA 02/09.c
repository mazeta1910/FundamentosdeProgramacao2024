#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, vitoriaMaquina = 0, vitoriaUsuario = 0;
    char jogadaUsuario;
    int u, m;

    srand(time(NULL));

    for (i = 0; i < 5; i++) {
        printf("Pedra, Papel ou Tesoura?\n");
        printf("0 - Pedra\n1 - Papel\n2 - Tesoura\n");
        printf("Digite a sua jogada: ");
        scanf(" %c", &jogadaUsuario);

        // Converte a jogada do usuário para um número
        switch (jogadaUsuario) {
            case '0':
                u = 0;
                break;
            case '1':
                u = 1;
                break;
            case '2':
                u = 2;
                break;
            default:
                printf("Jogada invalida!\n");
                i--; // Decrementa o contador para repetir a rodada
                continue; // Volta para o início do loop
        }

        // Gera a jogada da máquina
        m = rand() % 3;

        printf("Voce jogou: %d\n", u);
        printf("Maquina jogou: %d\n", m);

        // Verifica quem ganhou
        if (u == m) {
            printf("Empate!\n");
        } else if ((u == 0 && m == 2) || (u == 1 && m == 0) || (u == 2 && m == 1)) {
            printf("Voce ganhou!\n");
            vitoriaUsuario++;
        } else {
            printf("Maquina ganhou!\n");
            vitoriaMaquina++;
        }
    }

    // Imprime o resultado final
    if (vitoriaUsuario > vitoriaMaquina) {
        printf("Voce venceu o jogo!\n");
    } else if (vitoriaMaquina > vitoriaUsuario) {
        printf("A maquina venceu o jogo!\n");
    } else {
        printf("O jogo terminou em empate!\n");
    }

    return 0;
}
