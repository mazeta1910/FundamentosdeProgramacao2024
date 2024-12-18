#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Crie um programa em C que simule o cadastro de participantes em um evento. O programa deve gerar aleatoriamente a idade de 10 participantes. 
Para cada idade gerada, o programa deve:
Verificar se o participante é maior ou menor de idade (considerando 18 anos como a idade mínima).
Exibir uma mensagem na tela informando se o participante é maior ou menor de idade.
Calcular e exibir a média das idades de todos os participantes.*/

int main (){
    int i, idade, soma_idades, numeroparticipantes, maioridade = 0, menoridade = 0;
    float media_idades;
    srand(time(NULL));
    
    printf("Insira o numero de participantes: ");
    scanf("%d", &numeroparticipantes);
    
    for (i=0; i<numeroparticipantes; i++){
        idade = rand() % 100 + 1; //gera um número aleatorio
        printf("\nO participante %d tem %d anos.", i+1, idade);

        if(idade>=18){
            maioridade++;
            printf("\nEste participante eh maior de idade.\n");
        }
        if(idade<17){
            menoridade++;
            printf("\nEste participante eh menor de idade.\n");
        }
        soma_idades = soma_idades + idade;
    }

    media_idades = (double)soma_idades/numeroparticipantes;

    printf("\nO numero de participantes maiores de idade: %d", maioridade);
    printf("\nO numero de participantes menores de idade: %d", menoridade);
    printf("\nA media das idades dos participantes: %.2f", media_idades);
    
    return 0;
}