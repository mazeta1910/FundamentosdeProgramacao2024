#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

//Fun��o para calcular a % do or�amento total que j� foi gasto
float calculoPorcentagemOrcGasto(float orcamentoTotal, float gastoAtual){
  if (orcamentoTotal <= 0) {
    printf("Erro: O or�amento total n�o pode ser igual ou menor que zero.\n");
    return -1;
    }
    return (gastoAtual/orcamentoTotal)*100;

}

// Fun��o para calcular a % do or�amento gasto com os funcion�rios
float calculoOrcamentoFuncionarios(float orcamentoTotal, float gastoSalarios){
  if (orcamentoTotal <= 0) {
    printf("Erro: O or�amento total n�o pode ser igual ou menor que zero.\n");
    return -1;
    }
    return (gastoSalarios/orcamentoTotal)*100;

}

// Fun��o para calcular a diferen�a em dias entre duas datas
int calcularDuracao(const char *dataInicio, const char *dataTermino) {
    struct tm tmInicio, tmTermino;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));

    // Converte as strings de data para o tipo struct tm
    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o m�s (0-11)
    tmInicio.tm_year -= 1900;  // Ajusta o ano (anos desde 1900)
    tmTermino.tm_mon -= 1;
    tmTermino.tm_year -= 1900;

    // Converte as datas para segundos desde 1 de janeiro de 1970
    time_t tempoInicio = mktime(&tmInicio);
    time_t tempoTermino = mktime(&tmTermino);

    // Calcula a diferen�a em segundos e converte para dias
    double diffSegundos = difftime(tempoTermino, tempoInicio);
    int diffDias = (int)(diffSegundos / (60 * 60 * 24));

    return diffDias;
}

// Fun��o para calcular o tempo da obra
void calcularTempoObra(const char *dataInicio, const char *dataTermino, const char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    *diasPassados = calcularDuracao(dataInicio, dataAtual);
    *diasRestantes = calcularDuracao(dataAtual, dataTermino);

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal > 0) {
        *percentualPassado = (*diasPassados * 100.0f) / duracaoTotal;
    } else {
        *percentualPassado = 0.0f;
    }
}

// Fun��o para validar uma data no formato dd/mm/aaaa
int validarData(const char *data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; // Formato inv�lido
    }
    if (ano < 1900 || ano > 2100) {
        return 0; // Ano inv�lido
    }
    if (mes < 1 || mes > 12) {
        return 0; // M�s inv�lido
    }
    if (dia < 1 || dia > 31) {
        return 0; // Dia inv�lido
    }
    // Verificar dias espec�ficos de cada m�s (fevereiro, abril, junho, setembro, novembro)
    if ((mes == 2 && dia > 29) || ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31)) {
        return 0; // Dia inv�lido para o m�s
    }

    // Verificar se o ano � bissexto
    int ehBissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));

    if (mes == 2 && dia > 28 && !ehBissexto) {
        return 0; // Dia inv�lido para fevereiro em ano n�o bissexto
    }

    return 1; // Data v�lida
}

//Fun��o para gerar o relat�rio
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    fprintf(arquivo, "\n=== Relat�rio da Obra ===\n");
    printf("\n=== Relat�rio da Obra ===\n");

    fprintf(arquivo, "Nome da obra: %s\n", nomeObra);
    printf("Nome da obra: %s\n", nomeObra);

    fprintf(arquivo, "Data de in�cio: %s\n", dataInicio);
    printf("Data de in�cio: %s\n", dataInicio);

    fprintf(arquivo, "Data de t�rmino: %s\n", dataTermino);
    printf("Data de t�rmino prevista: %s\n", dataTermino);

    fprintf(arquivo, "Dias de obra: %d\n", diasPassados);
    printf("Dias de obra: %d\n", diasPassados);

    fprintf(arquivo, "Tempo restante para conclus�o: %d\n", diasRestantes);
    printf("Tempo restante para conclus�o: %d\n", diasRestantes);

    fprintf(arquivo, "Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    fprintf(arquivo, "Respons�vel t�cnico: %s\n", responsavel);
    printf("Respons�vel t�cnico: %s\n", responsavel);

    fprintf(arquivo, "Or�amento total: R$ %.2f\n", orcamentoTotal);
    printf("Or�amento total: R$ %.2f\n", orcamentoTotal);

    fprintf(arquivo, "Despesas acumuladas: R$ %.2f\n", gastoAtual);
    printf("Despesas acumuladas: R$ %.2f\n", gastoAtual);

    fprintf(arquivo, "Verba restante: R$ %.2f\n", orcamentoRestante);
    printf("Verba restante: R$ %.2f\n", orcamentoRestante);

    if (pctGasto >= 0) {
        fprintf(arquivo, "Percentual do or�amento gasto: %.2f%%\n", pctGasto);
        printf("Percentual do or�amento gasto: %.2f%%\n", pctGasto);
    } else {
        fprintf(arquivo, "Or�amento total inv�lido!\n");
        printf("Or�amento total inv�lido!\n");
    }

    fprintf(arquivo, "Mestre de obras: %s\n", mestredeObras);
    printf("Mestre de obras: %s\n", mestredeObras);

    fprintf(arquivo, "Gasto total com sal�rio de funcion�rios: R$ %.2f\n", salarioTotal);
    printf("Gasto total com sal�rio de funcion�rios: R$ %.2f\n", salarioTotal);

    fprintf(arquivo, "Porcentagem do or�amento gasto com sal�rios: %.2f%%\n", pctOrcGastoFuncionarios);
    printf("Porcentagem do or�amento gasto com sal�rios: %.2f%%\n", pctOrcGastoFuncionarios);

    printf("Fase da obra: ");
    switch (faseObra) {
        case 1: printf("In�cio\n"); break;
        case 2: printf("Funda��o\n"); break;
        case 3: printf("Estrutura\n"); break;
        case 4: printf("Acabamento\n"); break;
        case 5: printf("Conclus�o\n"); break;
        default: printf("Fase inv�lida\n");
    }
}

//Fun��o para ler e validar uma data:
void lerData(const char *mensagem, char *data) {
    do {
        printf("%s (dd/mm/aaaa): ", mensagem);
        scanf("%s", data);
        if (!validarData(data)) {
            printf("Data inv�lida. Digite novamente!\n");
        }
    } while (!validarData(data));
}

// Fun��o main(0)
int main() {
    // Configura��o para o idioma portugu�s
    setlocale(LC_ALL, "Portuguese");

    // Salva as informa��es em um arquivo .txt
    FILE *arquivo = fopen("relatorio_obra.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

// Definindo as vari�veis
char nomeObra[100];
char dataInicio[11]; 
char dataTermino[11];
char responsavel[100];
char mestredeObras[100];
char dataAtual[11];
int faseObra, qtdFuncionarios, diasPassados, diasRestantes;
float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

// Coletando as informa��es
printf("=== Gerador de Relat�rio de Obra ===\n");
printf("Digite o nome da obra: ");
scanf(" %[^\n]", nomeObra); // Lendo a string com espa�os em branco. 

// Usando a fun��o lerData para as datas
lerData("Digite a data de in�cio", dataInicio);
lerData("Digite a data de t�rmino prevista", dataTermino);
lerData("Digite a data atual", dataAtual);

// Entrada e valida��o do or�amento total: 
do {
    printf("Digite o or�amento total da obra: R$");
    scanf("%f", &orcamentoTotal);
    if (orcamentoTotal <= 0) {
        printf("O or�amento total deve ser maior que zero. Digite novamente!\n");
    }
    } while (orcamentoTotal<=0);

//Entrada e valida��o do gasto atual: 
do {
  printf("Digite o valor j� gasto na obra: R$");
  scanf("%f", &gastoAtual);
  if (gastoAtual < 0 || gastoAtual > orcamentoTotal) {
      printf("Gasto inv�lido! Digite um valor entre 0 e o or�amento total.\n");
}
} while(gastoAtual < 0 || gastoAtual > orcamentoTotal);

printf("Informe o nome do mestre de obras respons�vel: ");
scanf(" %[^\n]", mestredeObras); 

printf("Informe quantos funcion�rios est�o trabalhando na obra: ");
scanf("%d", &qtdFuncionarios);

printf("Informe o sal�rio desses funcion�rios: R$");
scanf("%f", &salarioFuncionarios);

printf("Digite o nome do respons�vel t�cnico: ");
scanf(" %[^\n]", responsavel);

//Entrada e valida��o da fase da obra:
do {
    printf("Digite a fase atual da obra (1-In�cio, 2-Funda��o, 3-Estrutura, 4-Acabamento, 5-Conclus�o): ");
    scanf("%d", &faseObra);
    if(faseObra < 1 || faseObra > 5) {
      printf("Fase inv�lida! Digite uma fase entre 1 e 5.\n");
      }
    } while (faseObra < 1 || faseObra > 5);

//C�lculo do tempo da obra:
calcularTempoObra(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

//C�lculos do or�amento:
float salarioTotal = qtdFuncionarios*salarioFuncionarios;
pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);
pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);
float orcamentoRestante = orcamentoTotal-gastoAtual;

//Chamando a fun��o gerarRelatorio
gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

fclose(arquivo);

return 0;
}