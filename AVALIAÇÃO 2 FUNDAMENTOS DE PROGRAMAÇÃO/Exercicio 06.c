
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int matriz[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int maior = matriz[0][0];
    int menor = matriz[0][0];
    int x_maior = 0;
    int y_maior = 0;
    int x_menor = 0;
    int y_menor = 0;
    int x_medio = 0;
    int y_medio = 0;
    int amplitude = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matriz[i][j] > maior)
            {
                maior = matriz[i][j];
                x_maior = i;
                y_maior = j;
            }
            if (matriz[i][j] < menor)
            {
                menor = matriz[i][j];
                x_menor = i;
                y_menor = j;
            }
        }
    }

    x_medio = (x_maior + x_menor) / 2;
    y_medio = (y_maior + y_menor) / 2;

    amplitude = sqrt(pow(x_maior - x_menor, 2) + pow(y_maior - y_menor, 2));

    printf("O maior valor é %d e está na posição (%d, %d).\n", maior, x_maior, y_maior);
    printf("O menor valor é %d e está na posição (%d, %d).\n", menor, x_menor, y_menor);
    printf("O ponto médio é (%d, %d).\n", x_medio, y_medio);
    printf("A amplitude é %d.\n", amplitude);

    return 0;
}