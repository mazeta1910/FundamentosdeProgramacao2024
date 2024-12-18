/*Construa um código que contenha um array com 2048 números aleatórios entre 0 e 1 em um ponto flutuante e calcule  média e desvio padrão*/

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
            printf("Média: %.6f\n", media);
            printf("Desvio Padrão: %.6f\n", desvio_padrao);
            
            return 0;
            }  
