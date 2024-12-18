/*Contar palavras
Escreva um código C para contar o número de palavras em uma string.*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    char str[100];
    int i, cont = 1;

    printf("Digite uma frase: ");
    fgets(str, 100, stdin);

    for(i = 0; i < strlen(str); i++){
        if(str[i] == ' '){
            cont++;
        }
    }

    printf("A frase tem %d palavras", cont);

    return 0;
}