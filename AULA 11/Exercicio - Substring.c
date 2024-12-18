/*Escreva um c�digo para verificar se uma string est� contida em outra.
Para tanto, utilize os seguintes passos:
1. Defina as duas strings
2. Inicie uma vari�vel temSubstring como Falso
3. Percorra a primeira string buscando o primeiro caractere da segunda
4. Ao encontrar, coloque temSubstring como Verdadeiro, e inicie outro la�o
(aninhado).
4.a. Se o �ndice somado (dos dois la�os) passar tamanho, ent�o
temSubstring = Falso e quebra o la�o.
4.a. Compare caractere a caractere, se s�o iguais
4.b. Se n�o forem, temSubstring = Falso, quebra o la�o interno
5. Se temSubstring for verdadeiro quebra o la�o*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    char str1[100], str2[100];
    int i, j, temSubstring;

    // 1. Defina as duas strings
    printf("Digite a primeira string: ");
    fgets(str1, sizeof(str1), stdin);
    printf("Digite a segunda string: ");
    fgets(str2, sizeof(str2), stdin);

    // Remover o caractere de nova linha, se presente
    str1[strcspn(str1, "\n")] = 0;
    str2[strcspn(str2, "\n")] = 0;

    // 2. Inicie uma vari�vel temSubstring como Falso
    temSubstring = 0;

    // 3. Percorra a primeira string
    for (i = 0; i < strlen(str1); i++) {
        // 4. Verifique se o primeiro caractere da segunda string est� na primeira
        if (str1[i] == str2[0]) {
            temSubstring = 1; // Assume que a substring pode estar presente
            // 4.a. Inicie um la�o aninhado para comparar os caracteres
            for (j = 0; j < strlen(str2); j++) {
                // Se chegarmos ao final da str1 ou os caracteres n�o coincidirem
                if (i + j >= strlen(str1) || str1[i + j] != str2[j]) {
                    temSubstring = 0; // N�o � uma substring
                    break; // Quebra o la�o interno
                }
            }
            // Se o la�o interno n�o quebrou, significa que a substring foi encontrada
            if (temSubstring) {
                printf("A segunda string est� contida na primeira.\n");
                break; // Quebra o la�o externo
            }
        }
    }

    // 5. Se n�o encontrou a substring, informe isso
    if (!temSubstring) {
        printf("A segunda string n�o est� contida na primeira.\n");
    }

    return 0;
}