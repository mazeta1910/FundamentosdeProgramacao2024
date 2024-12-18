#include <stdio.h>
#include <locale.h>

#define N 5000

int main (){
    setlocale(LC_ALL, "Portuguese");
    float vetor[N];
    int i;
    
    //laço de inicialização
    for (i=0;i<N;i++)
    {
        vetor[i]=(float)i/2;
    }

    //laço de impressão
    for (i=0;i<N;i++){
        printf("O elemento %d contém: %.2f\n", i, vetor);
    }
    
    return 0;
}