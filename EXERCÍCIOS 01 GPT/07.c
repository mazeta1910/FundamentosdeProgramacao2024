/*Crie um programa que simule o lançamento de um dado de 6 faces. 
O programa deve gerar um número aleatório entre 1 e 6 e exibir o resultado na tela. 
Permita que o usuário escolha quantas vezes deseja lançar o dado.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int num, i;
    srand(time(NULL));
    printf("Quantas vezes deseja jogar o dado? ");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        printf("Jogada #%d: %d\n", i+1, rand() % 6 + 1);
    }
    return 0;
}