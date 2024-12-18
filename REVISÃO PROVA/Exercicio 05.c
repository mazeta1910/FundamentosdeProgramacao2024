/*Construa um código que sorteia um valor aleatório limitado, e em um laço em que o usuário tenha de adivinhar o número. 
Caso acerte o código é finalizado, caso contrário é informado se valor é superior ou inferior à tentativa.*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    int numerosecreto, numerodigitado, tentativas = 0, numeromenor = 0, numeromaior = 0;
    srand(time(NULL));
    numerosecreto = rand() % 100 + 1;
    while (numerosecreto != numerodigitado){
        printf("Adivinhe o numero entre 1 e 100: ");
        scanf("%d", &numerodigitado);
        tentativas++;

        if (numerodigitado < numerosecreto){
            printf("\nO numero inserido eh menor que o numero secreto. Tente novamente.\n");
            numeromenor++;
        }
        else if (numerodigitado > numerosecreto){
            printf("\nO numero inserido eh maior que o numero secreto. Tente novamente.\n");
            numeromaior++;
        }
        else if (numerodigitado == numerosecreto){
            printf("\nParabens! Voce acertou o numero em %d tentativas!", tentativas);
            printf("\nVoce digitou %d numeros maiores que o numero secreto.", numeromaior);
            printf("\nVoce digitou %d numeros menores que o numero secreto.\n", numeromenor);
        }
    }
    return 0;
}