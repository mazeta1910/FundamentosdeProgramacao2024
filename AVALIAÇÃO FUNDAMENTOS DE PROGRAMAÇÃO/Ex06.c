/*Este exercício explora a dinâmica entre competição e cooperação em um cenário simplificado de teoria dos jogos.
Imagine um jogo interativo entre um Jogador humano e um Computador.
O objetivo de ambos é maximizar seus ganhos ao longo de 5 rodadas. 
A cada rodada, ambos escolhem entre duas ações: Competir (0) ou Cooperar (1).
Jogador	      Computador	 Ganho Jogador	Ganho Computador
Compete (0)	  Compete (0)	  0.5	             0.5 ok
Copera (1)	  Compete (0)	  0.0	             1.0 ok
Compete (0)	  Copera (1)	  1.0	             0.0
Copera (1)	  Copera (1)	  1.25	             1.25 ok
  
Escreva um código que para 5 rodadas, compute o ganho total do jogador e do computador. O código deve ser um laço, onde cada iteração do laço deve:
	1.  ler a jogada do usuário (0 ou 1)
	2.  sorteia um número randômico (0 ou 1) para jogada do computador;
	3.  Decide o ganho do jogador e do computador conforme a tabela anterior
	4. Acumula em uma variável o ganho do usuario e outra o ganho do computador.
Ao final do laço imprime o total de ganhos.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main ()
{
    setlocale(LC_ALL, "Portuguese");
    float jogadausuario, jogadacomputador, ganhousuario=0, ganhocomputador=0, i;
    for (i=1; i<=5; i++){
        srand(time(NULL));
        printf("Digite a sua jogada! 0 para competir e 1 para cooperar: ");
        scanf("%f", &jogadausuario);
        jogadacomputador = (rand() % 2);
        if (jogadacomputador == 0 && jogadausuario == 0){
            printf("Ambos escolheram competir! 0.5 pontos para cada um!");
            ganhousuario+=0.5;
            ganhocomputador+=0.5;
            printf("\n\nSua pontuação: %.2f", ganhousuario);
            printf("\nPontuação do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 1 && jogadausuario == 1){
            printf("Ambos escolheram cooperar! 1.25 pontos para ambos!");
            ganhocomputador+=1.25;
            ganhousuario+=1.25;
            printf("\n\nSua pontuação: %.2f", ganhousuario);
            printf("\nPontuação do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 0 && jogadausuario == 1){
            printf("Você escolheu cooperar e o computador escolheu competir!");
            ganhocomputador+=1.0;
            ganhousuario+=0.0;
            printf("\n\nSua pontuação: %.2f", ganhousuario);
            printf("\nPontuação do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 1 && jogadausuario == 0){
            printf("Você escolheu competir e o computador escolheu cooperar!");
            ganhousuario+=1.0;
            ganhocomputador+=0.0;
            printf("\n\nSua pontuação: %.2f", ganhousuario);
            printf("\nPontuação do computador: %.2f\n\n", ganhocomputador);
        }
        else {
            printf("Jogada inválida!");
            continue;
        }
    }

    printf("\n Chegamos na 5a rodada! O jogo terminou.\n");
    printf("O jogador ficou com %.2f pontos e o computador com %.2f.\n", ganhousuario, ganhocomputador);

    if (ganhousuario > ganhocomputador){
        printf("O jogador ganhou!");
    }
    else if (ganhocomputador > ganhousuario){
        printf("O computador ganhou!");
    }
    else {
        printf("Empate!");
    }
    return 0;

}