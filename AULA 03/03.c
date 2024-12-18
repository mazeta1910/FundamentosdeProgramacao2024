/*Um circuito simples tem uma bateria e duas resistência em série.
Calcule a corrente que flui pelo circuito usando a Lei de Ohm. Considere como entrada os dois valores de
resistência e a tensão de uma bateria, imprima a corrente.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main(){
    float resistencia1, resistencia2, tensao;
    int tipo;
    setlocale(LC_ALL, "pt_BR.UTF-8"); 
    
    do {
        printf("Informe o tipo da resistencia.\n0 - Em serie\n1 - Paralelo\n");
        scanf("%d", &tipo);
        if (tipo != 0 && tipo != 1){
            printf("Tipo inválido, tente novamente.\n");
        };
    }while(tipo != 0 && tipo != 1);
    if (tipo == 0 || tipo == 1){

        if (tipo == 0){
            printf("Insira o valor da R1: ");
            scanf("%f", &resistencia1);
            printf("Insira o valor da R2: ");
            scanf("%f", &resistencia2);
            printf("Insira o valor da tensao: ");
            scanf("%f", &tensao);
            float restot=resistencia1+resistencia2;
            printf("\nU = R*i\n");
            printf("\nU = %.0f * %0.f\n", restot, tensao);
            float U = restot*tensao;
            printf("U = %.0f", U);
        }
        else if (tipo == 1){
            printf("Insira o valor da R1: ");
            scanf("%f", &resistencia1);
            printf("Insira o valor da R2: ");
            scanf("%f", &resistencia2);
            printf("Insira o valor da tensao: ");
            scanf("%f", &tensao);
            float restot1=((resistencia1*resistencia2)/(resistencia1+resistencia2));
            printf("U = %.0f\n", restot1);
        }
    }

    return 0;
}