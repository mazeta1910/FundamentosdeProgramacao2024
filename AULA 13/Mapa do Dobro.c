#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Função que implementa o mapa do dobro sem usar fmod
float mapa_do_dobro(float x) {
    float resultado = 2 * x; // Calcula 2 * x
    if (resultado >= 1.0) {
        resultado -= 1.0; // Se o resultado é maior ou igual a 1, subtrai 1
    }
    return resultado; // Retorna o resultado
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // 1. Declaração das variáveis
    float x = 0.15;
    float y = 0.1501;

    // 3. Laço de iteração com 1000 iterações
    for (int i = 0; i < 1000; i++) {
        // 3.a. Imprime a diferença entre x e y
        printf("Iteração %d: Diferença = %f\n", i, x - y);
        
        // 3.b. Atualiza x e y usando o mapa do dobro
        x = mapa_do_dobro(x);
        y = mapa_do_dobro(y + ((float)rand() / RAND_MAX) * 0.01 - 0.005); // Adiciona um pequeno valor aleatório a y
    }

    return 0;
}