#include <math.h>
#include <stdio.h>
#include <locale.h>

/*Construa uma função que calcula o fatorial de um número de entrada.*/

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
    printf("Escolha o número que você deseja obter o fatorial: ");
    scanf("%d", &numero),
    resultado = fatorial(numero);
    printf("O valor do fatorial é: %d", resultado);
    printf("\nVocê deseja inserir outro número? (1 - Sim | 2 - Não): ");
    scanf("%d", &continuar);
    }while(continuar == 1);
    return 0;
}