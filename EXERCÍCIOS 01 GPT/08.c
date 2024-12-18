/*Exercício: Simulador de Ataque no Age of Empires 2
Cenário:
Um Arqueiro (ataque: 6, variação de ataque: +/- 2) ataca um Guerreiro (armadura: 2).
Objetivo:
Crie um programa que simule 10 ataques do Arqueiro no Guerreiro. Para cada ataque:
Gere um número aleatório entre 4 e 8 (ataque do Arqueiro com variação).
Calcule o dano: ataque do Arqueiro - armadura do Guerreiro.
Exiba o dano causado em cada ataque.
Ao final, mostre o dano total causado.
Dicas:
Use a função rand() para gerar o ataque do Arqueiro.
Use um laço for para simular os 10 ataques.
Use uma variável para acumular o dano total.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    int dano, ataque, armadura=2, vida=120, i;
    
    do{
        ataque = rand() % 8 + 4;
        dano = ataque - armadura;
        printf("Dano causado: %d\n", dano);
        vida = vida - dano;
        printf("Vida restante: %d\n", vida);
        i++;
    }while(vida>0);
    printf("Foram necessarios %d ataques do seu arqueiro para matar o guerreiro.", i);
    return 0;
}