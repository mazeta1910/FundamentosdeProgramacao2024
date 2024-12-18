/*Ponto mais próximo
Dada uma sequência de pontos, uma matriz Nx2, onde N representa o número de pontos e 2
as coordenadas (x e y), calcule qual é o ponto mais próximo de um novo ponto (x,y).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    float m[4][2]={{5,10},{12,3},{4,9},{7,15}};
    float p[2]={5,5};
    float d, minD=INFINITY;
    int indice=0;
    int i;
    for (i=0;i<4;i++){
        d = powf(m[i][0]-p[0],2.0)+powf(m[i][1]-p[1], 2.0);
        float draiz = sqrtf(d);
        printf("%f\n", draiz);
        if (draiz<minD){
            minD=draiz;
            indice=i;
        }
        printf("A menor distância é: %f no ponto %d\n", minD, indice);
    }
    return 0;
}
