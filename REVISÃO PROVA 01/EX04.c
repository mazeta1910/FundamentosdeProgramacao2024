/*Como verificar em C, se um n�mero � par ou impar?*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main (){
    int n1;
    setlocale(LC_ALL, "Portuguese");
    printf("Digite um n�mero (0 para encerrar): ");
    while (n1!=0){
        scanf("%d", &n1);
            if (n1%2==0 && n1 != 0){
                printf("%d � par.", n1);
                printf("\nDigite outro n�mero ou insira 0 para encerrar: ");
                }
            else if (n1%2!=0){
                printf("%d � impar.", n1);
                printf("\nDigite outro n�mero ou insira 0 para encerrar: ");
                }
            }
    printf("\nO programa foi encerrado.\n");
            
    return 0;
}