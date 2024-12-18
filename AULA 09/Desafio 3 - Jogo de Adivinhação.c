/*Escreva um c�digo que tenha uma string e sorteie um n�mero aleat�rio para decidir qual
string copiar usando strcpy. Ap�s isso, o usu�rio tentar� adivinhar a string sorteada,
caso erre, o computador dar� uma dica da solu��o (use a fun��o strcmp), limitando a
cinco rodadas.*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

    int main() {
        setlocale(LC_ALL, "Portuguese");
        srand(time(NULL));
        char str1[] = "Laranja";
        char str2[] = "Ma��";
        char str3[] = "Banana";
        char str4[] = "Pera";
        char str5[] = "Uva";
        char str6[] = "Mel�o";
        char str7[] = "Ameixa";
        char str8[] = "Mirtilo";
        char str9[] = "Goiaba";
        char str10[] = "Cereja";
        char str[100];
        int rodadas = 0;
        int sorteado = rand() % 10 + 1;
        strcpy(str, str10);
        while (rodadas < 5) {
            printf("Qual � a fruta sorteada?\n");
            fgets(str, sizeof(str), stdin);
            if (strcmp(str, str10) == 0) {
                printf("Parab�ns, voc� acertou!\n");
                break;
                } else {
                    printf("Voc� errou! Tente novamente.\n");
                    rodadas++;
                    if (rodadas == 5) {
                        printf("O n�mero sorteado era %d\n", sorteado);
                        printf("A fruta sorteada era %s\n", str10);
                        break;
                        }
                }
        }
        
        return 0;
    }