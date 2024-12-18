#include <stdio.h>
#include <string.h>
int main()
{
 char f1[12];
 int distance;
 do{
 printf("Digite Exatamente \"Hocus Pocus\":\n" );
 fgets(f1, 12, stdin);
 getchar(); //consome o \n
 distance = strcmp(f1,"Hocus Pocus" );
 printf("%s\n", f1);
 if (distance> 0){
 printf("O primeiro caracter diferente em f1 eh maior.\nDistancia: %d\n" , distance);
 }
 else{
 printf("O primeiro caracter diferente em f1 eh menor.\nDistancia: %d\n" , distance);
 }
 } while(strcmp(f1,"Hocus Pocus" ));
 return 0;
}
