/*4.	Crie um programa que gere aleatoriamente um numero inteiro entre 1 e 10. 
Em seguida, o programa deve exibir a tabuada desse numero, de 1 a 10.
	Dicas:
Use a função rand() para gerar o numero aleatÃ³rio entre 1 e 10.
Use um laço for para iterar pelos numeros de 1 a 10.
Dentro do laço, multiplique o numero aleatÃ³rio pelo numero atual do laço e exiba o resultado.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main (){
    int numero_aleatorio, i, resultado;
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    numero_aleatorio = rand() % 10 + 1;
    printf("O numero aleatório gerado foi: %d\n", numero_aleatorio);
    for (i = 1; i<=10; i++){
        resultado = numero_aleatorio*i;
        printf("%d x %d = %d\n", numero_aleatorio, i, resultado);
    }
    return 0;
}

