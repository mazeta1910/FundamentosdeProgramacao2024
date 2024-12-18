#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Fun��o que implementa o mapa do dobro sem usar fmod
float mapa_do_dobro(float x) {
    float resultado = 2 * x; // Calcula 2 * x
    if (resultado >= 1.0) {
        resultado -= 1.0; // Se o resultado � maior ou igual a 1, subtrai 1
    }
    return resultado; // Retorna o resultado
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios

    // 1. Declara��o das vari�veis
    float x = 0.15;
    float y = 0.1501;

    // 3. La�o de itera��o com 1000 itera��es
    for (int i = 0; i < 1000; i++) {
        // 3.a. Imprime a diferen�a entre x e y
        printf("Itera��o %d: Diferen�a = %f\n", i, x - y);
        
        // 3.b. Atualiza x e y usando o mapa do dobro
        x = mapa_do_dobro(x);
        y = mapa_do_dobro(y + ((float)rand() / RAND_MAX) * 0.01 - 0.005); // Adiciona um pequeno valor aleat�rio a y
    }

    return 0;
}