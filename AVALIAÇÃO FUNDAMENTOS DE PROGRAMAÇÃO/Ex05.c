#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>

// Incluindo as bibliotecas

int main() { // Corrigido para int main() e adicionado return 0;
    int numero, i, soma = 0;
    setlocale(LC_ALL, "Portuguese");
    char opcao; // Alterado para char pois estamos lidando com caracteres
    printf("Digite um número inteiro positivo: ");
    scanf("%d", &numero); // Removido o \n do scanf

    // Corrigido o loop para incrementar i corretamente
    for (i = 1; i <= numero; i++) { 
        printf("Deseja adicionar %d a soma (s/n)? ", i);
        scanf(" %c", &opcao);

        // Corrigido o uso do operador de comparação (==)
        if (opcao == 's' || opcao == 'S') { // Adicionado o { aqui
            soma += i; 
        } else if (opcao == 'n' || opcao == 'N') { // Adicionado o { aqui
            continue; 
        } else {
            printf("Opção inválida!\n");
            i--; // Decrementa i para repetição
        }
    }

    switch (soma) { 
        case 0:
            printf("Nenhum número foi adicionado.\n"); 
            break; // break adicionado
        case 1:
            printf("A soma é igual a 1.\n"); 
            break; // break
        default:
            printf("A soma é %d.\n", soma); 
            break; // break
    }

    return 0; // Retorno 0 para indicar que o programa terminou corretamente
}