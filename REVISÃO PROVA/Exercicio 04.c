/*Como verificar em C, se um n�mero � par ou impar?*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main (){
    int n1;
    setlocale(LC_ALL, "Portuguese");
    printf("Digite um n�mero: ");
    scanf("%d", &n1);
    
    if (n1%2 == 0){
        printf("%d � par.", n1);
    }
    else{
        printf("%d � impar.", n1);
    }
    return 0;
}
