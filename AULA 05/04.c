#include <stdio.h>
#include <math.h>
#include <locale.h>

void conversao_coordenadas() {
    float x, y, r, angulo; 
    int escolha;

    printf("O que você deseja fazer?\n");
    printf("1 - Coordenadas cartesianas -> coordenadas polares\n");
    printf("2 - Coordenadas polares -> coordenadas cartesianas\n");
    printf("0 - Encerrar.\n");
    printf("Escolha a opção 1 ou 2: ");
    scanf("%d", &escolha);
    
    if (escolha == 1) {
        printf("Digite o valor de x: ");
        scanf("%f", &x);
        printf("Digite o valor de y: ");
        scanf("%f", &y);

        r = sqrt(pow(x, 2) + pow(y, 2)); // Corrigido para usar y ao invés de x
        angulo = atan2(y, x);

        printf("\nO raio das coordenadas x = %.0f e y = %.0f é: %.2f", x, y, r);
        printf("\nO ângulo das coordenadas x = %.0f e y = %.0f é: %.2f radianos", x, y, angulo);
    } else if (escolha == 2) {
        printf("Digite o valor de r: ");
        scanf("%f", &r);
        printf("Digite o valor do ângulo (em radianos): ");
        scanf("%f", &angulo);
        x = r * cos(angulo);
        y = r * sin(angulo);

        printf("\nAs coordenadas cartesianas correspondentes são: x = %.2f e y = %.2f", x, y);
    } else {
        printf("\nO programa foi encerrado.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    conversao_coordenadas(); // Chama a função de conversão
    return 0;
}