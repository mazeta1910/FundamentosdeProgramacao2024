#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    char f1[12];
    char f2[12] = "hocus pocus"; // String de comparação em minúsculas

    do {
        printf("Digite \"Hocus Pocus\" (ignorando maiúsculas e minúsculas):\n");
        fgets(f1, 12, stdin);

        // Remover o caractere de nova linha '\n' do fgets
        f1[strcspn(f1, "\n")] = 0; 

        // Converter a entrada do usuário para minúsculas
        for (int i = 0; f1[i] != '\0'; i++) {
            f1[i] = tolower(f1[i]);
        }

    } while (strcmp(f1, f2)); // Comparar com a string em minúsculas

    printf("Frase correta!\n");
    return 0;
}