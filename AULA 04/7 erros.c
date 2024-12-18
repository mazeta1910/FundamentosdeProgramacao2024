#include <stdio.h>
    int main() {
    int temperatura, umidade;
    while(true){
    printf("Digite a temperatura (em graus Celsius): ");
    scanf("%f", temperatura);
    printf("Digite a umidade (em porcentagem): ");
    scanf("%f", &umidade);
    if (temperatura >= 20 && temperatura <= 25 && umidade >= 40 && umidde <= 60) {
        printf("Ambiente em condicoes normais.\n");
        continue;
    } else {
    if (temperatura < 20) {
        printf("Temperatura baixa!\n");
    else if (temperatura > 25) {
        printf("Temperatura alta!\n");
    }
    if (umidade < 40) {
        printf("Umidade baixa!\n");
    } else if (umidade > 60) {
        printf("Umidade alta!\n")
    }
    if ((temperatura < 20 || temperatura > 25) && (umidade < 40 || umidade > 60)) {
        printf("Ambiente em estado critico!\n");
}
}
}
    return 0;
}
    }
