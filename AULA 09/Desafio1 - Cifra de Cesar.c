#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/*Construa um c�digo que codifique um array de acordo com a Cifra de C�sar
e decodifique. O pseudoc�digo para codificar �:
defina tamanho = 20
declare msg = ?mensagem de exemplo?
declare i
declare senha = 3
Para i de 0 at� tamanho, fa�a:
Se i entre ?a? e ?z?, ent�o fa�a:
msg[i] = ( (int) (msg[i]-?a?)+senha) %26 + ?a?
fim Se
fim Para*/

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char mensagem[20] = "mensagem de exemplo";
    int tamanho = strlen(mensagem);
    int senha = 3;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (mensagem[i] >= 'a' && mensagem[i] <= 'z') {
            mensagem[i] = ((int) (mensagem[i] - 'a') + senha) %
            26 + 'a';
            }
            }
            printf("%s\n", mensagem);
            \
            /*Decodifica��o*/
            for (i = 0; i < tamanho; i++) {
                if (mensagem[i] >= 'a' && mensagem[i] <= 'z') {
                    mensagem[i] = ((int) (mensagem[i] - 'a') - senha) %
                    26 + 'a';
                    }
                    }
                    printf("%s\n", mensagem);

                    return 0;

                    }