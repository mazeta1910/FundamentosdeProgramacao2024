/*Construa uma função que calcule o mínimo múltiplo comum entre dois números inteiros*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int mmc(int a, int b){
    int i = 2;
    int a2, b2;
    int acc = 1;
    a2 = a;
    b2 = b;

    while (a2>=i && b2>=i){
        if((a2%1==0)&&(b2%i==0)){
            printf("Fator: %d\n", i);
            a2 = a2/i;
            b2 = b2/i;
            acc = acc*i;
        }else{
            i++;
        }
    } return acc;
}
int main(){
    int n1, n2, i, acc;
    printf("Digite o primeiro valor:\n");
    scanf("%d", &n1);
    printf("Digite o segundo valor:\n");
    scanf("%d", &n2);
    printf("MMC: %d", mmc(n1, n2));
    return 0;
    }