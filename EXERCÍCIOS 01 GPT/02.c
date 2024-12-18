/*Crie um programa em C que gere um número aleatório entre 1 e 100. O programa deve pedir ao usuário que adivinhe o número. 
A cada tentativa, o programa deve informar se o número digitado é maior ou menor que o número secreto. 
O jogo continua até que o usuário adivinhe o número correto. Ao final, o programa deve exibir o número de tentativas que o usuário fez, 
além de exibir quantas tentativas foram maiores ou menores que o número secreto.

Dicas:

Utilize a função rand() para gerar o número aleatório.
Utilize um laço while para repetir o processo de adivinhação até que o usuário acerte o número.
Utilize estruturas condicionais (if, else if, else) para comparar o número digitado com o número secreto e fornecer feedback ao usuário.
Utilize uma variável para contar o número de tentativas.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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