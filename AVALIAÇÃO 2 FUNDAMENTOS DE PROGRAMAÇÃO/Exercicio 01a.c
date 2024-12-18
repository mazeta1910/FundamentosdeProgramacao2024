
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main (){
    setlocale(LC_ALL, "Portuguese_Brazil");
    float numero;
    printf("Informe um número: ");
    scanf("%f", &numero);
    int sinal = numero / abs(numero);
    float mantissa = abs(numero) / pow(10, floor(log10(abs(numero))));
    int expoente = floor(log10(abs(numero)));
    printf("\nA mantissa do número é: %f", mantissa);
    printf("\nO sinal do número é: %d", sinal);
    printf("\nO expoente do número é: %d", expoente);
    return 0;

}