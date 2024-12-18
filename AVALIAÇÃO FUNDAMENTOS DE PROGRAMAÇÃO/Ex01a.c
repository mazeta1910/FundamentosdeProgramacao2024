/*Dado a altura (A) e a largura (L), como uma vari�vel lida,  calcule a hipotenusa, conforme: */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");
    float A, L, hipotenusa;
    printf("Digite a altura: ");
    scanf("%f", &A);
    printf("Digite a largura: ");
    scanf("%f", &L);
    hipotenusa = sqrt(A*A + L*L);
    printf("A hipotenusa �: %.2f\n", hipotenusa);
    return 0;
}