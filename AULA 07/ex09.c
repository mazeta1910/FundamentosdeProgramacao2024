/*Construa um código que contenha um array com 2048 números em ponto flutuante entre -0.5 e 0.5
Após inicializar o vetor, conforme o código anterior, faça mais um laço desta vez
somando cada posição com o valor anterior:*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    float array[2048];
    srand(time(NULL));
    for (int i = 0; i < 2048; i++) {
        array[i] = (float)(rand() % 1000) / 1000 - 0.5;
        printf("%f \n", array[i]);
    }
    for (int i = 1; i < 2048; i++) {
        array[i] = array[i] + array[i - 1];
        printf("%f \n", array[i]);
    }
    return 0;
}