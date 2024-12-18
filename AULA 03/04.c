/*Crie um algoritmo para decompor numeros inteiros.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
    int N, i;
    
    printf("Insira um numero inteiro: ");
    scanf("%d", &N);

    i = 2;

    while (i<=N) {
        if (N%i==0){
            printf("\n%d", i);
            N = N/i;
            }
            else {
                i=i+1;
            }
    }
    printf("\n");
    return 0;
}