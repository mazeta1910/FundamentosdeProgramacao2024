/*Este exerc�cio explora a din�mica entre competi��o e coopera��o em um cen�rio simplificado de teoria dos jogos.
Imagine um jogo interativo entre um Jogador humano e um Computador.
O objetivo de ambos � maximizar seus ganhos ao longo de 5 rodadas. 
A cada rodada, ambos escolhem entre duas a��es: Competir (0) ou Cooperar (1).
Jogador	      Computador	 Ganho Jogador	Ganho Computador
Compete (0)	  Compete (0)	  0.5	             0.5 ok
Copera (1)	  Compete (0)	  0.0	             1.0 ok
Compete (0)	  Copera (1)	  1.0	             0.0
Copera (1)	  Copera (1)	  1.25	             1.25 ok
  
Escreva um c�digo que para 5 rodadas, compute o ganho total do jogador e do computador. O c�digo deve ser um la�o, onde cada itera��o do la�o deve:
	1.  ler a jogada do usu�rio (0 ou 1)
	2.  sorteia um n�mero rand�mico (0 ou 1) para jogada do computador;
	3.  Decide o ganho do jogador e do computador conforme a tabela anterior
	4. Acumula em uma vari�vel o ganho do usuario e outra o ganho do computador.
Ao final do la�o imprime o total de ganhos.*/

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
            printf("\n\nSua pontua��o: %.2f", ganhousuario);
            printf("\nPontua��o do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 1 && jogadausuario == 1){
            printf("Ambos escolheram cooperar! 1.25 pontos para ambos!");
            ganhocomputador+=1.25;
            ganhousuario+=1.25;
            printf("\n\nSua pontua��o: %.2f", ganhousuario);
            printf("\nPontua��o do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 0 && jogadausuario == 1){
            printf("Voc� escolheu cooperar e o computador escolheu competir!");
            ganhocomputador+=1.0;
            ganhousuario+=0.0;
            printf("\n\nSua pontua��o: %.2f", ganhousuario);
            printf("\nPontua��o do computador: %.2f\n\n", ganhocomputador);
        }
        else if (jogadacomputador == 1 && jogadausuario == 0){
            printf("Voc� escolheu competir e o computador escolheu cooperar!");
            ganhousuario+=1.0;
            ganhocomputador+=0.0;
            printf("\n\nSua pontua��o: %.2f", ganhousuario);
            printf("\nPontua��o do computador: %.2f\n\n", ganhocomputador);
        }
        else {
            printf("Jogada inv�lida!");
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