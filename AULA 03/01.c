#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
    srand(time(NULL));

    int N, i, areapercentual=0;
    double x, y, pi;

    printf("Digite o numero de iteracoes: ");
    scanf("%d", &N);

    for (i=0; i<N; i++){
        // Gerar o número aleatório:
        double numero_aleatorio1 = (double)rand() / RAND_MAX * 2 - 1;
        double numero_aleatorio2 = (double)rand() / RAND_MAX * 2 - 1;
        printf("Numero aleatorio entre -1 e 1: %f\n", numero_aleatorio1);
        printf("Numero aleatorio entre -1 e 1: %f\n", numero_aleatorio2);

        // Atribuir os valores aos x e y:
        x = numero_aleatorio1;
        y = numero_aleatorio2;

        if (x*x + y*y < 1){
            areapercentual++;
        }
    }

    // Calculo do pi:
    pi = (double)areapercentual / N * 4;

    printf("O valor aproximado de pi eh: %f", pi);

    return 0;
}
