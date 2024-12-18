#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    char f1[12];
    char f2[12] = "hocus pocus"; // String de compara��o em min�sculas

    do {
        printf("Digite \"Hocus Pocus\" (ignorando mai�sculas e min�sculas):\n");
        fgets(f1, 12, stdin);

        // Remover o caractere de nova linha '\n' do fgets
        f1[strcspn(f1, "\n")] = 0; 

        // Converter a entrada do usu�rio para min�sculas
        for (int i = 0; f1[i] != '\0'; i++) {
            f1[i] = tolower(f1[i]);
        }

    } while (strcmp(f1, f2)); // Comparar com a string em min�sculas

    printf("Frase correta!\n");
    return 0;
}