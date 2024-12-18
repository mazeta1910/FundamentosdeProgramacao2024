/*Escreva um c�digo em  que diga se um array � sim�trico ou n�o:

{1,0,1} -> Sim�trico
{2,0,0,2} -> Sim�trico
{1,0,3} -> N�o sim�trico
{2,0,1,2} -> N�o sim�trico*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define N 4

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int numerosorteado1 = rand() % 10 + 1;
    int numerosorteado2 = rand() % 10 + 1;
    int numerosorteado3 = rand() % 10 + 1;
    int numerosorteado4 = rand() % 10 + 1;
    int array[N] = {numerosorteado1, numerosorteado2, numerosorteado3, numerosorteado4};
    if (array[0] == array[3] && array[1] == array[2]){
        printf("[%d, %d, %d, %d]\n",  array[0], array[1], array[2], array[3]);
        printf("Sim�trico\n");
    }
    else{
        printf("[%d, %d, %d, %d]\n",  array[0], array[1], array[2], array[3]);
        printf("N�o sim�trico\n");
    }
    return 0;
}