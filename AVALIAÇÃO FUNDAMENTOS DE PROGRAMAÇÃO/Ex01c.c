/*Dado o raio r de uma esfera, calcule o volume dessa esfera. */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    double r, V;
    printf("Digite o raio da esfera: ");
    scanf("%lf", &r);
    V = (4.0/3.0)*M_PI*pow(r, 3);
    printf("O volume da esfera é: %.2lf\n", V);
    return 0;
}