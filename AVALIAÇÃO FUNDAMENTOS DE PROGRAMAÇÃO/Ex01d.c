/*Dada uma coordenada em um sistema polar, com um ângulo ? (em radianos) e uma distância  r, converta-a para coordenadas cartesianas:*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");
    float r, theta, x, y;
    printf("Digite o valor da distância (r): ");
    scanf("%f", &r);
    printf("Digite o valor do ângulo (?) em radianos: ");
    scanf("%f", &theta);
    x = r * cos(theta);
    y = r * sin(theta);
    printf("\nA coordenada x é: %.2f", x);
    printf("\nA coordenada y é: %.2f", y);
    return 0;
}