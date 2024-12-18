#include <math.h>
#include <stdio.h>
#include <locale.h>

/* Construa uma função para converter temperaturas de graus Celsius para graus Fahrenheit:*/

float conversor(float C){
    float f = (9.0/5.0)*C + 32.0;
    return f;
}

int main(int argc, char** argv){
    setlocale(LC_ALL, "Portuguese_Brazil");
    float temperatura, temperatura1, F, F1;
    printf("Insira a temperatura em graus Celsius: ");
    scanf("%f", &temperatura),
    F = conversor(temperatura);
    printf("O valor em Fahrenheit é: %.2f", F);
    printf("\nInsira a segunda temperatura em graus Celsius: ");
    scanf("%f", &temperatura1),
    F1 = conversor(temperatura1);
    printf("O valor em Fahrenheit é: %.2f", F1);
    return 0;
}