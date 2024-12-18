/*Escreva um código que tenha uma string e sorteie um número aleatório para decidir qual
string copiar usando strcpy. Após isso, o usuário tentará adivinhar a string sorteada,
caso erre, o computador dará uma dica da solução (use a função strcmp), limitando a
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
        char str2[] = "Maçã";
        char str3[] = "Banana";
        char str4[] = "Pera";
        char str5[] = "Uva";
        char str6[] = "Melão";
        char str7[] = "Ameixa";
        char str8[] = "Mirtilo";
        char str9[] = "Goiaba";
        char str10[] = "Cereja";
        char str[100];
        int rodadas = 0;
        int sorteado = rand() % 10 + 1;
        strcpy(str, str10);
        while (rodadas < 5) {
            printf("Qual é a fruta sorteada?\n");
            fgets(str, sizeof(str), stdin);
            if (strcmp(str, str10) == 0) {
                printf("Parabéns, você acertou!\n");
                break;
                } else {
                    printf("Você errou! Tente novamente.\n");
                    rodadas++;
                    if (rodadas == 5) {
                        printf("O número sorteado era %d\n", sorteado);
                        printf("A fruta sorteada era %s\n", str10);
                        break;
                        }
                }
        }
        
        return 0;
    }