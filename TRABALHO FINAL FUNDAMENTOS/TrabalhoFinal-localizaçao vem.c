#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Prototipagem de funções
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado);
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado, int *diasUteis);
int calcularDiasUteis(const char *dataInicio, const char *dataTermino);
void lerData(const char *mensagem, char *data);

// Definições gerais
#define MAX_RESPONSAVEIS 10
#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_TELEFONE 15
#define MAX_OBRA_NOME 100
#define MAX_MESTRE_OBRAS 100
#define MAX_DATA 11
#define UF_COUNT 27

// Mensagens de erro
#define ERRO_DATA_INICIO_INVALIDA "Data de término inválida. A data de término deve ser posterior à data de início."
#define ERRO_DATA_ATUAL_INVALIDA "Data atual inválida. A data atual deve estar entre a data de início e a data de término."
#define ERRO_DATA_INVALIDA "Data inválida."
#define ERRO_ORCAMENTO_INVALIDO "Orçamento total inválido." // Definindo a mensagem de erro

// Limites financeiros
#define ORCAMENTO_MINIMO 0.0
#define ORCAMENTO_MAXIMO 10000000.0 // 

// Códigos de status
#define SUCESSO 0
#define ERRO 1

// Número de categorias de despesas
#define NUM_CATEGORIAS 5

// Nomes de arquivos
#define ARQUIVO_RELATORIO "relatorio_obra.txt"

// Limites de datas
#define ANO_MINIMO 1900
#define ANO_MAXIMO 2100

// Mensagens de sucesso
#define SUCESSO_RELATORIO "Relatório gerado com sucesso."

// Estrutura para armazenar as informações dos responsáveis técnicos
typedef struct {
    char nome[MAX_NOME];
    char numeroCREA[20];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
} ResponsavelTecnico;

// Estrutura para armazenar as informações da obra
typedef struct {
    char nomeObra[MAX_OBRA_NOME];
    char mestredeObras[MAX_MESTRE_OBRAS];
} InformacoesObra;

// Estrutura para armazenar as datas da obra
typedef struct {
    char dataInicio[MAX_DATA];
    char dataTermino[MAX_DATA];
    int diasPassados;
    int diasRestantes;
    float pctPassado;
} DatasObra;

// Estrutura para armazenar as informações financeiras
typedef struct {
    float orcamentoTotal;
    float gastoAtual;
    float orcamentoRestante;
    float pctGasto;
    float salarioTotal;
    float pctOrcGastoFuncionarios;
} InformacoesFinanceiras;

// Estrutura para armazenar as inforamççoes de localização da obra:
typedef struct {
    char cep[10];
    char endereco[MAX_OBRA_NOME];
    char numero[10];
    char complemento[MAX_OBRA_NOME];
    char bairro[MAX_OBRA_NOME];
    char cidade[MAX_OBRA_NOME];
    char estado[3];
} Localizacao;

// Estrutura para armazenar os custos referentes a localização da obra:
typedef struct {
    char uf[3];
    float custoHora;
} CustoMaoDeObra;

CustoMaoDeObra custos[] = {
    {"AC", 25.32}, {"AL", 22.85}, {"AP", 29.51}, {"AM", 24.18},
    {"BA", 26.93}, {"CE", 23.76}, {"DF", 32.14}, {"ES", 28.87},
    {"GO", 27.55}, {"MA", 21.99}, {"MT", 29.03}, {"MS", 28.42},
    {"MG", 27.18}, {"PA", 24.65}, {"PB", 22.31}, {"PR", 30.78},
    {"PE", 25.91}, {"PI", 21.54}, {"RJ", 31.45}, {"RN", 23.29},
    {"RS", 33.89}, {"RO", 25.78}, {"RR", 29.98}, {"SC", 30.12},
    {"SP", 34.56}, {"SE", 22.05}, {"TO", 24.92}
};

// Estrutura principal para o relatório da obra
typedef struct {
    InformacoesObra infoObra;
    DatasObra datas;
    InformacoesFinanceiras financas;
    ResponsavelTecnico responsaveis[MAX_RESPONSAVEIS];
    int numResponsaveis;
    int faseObra;
} RelatorioObra;

// Função para calcular orçamento:
float calculoPorcentagemOrcGasto(float orcamentoTotal, float gastoAtual) {
    if (orcamentoTotal <= ORCAMENTO_MINIMO) { // Usar ORCAMENTO_MINIMO
        printf("%s\n", ERRO_ORCAMENTO_INVALIDO); // Usar ERRO_ORCAMENTO_INVALIDO
        return -1;
    }
    return (gastoAtual / orcamentoTotal) * 100;
}

// Função para calcular a % do orçamento gasto com os funcionários
float calculoOrcamentoFuncionarios(float orcamentoTotal, float gastoSalarios) {
    if (orcamentoTotal <= 0) {
        printf("Erro: O orçamento total não pode ser igual ou menor que zero.\n");
        return -1;
    }
    return (gastoSalarios / orcamentoTotal) * 100;
}

// Função para validar, ler e calcular datas
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado, int *diasUteis) {
    // Função para validar uma data
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
        // Verificar dias específicos de cada mês
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

    // Função para calcular a diferença em dias entre duas datas
    int calcularDuracao(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
        memset(&tmInicio, 0, sizeof(struct tm));
        memset(&tmTermino, 0, sizeof(struct tm));

        sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon , &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o mês (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        return (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24); // Diferença em dias
    }

    // Função para calcular dias úteis
    int calcularDiasUteis(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
        memset(&tmInicio, 0, sizeof(struct tm));
        memset(&tmTermino, 0, sizeof(struct tm));

        sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o mês (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        int diasUteis = 0;
        for (time_t t = tempoInicio; t <= tempoTermino; t += 86400) { // 86400 segundos em um dia
            struct tm *tm = localtime(&t);
            // Contar apenas de segunda a sexta (0=domingo, 1=segunda, ..., 6=sábado)
            if (tm->tm_wday != 0 && tm->tm_wday != 6) {diasUteis++;
            }
        }

        return diasUteis;
    }

    // Ler a data de início
    lerData("Digite a data de início", dataInicio);

    // Ler a data de término e validar em relação à data de início
    do {
        lerData("Digite a data de término prevista", dataTermino);
        if (calcularDuracao(dataInicio, dataTermino) < 0) {
            printf("Data de término inválida. A data de término deve ser posterior à data de início.\n");
        }
    } while (calcularDuracao(dataInicio, dataTermino) < 0);

    // Ler a data atual e validar em relação à data de início
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataInicio, dataAtual) < 0) {
            printf("Data atual inválida. A data atual deve ser posterior à data de início da obra.\n");
        }
    } while (calcularDuracao(dataInicio, dataAtual) < 0);

    // Calcular o tempo da obra
    *diasPassados = calcularDuracao(dataInicio, dataAtual);
    *diasRestantes = calcularDuracao(dataAtual, dataTermino);

    // Calcular dias úteis
    *diasUteis = calcularDiasUteis(dataInicio, dataAtual);

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal != 0) {
        *percentualPassado = (((float)*diasPassados) / duracaoTotal) * 100;
    } else {
        *percentualPassado = 0;
    }
}

// Função para obter e validar o orçamento total
float obterOrcamentoTotal() {
    float orcamentoTotal;
    int valido;

    do {
        printf("Digite o orçamento total da obra: R$ ");
        valido = scanf("%f", &orcamentoTotal);

        // Verifica se a leitura foi bem-sucedida e se o valor é maior que ORCAMENTO_MINIMO
        if (valido != 1 || orcamentoTotal <= ORCAMENTO_MINIMO) { // Usar ORCAMENTO_MINIMO
            printf("O orçamento total deve ser um número maior que zero. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer até o final da linha
        }
    } while (orcamentoTotal <= ORCAMENTO_MINIMO || valido != 1);

    return orcamentoTotal;
}

// Função para obter informações sobre a equipe
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios, float *salarioFuncionarios) {
    // Obter o nome do mestre de obras
    printf("Informe o nome do mestre de obras responsável: ");
    scanf(" %[^\n]", mestredeObras);

    // Validar a quantidade de funcionários
    int valido;
    do {
        printf("Informe quantos funcionários estão trabalhando na obra: ");
        valido = scanf("%d", qtdFuncionarios);

        // Verifica se a leitura foi bem-sucedida e se o valor é maior que 0
        if (valido != 1 || *qtdFuncionarios <= 0) {
            printf("A quantidade de funcionários deve ser um número inteiro maior que zero. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer até o final da linha
        }
    } while (*qtdFuncionarios <= 0 || valido != 1);

    // Obter o salário dos funcionários
    do {
        printf("Informe o salário dos funcionários: R$ ");
        valido = scanf("%f", salarioFuncionarios);
        if (valido != 1 || *salarioFuncionarios <= 0) {
            printf("O salário deve ser um número positivo. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer até o final da linha
        }
    } while (*salarioFuncionarios <= 0 || valido != 1);
}

// Função para coletar informações do responsável técnico
void obterResponsavelTecnico(ResponsavelTecnico *responsavel) {
    printf("Digite o nome do responsável técnico: Eng. ");
    scanf(" %[^\n]", responsavel->nome);

    printf("Digite o número CREA do responsável técnico: ");
    scanf(" %[^\n]", responsavel->numeroCREA);

    printf("Digite o email do responsável técnico: ");
    scanf(" %[^\n]", responsavel->email);

    printf("Digite o telefone do responsável técnico: ");
    scanf(" %[^\n]", responsavel->telefone);
}

// Função para gerar o relatório
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra, Localizacao localizacao) {
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

    if (diasRestantes < 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes * -1);
        printf("Tempo do prazo excedido: %d\n", diasRestantes * -1);
    } else {
        fprintf(arquivo, "Dias restantes para conclusão: %d\n", diasRestantes);
        printf("Dias restantes para conclusão: %d\n", diasRestantes);
    }

    fprintf(arquivo, "Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    // Exibir informações de localização
    fprintf(arquivo, "\n=== Localização da Obra ===\n");
    fprintf(arquivo, "CEP: %s\n", localizacao.cep);
    fprintf(arquivo, "Endereço: %s, %s\n", localizacao.endereco, localizacao.numero);
    if (strlen(localizacao.complemento) > 0) {
        fprintf(arquivo, "Complemento: %s\n", localizacao.complemento);
    }
    fprintf(arquivo, "Bairro: %s\n", localizacao.bairro);
    fprintf(arquivo, "Cidade: %s\n", localizacao.cidade);
    fprintf(arquivo, "Estado (UF): %s\n", localizacao.estado);

    // Informações sobre responsáveis técnicos
    for (int i = 0; i < numResponsaveis; i++) {
        fprintf(arquivo, "Responsável técnico %d: %s\n", i + 1, responsaveis[i].nome);
        fprintf(arquivo, "Número CREA: %s\n", responsaveis[i].numeroCREA);
        fprintf(arquivo, "Email: %s\n", responsaveis[i].email);
        fprintf(arquivo, "Telefone: %s\n", responsaveis[i].telefone);
    }

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

// Função para exibir o relatório
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra, Localizacao localizacao) {
    printf("\n=== Relatório da Obra ===\n");
    printf("Nome da obra: %s\n", nomeObra);
    printf("Data de início: %s\n", dataInicio);
    printf("Data de término prevista: %s\n", dataTermino);
    printf("Dias de obra: %d\n", diasPassados);

    if (diasRestantes < 0) {
        printf("Tempo do prazo excedido: %d\n", diasRestantes * -1);
    } else {
        printf("Dias restantes para conclusão: %d\n", diasRestantes);
    }

    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    // Exibir informações de localização
    printf("\n=== Localização da Obra ===\n");
    printf("CEP: %s\n", localizacao.cep);
    printf("Endereço: %s, %s\n", localizacao.endereco, localizacao.numero);
    if (strlen(localizacao.complemento) > 0) {
        printf("Complemento: %s\n", localizacao.complemento);
    }
    printf("Bairro: %s\n", localizacao.bairro);
    printf("Cidade: %s\n", localizacao.cidade);
    printf("Estado (UF): %s\n", localizacao.estado);

    for (int i = 0; i < numResponsaveis; i++) {
        printf("Responsável técnico %d: %s\n", i + 1, responsaveis[i].nome);
        printf("Número CREA: %s\n", responsaveis[i].numeroCREA);
        printf("Email: %s\n", responsaveis[i].email);
        printf("Telefone: %s\n", responsaveis[i].telefone);
    }

    printf("Orçamento total: R$ %.2f\n", orcamentoTotal);
    printf("Despesas acumuladas: R$ %.2f\n", gastoAtual);
    printf("Verba restante: R$ %.2f\n", orcamentoRestante);

    if (pctGasto >= 0) {
        printf("Percentual do orçamento gasto: %.2f%%\n", pctGasto);
    } else {
        printf("Orçamento total inválido!\n");
    }

    printf("Mestre de obras: %s\n", mestredeObras);
    printf("Gasto total com salário de funcionários: R$ %.2f\n", salarioTotal);
    printf("Porcentagem do orçamento gasto com salários: %.2f%%\n", pctOrcGastoFuncionarios);

    printf("Fase da obra: ");
    switch (faseObra) {
        case 1: printf("Início\n"); break;
        case 2: printf("Fundação\n"); break;
        case 3: printf("Estrutura\n"); break;
        case 4: printf("Acabamento\n"); break;
        case 5: printf("Conclusão \n"); break;
        default: printf("Fase inválida\n");
    }
}

// Função para limpar caracteres inválidos de uma string
void limparCaracteresInvalidos(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (isalnum((unsigned char)*src) || *src == '_' || *src == '-') {
            *dst++ = *src; // Mantém caracteres alfanuméricos, '_' e '-'
        }
        src++;
    }
    *dst = '\0'; // Adiciona o terminador nulo
}

// Função para formatar a data para um formato adequado para o nome do arquivo
void formatarDataParaArquivo(char *dataAtual) {
    char dataFormatada[11]; // Para armazenar a data formatada
    snprintf(dataFormatada, sizeof(dataFormatada), "%c%c-%c%c-%c%c%c%c",
             dataAtual[0], dataAtual[1], // Dia
             dataAtual[3], dataAtual[4], // Mês
             dataAtual[6], dataAtual[7], dataAtual[8], dataAtual[9]); // Ano
    strcpy(dataAtual, dataFormatada); // Atualiza dataAtual com o formato correto
}

// Função para gerar o nome do arquivo do relatório
char* gerarNomeArquivoRelatorio(const char *nomeRelatorio, const char *dataAtual) {
    // Limpar caracteres inválidos
    char nomeRelatorioLimpo[100];
    char dataAtualLimpa[11];

    strcpy(nomeRelatorioLimpo, nomeRelatorio);
    strcpy(dataAtualLimpa, dataAtual);

    limparCaracteresInvalidos(nomeRelatorioLimpo);
    limparCaracteresInvalidos(dataAtualLimpa);

    // Alocar memória dinamicamente para o nome do arquivo
    char *nomeArquivo = malloc(strlen("relatorio_") + strlen(nomeRelatorioLimpo) + strlen("_") + strlen(dataAtualLimpa) + strlen(".txt") + 1);
    if (nomeArquivo == NULL) {
        printf("Erro ao alocar memória para o nome do arquivo.\n");
        return NULL;
    }

    // Construir o nome do arquivo
    strcpy(nomeArquivo, "relatorio_");
    strcat(nomeArquivo, nomeRelatorioLimpo);
    strcat(nomeArquivo, "_");
    strcat(nomeArquivo, dataAtualLimpa); // Incluindo a data
    strcat(nomeArquivo, ".txt");

    return nomeArquivo;
}

// Função para verificar se a UF é válida
bool ufValida(const char* uf) {
    const char* ufs[UF_COUNT] = {
        "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", 
        "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN", 
        "RS", "RO", "RR", "SC", "SP", "SE", "TO"
    };

    for (int i = 0; i < UF_COUNT; i++) {
        if (strcmp(uf, ufs[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Função para obter informações sobre a localização da obra
void obterLocalizacaoObra(Localizacao *localizacao) {
    printf("Informe o CEP: ");
    fgets(localizacao->cep, sizeof(localizacao->cep), stdin);
    localizacao->cep[strcspn(localizacao->cep, "\n")] = 0; // Remove a nova linha

    printf("Informe o endereço: ");
    fgets(localizacao->endereco, sizeof(localizacao->endereco), stdin);
    localizacao->endereco[strcspn(localizacao->endereco, "\n")] = 0; // Remove a nova linha

    printf("Informe o número: ");
    fgets(localizacao->numero, sizeof(localizacao->numero), stdin);
    localizacao->numero[strcspn(localizacao->numero, "\n")] = 0; // Remove a nova linha

    printf("Informe o complemento: ");
    fgets(localizacao->complemento, sizeof(localizacao->complemento), stdin);
    localizacao->complemento[strcspn(localizacao->complemento, "\n")] = 0; // Remove a nova linha

    printf("Informe o bairro: ");
    fgets(localizacao->bairro, sizeof(localizacao->bairro), stdin);
    localizacao->bairro[strcspn(localizacao->bairro, "\n")] = 0; // Remove a nova linha

    printf("Informe a cidade: ");
    fgets(localizacao->cidade, sizeof(localizacao->cidade), stdin);
    localizacao->cidade[strcspn(localizacao->cidade, "\n")] = 0; // Remove a nova linha

    // Loop até que uma UF válida seja inserida
    do {
        printf("Informe o estado (UF): ");
        fgets(localizacao->estado, sizeof(localizacao->estado), stdin);
        localizacao->estado[strcspn(localizacao->estado, "\n")] = 0; // Remove a nova linha

        if (!ufValida(localizacao->estado)) {
            fprintf(stderr, "Erro: UF inválida. Por favor, insira uma UF válida.\n");
        }
    } while (!ufValida(localizacao->estado)); // Continua pedindo até que a UF seja válida
}

// Função main
int main() {
    // Configuração para o idioma português
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    char *nomeArquivo = NULL; // Declara nomeArquivo
    FILE *arquivo = NULL; // Declara arquivo aqui
    char nomeRelatorio[100];
    char dataAtual[11]; // Declare apenas uma vez
    RelatorioObra relatorio; // Declarar a variável relatório
    
    do {
        // Exibir o menu de opções
        char opcao_str[10]; // String para ler a opção do menu
        printf("\n=== Menu ===\n");
        printf("1. Gerar novo relatório\n");
        printf("2. Visualizar relatórios existentes\n"); // Nova opção
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        fgets(opcao_str, 10, stdin);
        sscanf(opcao_str, "%d", &opcao);

        switch (opcao) {
            case 1: {
                // Coletando as informações
                printf("=== Gerador de Relatório de Obra ===\n");
                printf("Digite o nome do relatório: ");
                fgets(nomeRelatorio, 100, stdin); // Usar fgets para ler a string
                nomeRelatorio[strcspn(nomeRelatorio, "\n")] = 0; // Remover o caractere de nova linha

                // Definindo as variáveis
                char dataInicio[11];
                char dataTermino[11];
                char mestredeObras[100];
                int qtdFuncionarios, diasPassados, diasRestantes;
                float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

                // Definindo categorias de despesas
                const char *categoriasDespesas[NUM_CATEGORIAS] = {
                    "Materiais",
                    "Mão de obra terceirizada",
                    "Aluguel de equipamentos",
                    "Transporte",
                    "Outros"
                };
                float despesas[NUM_CATEGORIAS] = {0};

                // Obter e validar as datas
                obterDatasValidas(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

                // Formatar a data para o nome do arquivo
                formatarDataParaArquivo(dataAtual);

                // Gerar o nome do arquivo do relatório
                nomeArquivo = gerarNomeArquivoRelatorio(nomeRelatorio, dataAtual);
                if (nomeArquivo == NULL) {
                    return 1; // Erro ao gerar o nome do arquivo.
                }

                printf("Relatório salvo. Nome do arquivo: %s\n", nomeArquivo); // Verifique o nome do arquivo

                // Abrindo o arquivo para salvar o relatório
                arquivo = fopen(nomeArquivo, "w"); // Atribui o novo valor ao arquivo
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo para escrita.\n");
                    free(nomeArquivo);
                    return 1;
                }

                // Usando as funções para obter as informações
                orcamentoTotal = obterOrcamentoTotal();
                obterInformacoesEquipe(mestredeObras, &qtdFuncionarios, &salarioFuncionarios);

                // Coletando informações dos responsáveis técnicos
                relatorio.numResponsaveis = 0; // Inicializa o contador de responsáveis
                do {
                    if (relatorio.numResponsaveis < MAX_RESPONSAVEIS) {
                        printf("=== Coleta de Informações do Responsável Técnico %d ===\n", relatorio.numResponsaveis + 1);
                        obterResponsavelTecnico(&relatorio.responsaveis[relatorio.numResponsaveis]);
                        relatorio.numResponsaveis++;
                    } else {
                        printf("Número máximo de responsáveis atingido.\n");
                        break;
                    }

                    char continuar;
                    printf("Deseja adicionar outro responsável técnico? (s/n): ");
                    scanf(" %c", &continuar);
                    if (continuar != 's' && continuar != 'S') {
                        break;
                    }
                } while (1);

                // Coletando despesas por categoria
                for (int i = 0; i < NUM_CATEGORIAS; i++) {
                    do {
                        printf("Digite o gasto com %s: R$ ", categoriasDespesas[i]);
                        scanf("%f", &despesas[i]);
                        if (despesas[i] < 0) {
                            printf("Valor inválido. Digite um valor não negativo.\n");
                        }
                    } while (despesas[i] < 0);
                }

                // Calculando o gastoAtual
                gastoAtual = 0;
                for (int i = 0; i < NUM_CATEGORIAS; i++) {
                    gastoAtual += despesas[i];
                }

                // Adicionar o gasto com salários dos funcionários
                float salarioTotal = qtdFuncionarios * salarioFuncionarios;
                gastoAtual += salarioTotal;

                // Calculando a porcentagem do orçamento gasta
                pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);

                // Calculando a porcentagem do orçamento gasta com funcionários
                pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);

                // Calculando o orçamento restante
                float orcamentoRestante = orcamentoTotal - gastoAtual;

                // Escrevendo os dados no arquivo
                fprintf(arquivo, "Relatório de Obra: %s\n", nomeRelatorio);
                fprintf(arquivo, "Data do Relatório: %s\n", dataAtual);
                fprintf(arquivo, "Orçamento Total: R$ %.2f\n", orcamentoTotal);
                fprintf(arquivo, "Gasto Atual: R$ %.2f\n", gastoAtual);
                fprintf(arquivo, "Orçamento Restante: R$ %.2f\n", orcamentoRestante);
                fprintf(arquivo, "Porcentagem do Orçamento Gasta: %.2f%%\n", pctGasto);
                fprintf(arquivo, "Porcentagem do Orçamento Gasta com Funcionários: %.2f%%\n", pctOrcGastoFuncionarios);
                fprintf(arquivo, "Dias Passados: %d\n", diasPassados);
                fprintf(arquivo, "Dias Restantes: %d\n", diasRestantes);

                // Fechar o arquivo
                fclose(arquivo);
                free(nomeArquivo); // Liberar a memória alocada para o nome do arquivo

                // Mensagem de sucesso após gerar o relatório
                printf("%s\n", SUCESSO_RELATORIO); // Usar SUCESSO_RELATORIO após gerar o relatório
                break;

            }
            case 2:
                // Lógica para visualizar relatórios existentes
                printf("Opção de visualizar relatórios ainda não implementada.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}