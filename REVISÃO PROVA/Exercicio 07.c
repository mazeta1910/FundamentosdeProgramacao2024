/*Crie um programa que calcule o volume de uma esfera. Solicite o raio (r) ao usu�rio e exiba o resultado. Use a f�rmula:*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main (){
    setlocale(LC_ALL, "Portuguese");
    float r, V;
    printf("Digite o raio da esfera: ");
    scanf("%f", &r);
    V = 4.0/3.0*(M_PI*pow(r,3));
    printf("O volume da esfera �: %.2f", V);
    return 0;
}