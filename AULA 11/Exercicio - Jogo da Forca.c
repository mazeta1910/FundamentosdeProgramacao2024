#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    char palavra[100], letra, palavra_adivinhada[100];
    int i, erro = 0, tamanho_palavra, letras_acertadas = 0;
    
    printf("Digite uma palavra para ser adivinhada: ");
    fgets(palavra, 100, stdin); // Usando fgets para evitar problemas com gets

    tamanho_palavra = strlen(palavra);
    
    // Remover o caractere de nova linha '\n' que o fgets pode adicionar
    if (palavra[tamanho_palavra - 1] == '\n') {
        palavra[tamanho_palavra - 1] = '\0';
        tamanho_palavra--;
    }

    for (i = 0; i < tamanho_palavra; i++) {
        palavra_adivinhada[i] = '_';
    }
    palavra_adivinhada[tamanho_palavra] = '\0'; // Adicionando o terminador de string

    while (erro < 4 && letras_acertadas < tamanho_palavra) {
        printf("\nPalavra adivinhada: %s\n", palavra_adivinhada);
        printf("Digite uma letra: ");
        scanf(" %c", &letra); // Lendo a letra com scanf
        letra = tolower(letra);

        if (!isalpha(letra)) {
            printf("Entrada inválida. Digite uma letra.\n");
            continue; 
        }

        int letra_encontrada = 0; 
        for (i = 0; i < tamanho_palavra; i++) {
            if (palavra[i] == letra && palavra_adivinhada[i] == '_') {
                palavra_adivinhada[i] = letra;
                letras_acertadas++;
                letra_encontrada = 1; 
            }
        }

        if (!letra_encontrada) {
            erro++;
            printf("Letra incorreta. Você tem mais %d tentativas.\n", 4 - erro);
        }
    }

    if (letras_acertadas == tamanho_palavra) {
        printf("\nVitória! A palavra era %s.\n", palavra);
    } else {
        printf("\nDerrota! A palavra era %s.\n", palavra);
    }

    return 0;
}