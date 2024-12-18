
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    char frase[100];
    int i, contAlfabeto = 0, contVogais = 0, contConsoantes = 0, contEspaco = 0;
    printf("Digite uma frase: ");
    gets(frase);
    for(i = 0; i < strlen(frase); i++){
        if((frase[i] >= 'a' && frase[i] <= 'z') || (frase[i] >= 'A' && frase[i] <= 'Z')){
            contAlfabeto++;
            if(frase[i] == 'a' || frase[i] == 'e' || frase[i] == 'i' || frase[i] == 'o' || frase[i] == 'u' || frase[i] == 'A' || frase[i] == 'E' || frase[i] == 'I' || frase[i] == 'O' || frase[i] == 'U'){
                contVogais++;
            }else{
                contConsoantes++;
            }
        }else if(frase[i] == ' '){
            contEspaco++;
        }
    }
    printf("Número de caracteres alfabéticos: %d\n", contAlfabeto);
    printf("Número de vogais: %d\n", contVogais);
    printf("Número de consoantes: %d\n", contConsoantes);
    printf("Número de espaços: %d\n", contEspaco);
    printf("Primeira palavra: ");
    for(i = 0; i < strlen(frase); i++){
        if(frase[i] == ' '){
            break;
        }
        printf("%c", frase[i]);
    }
    return 0;
}