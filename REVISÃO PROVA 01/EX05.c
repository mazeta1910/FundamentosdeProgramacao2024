/*Construa um código que sorteia um valor aleatório limitado, e em um laço em que o usuário tenha de adivinhar o número. 
Caso acerte o código é finalizado, caso contrário é informado se valor é superior ou inferior à tentativa.*/

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
        printf("Informe um número  entre 1 e 100: ");
        scanf("%d", &escolha);
        tentativas++;

        if (escolha<sorteado){
            printf("Tente um número maior!\n");
            menor++;
        }
        else if (escolha>sorteado){
            printf("Tente um número menor!\n");
            maior++;
        }
        else{
            printf("Parabéns, o número era %d! Você acertou em %d tentativas!", sorteado, tentativas);
            printf("\nVocê digitou %d números maiores.", maior);
            printf("\nVocê digitou %d números menores.", menor);
            break;
            }
        }
        return 0;
}