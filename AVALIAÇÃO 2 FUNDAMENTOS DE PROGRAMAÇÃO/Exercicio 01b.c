
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int main (){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int x1, x2, y1, y2, distancia, distanciax, distanciay;
    printf("Digite o valor de x1: ");
    scanf("%d", &x1);
    printf("Digite o valor de x2: ");
    scanf("%d", &x2);
    printf("Digite o valor de y1: ");
    scanf("%d", &y1);
    printf("Digite o valor de y2: ");
    scanf("%d", &y2);
    distanciax = abs(x1 - x2);
    distanciay = abs(y1 - y2);
    distancia = distanciax + distanciay;
    printf("A distância entre os dois pontos é: %d", distancia);
    return 0;
}