/*Construa um c�digo que contenha um array com 2048 n�meros em ponto flutuante entre -0.5 e 0.5
Ap�s inicializar o vetor, conforme o c�digo anterior, fa�a mais um la�o desta vez
somando cada posi��o com o valor anterior:*/

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