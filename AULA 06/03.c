#include <stdio.h>

long int fat(int n) {
  if (n == 0) {  // Caso base: fatorial de 0 é 1
    return 1;
  } else {
    return n * fat(n - 1);  // Chamada recursiva
  }
}

int main() {
  int n = 5;
  printf("%ld", fat(n));
  return 0;
}