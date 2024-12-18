#include <stdio.h>

int main(){
int x1, x2, x3, y1, y2, y3;
float base=0, area=0;

    printf("Informe o x1 do triangulo: ");
    scanf("%d", &x1);
    printf("Informe o x2 do triangulo: ");
    scanf("%d", &x2);
    printf("Informe a altura do triangulo: ");
    scanf("%d", &h1);

    base=(x2-x1);
    area=((base*h1)/2);

    printf("A area do triangulo eh: %f \n", area);

    return 0;
}
