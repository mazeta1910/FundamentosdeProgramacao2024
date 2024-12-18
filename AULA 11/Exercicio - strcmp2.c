#include <stdio.h>
#include <string.h>
#include <locale.h>

/*Escreva um código que realize o mesmo procedimento que o strcmp, porém sem utilizar a biblioteca.
Considere os passos:
1. Defina as duas strings no início do código.
2. Faça um laço que percorre a primeira e segunda string e verifica se os caracteres são iguais.
2.a. Se não forem iguais, imprime a diferença e quebra o laço.
Compare os resultados*/

int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("Informe a primeira string: ");
    char str1[100];
    fgets(str1, sizeof(str1), stdin);
    printf("Informe a segunda string: ");
    char str2[100];
    fgets(str2, sizeof(str2), stdin);
    int i = 0;
    int dif = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            dif = 1;
            break;
        }
        i++;
        }
        if (dif == 1)
        {
            printf("As strings não são iguais.\n");
            printf("A diferença está na posição %d.\n", i+1);
            printf("O caractere da string 1 é ''%c'' e o caractere da string 2 é ''%c.''\n", str1[i], str2[i]);
            }
            else
            {
                printf("As strings são iguais.\n");
            }

    return 0;
}
