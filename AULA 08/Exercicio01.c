/*Escreva um código em  que diga se um array é simétrico ou não:

{1,0,1} -> Simétrico
{2,0,0,2} -> Simétrico
{1,0,3} -> Não simétrico
{2,0,1,2} -> Não simétrico*/

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
        printf("Simétrico\n");
    }
    else{
        printf("[%d, %d, %d, %d]\n",  array[0], array[1], array[2], array[3]);
        printf("Não simétrico\n");
    }
    return 0;
}