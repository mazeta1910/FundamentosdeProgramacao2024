#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int ContaDivisores(int n){
    int divisores = 1;
    for(int i = 2; i <= n/2; i++){
        if(n % i == 0){
            divisores++;
        }
    }
    return divisores;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int vetor[32];
    int ehAntiPrimo;
    for(int i = 1; i <= 32; i++){
        vetor[i-1] = ContaDivisores(i);
    }
    for(int i = 1; i < 32; i++){
        ehAntiPrimo = 1;
        for(int k = 1; k < i; k++){
            if(vetor[k] >= vetor[i]){
                ehAntiPrimo = 0;
            }
        }
        if(ehAntiPrimo){
            printf("%d é antiprimo com %d divisores\n", i, vetor[i]);
        }
    }
    return 0;
}