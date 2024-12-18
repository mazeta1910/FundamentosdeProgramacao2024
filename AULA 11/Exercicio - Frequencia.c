/*Exercício - Frequência
Escreva um código em C que conte a frequência de cada caractere na string, considere os passos:
1. Defina a string no início do código
2. Construa um array freq com 26 posições
3. Coloque 0 em cada elemento do array freq
4. Faça um laço para percorrer a string e somar no freq[c], onde c é a posição do caractere*
5. Faça um laço que percorre o array e procura o maior valor
O índice c pode ser calculado como:
c = string[i] - ?a?;
Porém é preciso ver se c está entre 0 e 26.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Informe a primeira string: ");
    char str1[100];
    fgets(str1, sizeof(str1), stdin);
    
    int freq[26] = {0}; 

    for (int i = 0; i < strlen(str1); i++) {
        char c = str1[i];

        if (c >= 'a' && c <= 'z') {
            int index = c - 'a';
            freq[index]++;
        }
    }
    

    int maxFreq = 0;
    char maxChar = 'a';
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxChar = 'a' + i;
        }
    }
    
    printf("O caractere mais frequente é '%c' com %d ocorrências.\n", maxChar, maxFreq);
    
    return 0;
}