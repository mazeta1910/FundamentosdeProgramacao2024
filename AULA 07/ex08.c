#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    float array[2048];
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o array com números aleatórios entre -0.5 e 0.5
    for (int i = 0; i < 2048; i++) {
        array[i] = ((float)rand() / RAND_MAX) - 0.5f; // Gera número entre -0.5 e 0.5
        printf("%f\n", array[i]);
    }

    return 0;
}