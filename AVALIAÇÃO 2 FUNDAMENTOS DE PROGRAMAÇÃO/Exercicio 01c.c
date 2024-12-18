
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

int main (){
    setlocale(LC_ALL, "Portuguese_Brazil");
    float volume;
    float raio, altura;
    printf("Insira o raio do cone: ");
    scanf("%f", &raio);
    printf("Insira a altura do cone: ");
    scanf("%f", &altura);
    volume = (3.14 * pow(raio, 2) * altura) / 3;
    printf("O volume do cone é: %.2f", volume);
    return 0;
}