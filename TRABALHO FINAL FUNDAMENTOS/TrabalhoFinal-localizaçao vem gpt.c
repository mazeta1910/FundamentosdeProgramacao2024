#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

// Constantes
#define MAX_RESPONSAVEIS 10
#define MAX_NOME 100
#define MAX_OBRA_NOME 100
#define MAX_DATA 11
#define UF_COUNT 27
#define ORCAMENTO_MINIMO 0.0

// Estruturas
typedef struct {
    char nome[MAX_NOME];
    char numeroCREA[20];
    char email[MAX_NOME];
    char telefone[MAX_NOME];
} ResponsavelTecnico;

typedef struct {
    char nomeObra[MAX_OBRA_NOME];
    char mestreObras[MAX_NOME];
} InformacoesObra;

typedef struct {
    char dataInicio[MAX_DATA];
    char dataTermino[MAX_DATA];
    char dataAtual[MAX_DATA];
    int diasPassados;
    int diasAtraso;
    int diasRestantes;
    float pctPassado;
} DatasObra;

typedef struct {
    float orcamentoTotal;
    float gastoAtual;
    float orcamentoRestante;
    float pctGasto;
} InformacoesFinanceiras;

// Funções auxiliares
void limparString(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

bool validarData(const char *data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) return false;
    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12 || dia < 1 || dia > 31) return false;

    // Validação para meses com menos de 31 dias
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) return false;
    } else if (mes == 2) {
        bool bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        if (dia > (bissexto ? 29 : 28)) return false;
    }
    return true;
}

int calcularDiferencaDias(const char *data1, const char *data2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(data1, "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(data2, "%d/%d/%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);
    tm1.tm_mon -= 1;
    tm1.tm_year -= 1900;
    tm2.tm_mon -= 1;
    tm2.tm_year -= 1900;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    return (int)difftime(t2, t1) / (60 * 60 * 24);
}

void coletarDatas(DatasObra *datas) {
    do {
        printf("Digite a data de início (dd/mm/aaaa): ");
        fgets(datas->dataInicio, MAX_DATA, stdin);
        limparString(datas->dataInicio);
        if (!validarData(datas->dataInicio)) {
            printf("Data de início inválida. Tente novamente.\n");
        }
    } while (!validarData(datas->dataInicio));

    do {
        printf("Digite a data de término (dd/mm/aaaa): ");
        fgets(datas->dataTermino, MAX_DATA, stdin);
        limparString(datas->dataTermino);
        if (!validarData(datas->dataTermino) || 
            calcularDiferencaDias(datas->dataInicio, datas->dataTermino) < 0) {
            printf("Data de término inválida. Deve ser posterior à data de início.\n");
        }
    } while (!validarData(datas->dataTermino) || 
             calcularDiferencaDias(datas->dataInicio, datas->dataTermino) < 0);

    do {
        printf("Digite a data atual (dd/mm/aaaa): ");
        fgets(datas->dataAtual, MAX_DATA, stdin);
        limparString(datas->dataAtual);
        if (!validarData(datas->dataAtual) || 
            calcularDiferencaDias(datas->dataInicio, datas->dataAtual) < 0) {
            printf("Data atual inválida. Deve ser posterior ou igual à data de início.\n");
        }
    } while (!validarData(datas->dataAtual) || 
             calcularDiferencaDias(datas->dataInicio, datas->dataAtual) < 0);

    datas->diasPassados = calcularDiferencaDias(datas->dataInicio, datas->dataAtual);
    datas->diasRestantes = calcularDiferencaDias(datas->dataAtual, datas->dataTermino);
    datas->diasAtraso = (datas->diasRestantes < 0) ? -datas->diasRestantes : 0;
    int duracaoTotal = calcularDiferencaDias(datas->dataInicio, datas->dataTermino);
    datas->pctPassado = duracaoTotal > 0 ? (float)datas->diasPassados / duracaoTotal * 100 : 100;
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    InformacoesObra obra;
    DatasObra datas;
    InformacoesFinanceiras financas;

    printf("=== Gerador de Relatório de Obra ===\n");

    // Nome da obra e mestre de obras
    printf("Digite o nome da obra: ");
    fgets(obra.nomeObra, MAX_OBRA_NOME, stdin);
    limparString(obra.nomeObra);

    printf("Digite o nome do mestre de obras: ");
    fgets(obra.mestreObras, MAX_NOME, stdin);
    limparString(obra.mestreObras);

    // Coleta de datas
    coletarDatas(&datas);

    // Informações financeiras
    printf("Digite o orçamento total (R$): ");
    scanf("%f", &financas.orcamentoTotal);
    printf("Digite o gasto atual (R$): ");
    scanf("%f", &financas.gastoAtual);
    financas.orcamentoRestante = financas.orcamentoTotal - financas.gastoAtual;
    financas.pctGasto = financas.orcamentoTotal > 0 
        ? (financas.gastoAtual / financas.orcamentoTotal) * 100 
        : 0;

    // Exibição do relatório
    printf("\n=== Relatório da Obra ===\n");
    printf("Nome da obra: %s\n", obra.nomeObra);
    printf("Mestre de obras: %s\n", obra.mestreObras);
    printf("Data de início: %s\n", datas.dataInicio);
    printf("Data de término: %s\n", datas.dataTermino);
    printf("Data atual: %s\n", datas.dataAtual);
    printf("Dias passados: %d\n", datas.diasPassados);
    if (datas.diasRestantes >= 0) {
        printf("Dias restantes: %d\n", datas.diasRestantes);
    } else {
        printf("A obra está atrasada em %d dias.\n", datas.diasAtraso);
    }
    printf("Percentual do prazo decorrido: %.2f%%\n", datas.pctPassado);
    printf("Orçamento total: R$ %.2f\n", financas.orcamentoTotal);
    printf("Gasto atual: R$ %.2f\n", financas.gastoAtual);
    printf("Orçamento restante: R$ %.2f\n", financas.orcamentoRestante);
    printf("Percentual do orçamento gasto: %.2f%%\n", financas.pctGasto);

    return 0;
}
