#include <stdio.h>

void mmc(int n, int m, int divisor) {
  if (n == 1 && m == 1) {  // Caso base: MMC encontrado
    return;
  }

  if (n % divisor == 0 && m % divisor == 0) {
    printf("%d\n", divisor);
    mmc(n / divisor, m / divisor, divisor);
  } else {
    mmc(n, m, divisor + 1);
  }
}

int main() {
  mmc(192, 96, 2);  // Começa com o divisor 2
  return 0;
}