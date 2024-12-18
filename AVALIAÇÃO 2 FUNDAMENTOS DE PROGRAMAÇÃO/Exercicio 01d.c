
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    float angulo, coseno, seno;
    printf("Digite o ângulo: ");
    scanf("%f", &angulo);
    coseno = cos(angulo);
    seno = sin(angulo);
    printf("Matriz de rotação:\n");
    printf("%.2f\t%.2f\n", coseno, seno);
    printf("-%.2f\t%.2f\n", seno, coseno);
    return 0;
}