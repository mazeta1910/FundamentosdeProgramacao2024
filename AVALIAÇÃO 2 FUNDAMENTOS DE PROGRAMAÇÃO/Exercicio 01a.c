
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main (){
    setlocale(LC_ALL, "Portuguese_Brazil");
    float numero;
    printf("Informe um n�mero: ");
    scanf("%f", &numero);
    int sinal = numero / abs(numero);
    float mantissa = abs(numero) / pow(10, floor(log10(abs(numero))));
    int expoente = floor(log10(abs(numero)));
    printf("\nA mantissa do n�mero �: %f", mantissa);
    printf("\nO sinal do n�mero �: %d", sinal);
    printf("\nO expoente do n�mero �: %d", expoente);
    return 0;

}