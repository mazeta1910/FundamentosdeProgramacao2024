/*Dadas as coordenadas de dois pontos no plano cartesiano (x1,y1) e  (x2,y2), calcule a distância euclidiana entre esses pontos. 
A fórmula da distância entre dois pontos deve ser implementada, conforme:  */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    float x1, y1, x2, y2, dist, raiz;
    printf("Coordenadas do primeiro ponto (x1):");
    scanf("%f", &x1);
    printf("Coordenadas do primeiro ponto (y1):");
    scanf("%f", &y1);
    printf("Coordenadas do segundo ponto (x2):");
    scanf("%f", &x2);
    printf("Coordenadas do segundo ponto (y2):");
    scanf("%f", &y2);
    dist = (pow((x1-x2),2))+(pow((y1-y2),2));
    raiz = sqrt(dist);
    printf("A distância entre os pontos é: %.2f", raiz);
    return 0;
}

