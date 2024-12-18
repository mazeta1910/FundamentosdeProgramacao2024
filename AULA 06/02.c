#include <stdio.h>
int somaAteN(int n){
 int i = 0;
 int acc = 0;
 for(i=0;i<n+1;i++)
 acc = acc + i;
 return acc;
}
int main(){
 printf("%d",somaAteN(100));
}