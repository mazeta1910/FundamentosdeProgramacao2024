/*Exercício: Jogo de Dados Simplificado
5.	Crie um programa que simule um jogo de dados simples. 
O programa deve gerar dois números aleatórios entre 1 e 6, representando o resultado de dois dados. 
O programa deve então exibir o resultado de cada dado e a soma dos dois valores.
•	Dicas:
•	Use a função rand() para gerar os números aleatórios.
•	Exiba o valor de cada dado individualmente.
•	Calcule a soma dos dois valores e exiba o resultado.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (){
    srand(time(NULL));
    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;
    int soma = dado1 + dado2;
    printf("\nDado 1: %d", dado1);
    printf("\nDado 2: %d", dado2);
    printf("\nSoma %d + %d = %d", dado1, dado2, soma);
    return 0;
}