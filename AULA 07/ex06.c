#include <stdio.h>
#include <locale.h>

#define N 1000000000

int main (){
    setlocale(LC_ALL, "Portuguese");
    float vetor[N];
    int i;
    
    //la�o de inicializa��o
    for (i=0;i<N;i++)
    {
        vetor[i]=(float)i/2;
    }

    //la�o de impress�o
    
    return 0;
}