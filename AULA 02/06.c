#include <stdio.h>

int main(){
    int x, y;
    printf("Digite um valor inteiro para x:\n");
    scanf("%d",&x);
    printf("Digite um valor inteiro para y:\n");
    scanf("%d",&y);

    if (x>y){
        printf("x eh maior que y\n");
    }
    else{
        printf("y eh maior que x\n");
    }
    return 0;
    }
