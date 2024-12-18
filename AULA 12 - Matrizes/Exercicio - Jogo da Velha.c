/*Exerc�cio - Jogo da Velha
Escreva um c�digo de jogo da velha, onde o computador tamb�m joga;
Para isso, codifique a matriz com 3 s�mbolos:
X, O e vazio*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define o tamanho do tabuleiro
#define TAMANHO 3

// Define os s�mbolos usados no jogo
#define VAZIO ' '
#define JOGADOR_X 'X'
#define JOGADOR_O 'O'

// Fun��o para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
  printf("\n");
  for (int i = 0; i < TAMANHO; i++) {
    for (int j = 0; j < TAMANHO; j++) {
      printf(" %c ", tabuleiro[i][j]);
      if (j < TAMANHO - 1) {
        printf("|");
      }
    }
    printf("\n");
    if (i < TAMANHO - 1) {
      printf("---+---+---\n");
    }
  }
  printf("\n");
}

// Fun��o para verificar se h� um vencedor
char verificarVencedor(char tabuleiro[TAMANHO][TAMANHO]) {
  // Verifica linhas
  for (int i = 0; i < TAMANHO; i++) {
    if (tabuleiro[i][0] != VAZIO && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2]) {
      return tabuleiro[i][0];
    }
  }

  // Verifica colunas
  for (int j = 0; j < TAMANHO; j++) {
    if (tabuleiro[0][j] != VAZIO && tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[0][j] == tabuleiro[2][j]) {
      return tabuleiro[0][j];
    }
  }

  // Verifica diagonais
  if (tabuleiro[0][0] != VAZIO && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2]) {
    return tabuleiro[0][0];
  }
  if (tabuleiro[0][2] != VAZIO && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[0][2] == tabuleiro[2][0]) {
    return tabuleiro[0][2];
  }

  // Nenhum vencedor ainda
  return VAZIO;
}

// Fun��o para verificar se o tabuleiro est� cheio
int tabuleiroCheio(char tabuleiro[TAMANHO][TAMANHO]) {
  for (int i = 0; i < TAMANHO; i++) {
    for (int j = 0; j < TAMANHO; j++) {
      if (tabuleiro[i][j] == VAZIO) {
        return 0; // Ainda h� espa�os vazios
      }
    }
  }
  return 1; // Tabuleiro cheio
}

int main() {
  // Inicializa o tabuleiro com espa�os vazios
  char tabuleiro[TAMANHO][TAMANHO] = {{VAZIO, VAZIO, VAZIO},
                                     {VAZIO, VAZIO, VAZIO},
                                     {VAZIO, VAZIO, VAZIO}};

  // Define quem come�a jogando
  char jogadorAtual = JOGADOR_X;

  // Loop principal do jogo
  while (1) {
    // Imprime o tabuleiro
    imprimirTabuleiro(tabuleiro);

    // Vez do jogador
    int linha, coluna;
    printf("Jogador %c, sua vez! Informe a linha e a coluna (1-3): ", jogadorAtual);
    scanf("%d %d", &linha, &coluna);

    // Ajusta os valores para o �ndice da matriz (0-2)
    linha--;
    coluna--;

    // Valida a jogada
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO || tabuleiro[linha][coluna] != VAZIO) {
      printf("Jogada inv�lida! Tente novamente.\n");
      continue;
    }

    // Realiza a jogada
    tabuleiro[linha][coluna] = jogadorAtual;

    // Verifica se h� um vencedor
    char vencedor = verificarVencedor(tabuleiro);
    if (vencedor != VAZIO) {
      imprimirTabuleiro(tabuleiro);
      printf("Jogador %c venceu!\n", vencedor);
      break;
    }

    // Verifica se o jogo empatou
    if (tabuleiroCheio(tabuleiro)) {
      imprimirTabuleiro(tabuleiro);
      printf("Empate!\n");
      break;
    }

    // Alterna para o pr�ximo jogador
    jogadorAtual = (jogadorAtual == JOGADOR_X) ? JOGADOR_O : JOGADOR_X;
  }

  return 0;
}