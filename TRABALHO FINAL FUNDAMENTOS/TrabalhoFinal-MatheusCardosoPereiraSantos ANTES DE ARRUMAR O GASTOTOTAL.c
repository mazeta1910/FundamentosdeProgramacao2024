#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

//Função para calcular a % do orçamento total que já foi gasto
float calculoPorcentagemOrcGasto(float orcamentoTotal, float gastoAtual){
  if (orcamentoTotal <= 0) {
    printf("Erro: O orçamento total não pode ser igual ou menor que zero.\n");
    return -1;
    }
    return (gastoAtual/orcamentoTotal)*100;

}

// Função para calcular a % do orçamento gasto com os funcionários
float calculoOrcamentoFuncionarios(float orcamentoTotal, float gastoSalarios){
  if (orcamentoTotal <= 0) {
    printf("Erro: O orçamento total não pode ser igual ou menor que zero.\n");
    return -1;
    }
    return (gastoSalarios/orcamentoTotal)*100;

}

// Função para calcular a diferença em dias entre duas datas
int calcularDuracao(const char *dataInicio, const char *dataTermino) {
    struct tm tmInicio, tmTermino;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));

    // Converte as strings de data para o tipo struct tm
    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o mês (0-11)
    tmInicio.tm_year -= 1900;  // Ajusta o ano (anos desde 1900)
    tmTermino.tm_mon -= 1;
    tmTermino.tm_year -= 1900;

    // Converte as datas para segundos desde 1 de janeiro de 1970
    time_t tempoInicio = mktime(&tmInicio);
    time_t tempoTermino = mktime(&tmTermino);

    // Calcula a diferença em segundos e converte para dias
    double diffSegundos = difftime(tempoTermino, tempoInicio);
    int diffDias = (int)(diffSegundos / (60 * 60 * 24));

    return diffDias;
}

// Função para calcular o tempo da obra
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

// Função para validar uma data no formato dd/mm/aaaa
int validarData(const char *data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; // Formato inválido
    }
    if (ano < 1900 || ano > 2100) {
        return 0; // Ano inválido
    }
    if (mes < 1 || mes > 12) {
        return 0; // Mês inválido
    }
    if (dia < 1 || dia > 31) {
        return 0; // Dia inválido
    }
    // Verificar dias específicos de cada mês (fevereiro, abril, junho, setembro, novembro)
    if ((mes == 2 && dia > 29) || ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31)) {
        return 0; // Dia inválido para o mês
    }

    // Verificar se o ano é bissexto
    int ehBissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));

    if (mes == 2 && dia > 28 && !ehBissexto) {
        return 0; // Dia inválido para fevereiro em ano não bissexto
    }

    return 1; // Data válida
}

//Função para gerar o relatório
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    fprintf(arquivo, "\n=== Relatório da Obra ===\n");
    printf("\n=== Relatório da Obra ===\n");

    fprintf(arquivo, "Nome da obra: %s\n", nomeObra);
    printf("Nome da obra: %s\n", nomeObra);

    fprintf(arquivo, "Data de início: %s\n", dataInicio);
    printf("Data de início: %s\n", dataInicio);

    fprintf(arquivo, "Data de término: %s\n", dataTermino);
    printf("Data de término prevista: %s\n", dataTermino);

    fprintf(arquivo, "Dias de obra: %d\n", diasPassados);
    printf("Dias de obra: %d\n", diasPassados);

    fprintf(arquivo, "Tempo restante para conclusão: %d\n", diasRestantes);
    printf("Tempo restante para conclusão: %d\n", diasRestantes);

    fprintf(arquivo, "Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    fprintf(arquivo, "Responsável técnico: %s\n", responsavel);
    printf("Responsável técnico: %s\n", responsavel);

    fprintf(arquivo, "Orçamento total: R$ %.2f\n", orcamentoTotal);
    printf("Orçamento total: R$ %.2f\n", orcamentoTotal);

    fprintf(arquivo, "Despesas acumuladas: R$ %.2f\n", gastoAtual);
    printf("Despesas acumuladas: R$ %.2f\n", gastoAtual);

    fprintf(arquivo, "Verba restante: R$ %.2f\n", orcamentoRestante);
    printf("Verba restante: R$ %.2f\n", orcamentoRestante);

    if (pctGasto >= 0) {
        fprintf(arquivo, "Percentual do orçamento gasto: %.2f%%\n", pctGasto);
        printf("Percentual do orçamento gasto: %.2f%%\n", pctGasto);
    } else {
        fprintf(arquivo, "Orçamento total inválido!\n");
        printf("Orçamento total inválido!\n");
    }

    fprintf(arquivo, "Mestre de obras: %s\n", mestredeObras);
    printf("Mestre de obras: %s\n", mestredeObras);

    fprintf(arquivo, "Gasto total com salário de funcionários: R$ %.2f\n", salarioTotal);
    printf("Gasto total com salário de funcionários: R$ %.2f\n", salarioTotal);

    fprintf(arquivo, "Porcentagem do orçamento gasto com salários: %.2f%%\n", pctOrcGastoFuncionarios);
    printf("Porcentagem do orçamento gasto com salários: %.2f%%\n", pctOrcGastoFuncionarios);

    printf("Fase da obra: ");
    switch (faseObra) {
        case 1: printf("Início\n"); break;
        case 2: printf("Fundação\n"); break;
        case 3: printf("Estrutura\n"); break;
        case 4: printf("Acabamento\n"); break;
        case 5: printf("Conclusão\n"); break;
        default: printf("Fase inválida\n");
    }
}

//Função para ler e validar uma data:
void lerData(const char *mensagem, char *data) {
    do {
        printf("%s (dd/mm/aaaa): ", mensagem);
        scanf("%s", data);
        if (!validarData(data)) {
            printf("Data inválida. Digite novamente!\n");
        }
    } while (!validarData(data));
}

// Função main(0)
int main() {
    // Configuração para o idioma português
    setlocale(LC_ALL, "Portuguese");

    // Salva as informações em um arquivo .txt
    FILE *arquivo = fopen("relatorio_obra.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

// Definindo as variáveis
char nomeObra[100];
char dataInicio[11]; 
char dataTermino[11];
char responsavel[100];
char mestredeObras[100];
char dataAtual[11];
int faseObra, qtdFuncionarios, diasPassados, diasRestantes;
float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

// Coletando as informações
printf("=== Gerador de Relatório de Obra ===\n");
printf("Digite o nome da obra: ");
scanf(" %[^\n]", nomeObra); // Lendo a string com espaços em branco. 

// Usando a função lerData para as datas
lerData("Digite a data de início", dataInicio);
lerData("Digite a data de término prevista", dataTermino);
lerData("Digite a data atual", dataAtual);

// Entrada e validação do orçamento total: 
do {
    printf("Digite o orçamento total da obra: R$");
    scanf("%f", &orcamentoTotal);
    if (orcamentoTotal <= 0) {
        printf("O orçamento total deve ser maior que zero. Digite novamente!\n");
    }
    } while (orcamentoTotal<=0);

//Entrada e validação do gasto atual: 
do {
  printf("Digite o valor já gasto na obra: R$");
  scanf("%f", &gastoAtual);
  if (gastoAtual < 0 || gastoAtual > orcamentoTotal) {
      printf("Gasto inválido! Digite um valor entre 0 e o orçamento total.\n");
}
} while(gastoAtual < 0 || gastoAtual > orcamentoTotal);

printf("Informe o nome do mestre de obras responsável: ");
scanf(" %[^\n]", mestredeObras); 

printf("Informe quantos funcionários estão trabalhando na obra: ");
scanf("%d", &qtdFuncionarios);

printf("Informe o salário desses funcionários: R$");
scanf("%f", &salarioFuncionarios);

printf("Digite o nome do responsável técnico: ");
scanf(" %[^\n]", responsavel);

//Entrada e validação da fase da obra:
do {
    printf("Digite a fase atual da obra (1-Início, 2-Fundação, 3-Estrutura, 4-Acabamento, 5-Conclusão): ");
    scanf("%d", &faseObra);
    if(faseObra < 1 || faseObra > 5) {
      printf("Fase inválida! Digite uma fase entre 1 e 5.\n");
      }
    } while (faseObra < 1 || faseObra > 5);

//Cálculo do tempo da obra:
calcularTempoObra(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

//Cálculos do orçamento:
float salarioTotal = qtdFuncionarios*salarioFuncionarios;
pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);
pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);
float orcamentoRestante = orcamentoTotal-gastoAtual;

//Chamando a função gerarRelatorio
gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

fclose(arquivo);

return 0;
}