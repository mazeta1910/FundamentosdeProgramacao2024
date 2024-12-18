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
    printf("Digite um n�mero inteiro positivo: ");
    scanf("%d", &numero); // Removido o \n do scanf

    // Corrigido o loop para incrementar i corretamente
    for (i = 1; i <= numero; i++) { 
        printf("Deseja adicionar %d a soma (s/n)? ", i);
        scanf(" %c", &opcao);

        // Corrigido o uso do operador de compara��o (==)
        if (opcao == 's' || opcao == 'S') { // Adicionado o { aqui
            soma += i; 
        } else if (opcao == 'n' || opcao == 'N') { // Adicionado o { aqui
            continue; 
        } else {
            printf("Op��o inv�lida!\n");
            i--; // Decrementa i para repeti��o
        }
    }

    switch (soma) { 
        case 0:
            printf("Nenhum n�mero foi adicionado.\n"); 
            break; // break adicionado
        case 1:
            printf("A soma � igual a 1.\n"); 
            break; // break
        default:
            printf("A soma � %d.\n", soma); 
            break; // break
    }

    return 0; // Retorno 0 para indicar que o programa terminou corretamente
}