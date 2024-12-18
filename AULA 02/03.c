#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Semente para o gerador de n�meros aleat�rios
    srand(time(NULL));

    // Gera um n�mero aleat�rio entre 0 e 1
    float num1 = (float)rand() / RAND_MAX;

    // Ajusta o intervalo para -1 a 1
    num1 = num1 * 2 - 1;

    printf("N�mero aleat�rio entre -1 e 1: %f\n", num1);

    return 0;
}
