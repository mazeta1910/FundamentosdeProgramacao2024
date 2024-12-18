/*Construa um c�digo que sorteia um valor aleat�rio limitado, e em um la�o em que o usu�rio tenha de adivinhar o n�mero. 
Caso acerte o c�digo � finalizado, caso contr�rio � informado se valor � superior ou inferior � tentativa.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int sorteado = rand() % 100 + 1;
    int escolha, tentativas, maior=0, menor=0;
    tentativas = 0;

    while (escolha != sorteado){
        printf("Informe um n�mero  entre 1 e 100: ");
        scanf("%d", &escolha);
        tentativas++;

        if (escolha<sorteado){
            printf("Tente um n�mero maior!\n");
            menor++;
        }
        else if (escolha>sorteado){
            printf("Tente um n�mero menor!\n");
            maior++;
        }
        else{
            printf("Parab�ns, o n�mero era %d! Voc� acertou em %d tentativas!", sorteado, tentativas);
            printf("\nVoc� digitou %d n�meros maiores.", maior);
            printf("\nVoc� digitou %d n�meros menores.", menor);
            break;
            }
        }
        return 0;
}