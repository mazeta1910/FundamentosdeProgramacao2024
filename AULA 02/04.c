#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Semente para o gerador de n�meros aleat�rios
    int n;
    int m = 10000;
    float f;
    srand(time(NULL));
    n = rand();
    n = n%m;
    f = (float) n;
    f = f/(float)m;
    f = f-0.5;
    f = f/0.5;

    printf("%f\n", f);
    return 0;

    // Gera um n�mero aleat�rio entre 0 e 1

}