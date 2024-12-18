/*Construa um c�digo que contenha um array com 2048 n�meros aleat�rios entre 0 e 1 em um ponto flutuante e calcule  m�dia e desvio padr�o*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");
    float vet[2048], media=0.0, desvio_padrao=0.0, soma = 0,
    aux;
    int i, n = 2048;
    for (i = 0; i < n; i++) {
        vet[i] = (float)rand() / RAND_MAX;
        soma += vet[i];
        }
        media = soma / n;
        for (i = 0; i < n; i++) {
            aux = vet[i] - media;
            desvio_padrao += pow(aux, 2);
            }
            desvio_padrao = sqrt(desvio_padrao / n);
            printf("M�dia: %.6f\n", media);
            printf("Desvio Padr�o: %.6f\n", desvio_padrao);
            
            return 0;
            }  
