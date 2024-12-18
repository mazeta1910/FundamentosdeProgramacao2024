#include <math.h>
#include <stdio.h>
#include <locale.h>

/*Construa uma fun��o que calcula o fatorial de um n�mero de entrada.*/

int fatorial(int N){
    int i;
    int fat = 1;
    for  (i = 1; i <= N; i++){
        fat = fat * i;
    }
    return fat;
}
int main(int argc, char** argv){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int numero, resultado, continuar;
    do{
    printf("Escolha o n�mero que voc� deseja obter o fatorial: ");
    scanf("%d", &numero),
    resultado = fatorial(numero);
    printf("O valor do fatorial �: %d", resultado);
    printf("\nVoc� deseja inserir outro n�mero? (1 - Sim | 2 - N�o): ");
    scanf("%d", &continuar);
    }while(continuar == 1);
    return 0;
}