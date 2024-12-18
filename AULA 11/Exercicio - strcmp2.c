#include <stdio.h>
#include <string.h>
#include <locale.h>

/*Escreva um c�digo que realize o mesmo procedimento que o strcmp, por�m sem utilizar a biblioteca.
Considere os passos:
1. Defina as duas strings no in�cio do c�digo.
2. Fa�a um la�o que percorre a primeira e segunda string e verifica se os caracteres s�o iguais.
2.a. Se n�o forem iguais, imprime a diferen�a e quebra o la�o.
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
            printf("As strings n�o s�o iguais.\n");
            printf("A diferen�a est� na posi��o %d.\n", i+1);
            printf("O caractere da string 1 � ''%c'' e o caractere da string 2 � ''%c.''\n", str1[i], str2[i]);
            }
            else
            {
                printf("As strings s�o iguais.\n");
            }

    return 0;
}
