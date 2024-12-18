#include <stdio.h>

#ifdef _WIN32
#define TIPO int
#elif __linux__
#define TIPO float
#else
#define TIPO int  // Padrão para outros sistemas
#endif

int main() {
  TIPO variavel = (TIPO)5;

#ifdef _WIN32
  printf("%d\n", variavel);  // Imprime como inteiro em Windows
#elif __linux__
  printf("%.1f\n", variavel);  // Imprime como float com uma casa decimal em Linux
#else
  printf("%d\n", variavel);  // Imprime como inteiro por padrão
#endif

  return 0;
}