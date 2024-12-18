/*Modifique o código, para funcionar independente de um texto estar em caixa alta, caixa baixa ou
misturado

#include <stdio.h>
#include <string.h>
int main()
{
 char f1[12];
 do{
 printf("Digite Exatamente \"Hocus Pocus\":\n" );
 fgets(f1, 12, stdin);
 } while(strcmp(f1,"Hocus Pocus" ));
 return 0;
}

*/

int main(){
    char f1[12];
    do{
        printf("Digite Exatamente \"Hocus Pocus\":\n" );
        fgets(f1, 12, stdin);
        // Convertendo para caixa baixa
        for(int i = 0; i < strlen(f1); i++){
            f1[i] = tolower(f1[i]);
            }


}