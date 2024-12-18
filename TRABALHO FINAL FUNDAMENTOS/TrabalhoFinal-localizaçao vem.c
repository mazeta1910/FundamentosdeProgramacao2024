#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Prototipagem de fun��es
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado);
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado, int *diasUteis);
int calcularDiasUteis(const char *dataInicio, const char *dataTermino);
void lerData(const char *mensagem, char *data);

// Defini��es gerais
#define MAX_RESPONSAVEIS 10
#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_TELEFONE 15
#define MAX_OBRA_NOME 100
#define MAX_MESTRE_OBRAS 100
#define MAX_DATA 11
#define UF_COUNT 27

// Mensagens de erro
#define ERRO_DATA_INICIO_INVALIDA "Data de t�rmino inv�lida. A data de t�rmino deve ser posterior � data de in�cio."
#define ERRO_DATA_ATUAL_INVALIDA "Data atual inv�lida. A data atual deve estar entre a data de in�cio e a data de t�rmino."
#define ERRO_DATA_INVALIDA "Data inv�lida."
#define ERRO_ORCAMENTO_INVALIDO "Or�amento total inv�lido." // Definindo a mensagem de erro

// Limites financeiros
#define ORCAMENTO_MINIMO 0.0
#define ORCAMENTO_MAXIMO 10000000.0 // 

// C�digos de status
#define SUCESSO 0
#define ERRO 1

// N�mero de categorias de despesas
#define NUM_CATEGORIAS 5

// Nomes de arquivos
#define ARQUIVO_RELATORIO "relatorio_obra.txt"

// Limites de datas
#define ANO_MINIMO 1900
#define ANO_MAXIMO 2100

// Mensagens de sucesso
#define SUCESSO_RELATORIO "Relat�rio gerado com sucesso."

// Estrutura para armazenar as informa��es dos respons�veis t�cnicos
typedef struct {
    char nome[MAX_NOME];
    char numeroCREA[20];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
} ResponsavelTecnico;

// Estrutura para armazenar as informa��es da obra
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

// Estrutura para armazenar as informa��es financeiras
typedef struct {
    float orcamentoTotal;
    float gastoAtual;
    float orcamentoRestante;
    float pctGasto;
    float salarioTotal;
    float pctOrcGastoFuncionarios;
} InformacoesFinanceiras;

// Estrutura para armazenar as inforam��oes de localiza��o da obra:
typedef struct {
    char cep[10];
    char endereco[MAX_OBRA_NOME];
    char numero[10];
    char complemento[MAX_OBRA_NOME];
    char bairro[MAX_OBRA_NOME];
    char cidade[MAX_OBRA_NOME];
    char estado[3];
} Localizacao;

// Estrutura para armazenar os custos referentes a localiza��o da obra:
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

// Estrutura principal para o relat�rio da obra
typedef struct {
    InformacoesObra infoObra;
    DatasObra datas;
    InformacoesFinanceiras financas;
    ResponsavelTecnico responsaveis[MAX_RESPONSAVEIS];
    int numResponsaveis;
    int faseObra;
} RelatorioObra;

// Fun��o para calcular or�amento:
float calculoPorcentagemOrcGasto(float orcamentoTotal, float gastoAtual) {
    if (orcamentoTotal <= ORCAMENTO_MINIMO) { // Usar ORCAMENTO_MINIMO
        printf("%s\n", ERRO_ORCAMENTO_INVALIDO); // Usar ERRO_ORCAMENTO_INVALIDO
        return -1;
    }
    return (gastoAtual / orcamentoTotal) * 100;
}

// Fun��o para calcular a % do or�amento gasto com os funcion�rios
float calculoOrcamentoFuncionarios(float orcamentoTotal, float gastoSalarios) {
    if (orcamentoTotal <= 0) {
        printf("Erro: O or�amento total n�o pode ser igual ou menor que zero.\n");
        return -1;
    }
    return (gastoSalarios / orcamentoTotal) * 100;
}

// Fun��o para validar, ler e calcular datas
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado, int *diasUteis) {
    // Fun��o para validar uma data
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
        // Verificar dias espec�ficos de cada m�s
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

    // Fun��o para calcular a diferen�a em dias entre duas datas
    int calcularDuracao(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
        memset(&tmInicio, 0, sizeof(struct tm));
        memset(&tmTermino, 0, sizeof(struct tm));

        sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon , &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o m�s (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        return (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24); // Diferen�a em dias
    }

    // Fun��o para calcular dias �teis
    int calcularDiasUteis(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
        memset(&tmInicio, 0, sizeof(struct tm));
        memset(&tmTermino, 0, sizeof(struct tm));

        sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o m�s (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        int diasUteis = 0;
        for (time_t t = tempoInicio; t <= tempoTermino; t += 86400) { // 86400 segundos em um dia
            struct tm *tm = localtime(&t);
            // Contar apenas de segunda a sexta (0=domingo, 1=segunda, ..., 6=s�bado)
            if (tm->tm_wday != 0 && tm->tm_wday != 6) {diasUteis++;
            }
        }

        return diasUteis;
    }

    // Ler a data de in�cio
    lerData("Digite a data de in�cio", dataInicio);

    // Ler a data de t�rmino e validar em rela��o � data de in�cio
    do {
        lerData("Digite a data de t�rmino prevista", dataTermino);
        if (calcularDuracao(dataInicio, dataTermino) < 0) {
            printf("Data de t�rmino inv�lida. A data de t�rmino deve ser posterior � data de in�cio.\n");
        }
    } while (calcularDuracao(dataInicio, dataTermino) < 0);

    // Ler a data atual e validar em rela��o � data de in�cio
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataInicio, dataAtual) < 0) {
            printf("Data atual inv�lida. A data atual deve ser posterior � data de in�cio da obra.\n");
        }
    } while (calcularDuracao(dataInicio, dataAtual) < 0);

    // Calcular o tempo da obra
    *diasPassados = calcularDuracao(dataInicio, dataAtual);
    *diasRestantes = calcularDuracao(dataAtual, dataTermino);

    // Calcular dias �teis
    *diasUteis = calcularDiasUteis(dataInicio, dataAtual);

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal != 0) {
        *percentualPassado = (((float)*diasPassados) / duracaoTotal) * 100;
    } else {
        *percentualPassado = 0;
    }
}

// Fun��o para obter e validar o or�amento total
float obterOrcamentoTotal() {
    float orcamentoTotal;
    int valido;

    do {
        printf("Digite o or�amento total da obra: R$ ");
        valido = scanf("%f", &orcamentoTotal);

        // Verifica se a leitura foi bem-sucedida e se o valor � maior que ORCAMENTO_MINIMO
        if (valido != 1 || orcamentoTotal <= ORCAMENTO_MINIMO) { // Usar ORCAMENTO_MINIMO
            printf("O or�amento total deve ser um n�mero maior que zero. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer at� o final da linha
        }
    } while (orcamentoTotal <= ORCAMENTO_MINIMO || valido != 1);

    return orcamentoTotal;
}

// Fun��o para obter informa��es sobre a equipe
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios, float *salarioFuncionarios) {
    // Obter o nome do mestre de obras
    printf("Informe o nome do mestre de obras respons�vel: ");
    scanf(" %[^\n]", mestredeObras);

    // Validar a quantidade de funcion�rios
    int valido;
    do {
        printf("Informe quantos funcion�rios est�o trabalhando na obra: ");
        valido = scanf("%d", qtdFuncionarios);

        // Verifica se a leitura foi bem-sucedida e se o valor � maior que 0
        if (valido != 1 || *qtdFuncionarios <= 0) {
            printf("A quantidade de funcion�rios deve ser um n�mero inteiro maior que zero. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer at� o final da linha
        }
    } while (*qtdFuncionarios <= 0 || valido != 1);

    // Obter o sal�rio dos funcion�rios
    do {
        printf("Informe o sal�rio dos funcion�rios: R$ ");
        valido = scanf("%f", salarioFuncionarios);
        if (valido != 1 || *salarioFuncionarios <= 0) {
            printf("O sal�rio deve ser um n�mero positivo. Digite novamente!\n");
            while (getchar() != '\n'); // Limpa o buffer at� o final da linha
        }
    } while (*salarioFuncionarios <= 0 || valido != 1);
}

// Fun��o para coletar informa��es do respons�vel t�cnico
void obterResponsavelTecnico(ResponsavelTecnico *responsavel) {
    printf("Digite o nome do respons�vel t�cnico: Eng. ");
    scanf(" %[^\n]", responsavel->nome);

    printf("Digite o n�mero CREA do respons�vel t�cnico: ");
    scanf(" %[^\n]", responsavel->numeroCREA);

    printf("Digite o email do respons�vel t�cnico: ");
    scanf(" %[^\n]", responsavel->email);

    printf("Digite o telefone do respons�vel t�cnico: ");
    scanf(" %[^\n]", responsavel->telefone);
}

// Fun��o para gerar o relat�rio
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra, Localizacao localizacao) {
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

    if (diasRestantes < 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes * -1);
        printf("Tempo do prazo excedido: %d\n", diasRestantes * -1);
    } else {
        fprintf(arquivo, "Dias restantes para conclus�o: %d\n", diasRestantes);
        printf("Dias restantes para conclus�o: %d\n", diasRestantes);
    }

    fprintf(arquivo, "Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    // Exibir informa��es de localiza��o
    fprintf(arquivo, "\n=== Localiza��o da Obra ===\n");
    fprintf(arquivo, "CEP: %s\n", localizacao.cep);
    fprintf(arquivo, "Endere�o: %s, %s\n", localizacao.endereco, localizacao.numero);
    if (strlen(localizacao.complemento) > 0) {
        fprintf(arquivo, "Complemento: %s\n", localizacao.complemento);
    }
    fprintf(arquivo, "Bairro: %s\n", localizacao.bairro);
    fprintf(arquivo, "Cidade: %s\n", localizacao.cidade);
    fprintf(arquivo, "Estado (UF): %s\n", localizacao.estado);

    // Informa��es sobre respons�veis t�cnicos
    for (int i = 0; i < numResponsaveis; i++) {
        fprintf(arquivo, "Respons�vel t�cnico %d: %s\n", i + 1, responsaveis[i].nome);
        fprintf(arquivo, "N�mero CREA: %s\n", responsaveis[i].numeroCREA);
        fprintf(arquivo, "Email: %s\n", responsaveis[i].email);
        fprintf(arquivo, "Telefone: %s\n", responsaveis[i].telefone);
    }

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

// Fun��o para exibir o relat�rio
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra, Localizacao localizacao) {
    printf("\n=== Relat�rio da Obra ===\n");
    printf("Nome da obra: %s\n", nomeObra);
    printf("Data de in�cio: %s\n", dataInicio);
    printf("Data de t�rmino prevista: %s\n", dataTermino);
    printf("Dias de obra: %d\n", diasPassados);

    if (diasRestantes < 0) {
        printf("Tempo do prazo excedido: %d\n", diasRestantes * -1);
    } else {
        printf("Dias restantes para conclus�o: %d\n", diasRestantes);
    }

    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);

    // Exibir informa��es de localiza��o
    printf("\n=== Localiza��o da Obra ===\n");
    printf("CEP: %s\n", localizacao.cep);
    printf("Endere�o: %s, %s\n", localizacao.endereco, localizacao.numero);
    if (strlen(localizacao.complemento) > 0) {
        printf("Complemento: %s\n", localizacao.complemento);
    }
    printf("Bairro: %s\n", localizacao.bairro);
    printf("Cidade: %s\n", localizacao.cidade);
    printf("Estado (UF): %s\n", localizacao.estado);

    for (int i = 0; i < numResponsaveis; i++) {
        printf("Respons�vel t�cnico %d: %s\n", i + 1, responsaveis[i].nome);
        printf("N�mero CREA: %s\n", responsaveis[i].numeroCREA);
        printf("Email: %s\n", responsaveis[i].email);
        printf("Telefone: %s\n", responsaveis[i].telefone);
    }

    printf("Or�amento total: R$ %.2f\n", orcamentoTotal);
    printf("Despesas acumuladas: R$ %.2f\n", gastoAtual);
    printf("Verba restante: R$ %.2f\n", orcamentoRestante);

    if (pctGasto >= 0) {
        printf("Percentual do or�amento gasto: %.2f%%\n", pctGasto);
    } else {
        printf("Or�amento total inv�lido!\n");
    }

    printf("Mestre de obras: %s\n", mestredeObras);
    printf("Gasto total com sal�rio de funcion�rios: R$ %.2f\n", salarioTotal);
    printf("Porcentagem do or�amento gasto com sal�rios: %.2f%%\n", pctOrcGastoFuncionarios);

    printf("Fase da obra: ");
    switch (faseObra) {
        case 1: printf("In�cio\n"); break;
        case 2: printf("Funda��o\n"); break;
        case 3: printf("Estrutura\n"); break;
        case 4: printf("Acabamento\n"); break;
        case 5: printf("Conclus�o \n"); break;
        default: printf("Fase inv�lida\n");
    }
}

// Fun��o para limpar caracteres inv�lidos de uma string
void limparCaracteresInvalidos(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (isalnum((unsigned char)*src) || *src == '_' || *src == '-') {
            *dst++ = *src; // Mant�m caracteres alfanum�ricos, '_' e '-'
        }
        src++;
    }
    *dst = '\0'; // Adiciona o terminador nulo
}

// Fun��o para formatar a data para um formato adequado para o nome do arquivo
void formatarDataParaArquivo(char *dataAtual) {
    char dataFormatada[11]; // Para armazenar a data formatada
    snprintf(dataFormatada, sizeof(dataFormatada), "%c%c-%c%c-%c%c%c%c",
             dataAtual[0], dataAtual[1], // Dia
             dataAtual[3], dataAtual[4], // M�s
             dataAtual[6], dataAtual[7], dataAtual[8], dataAtual[9]); // Ano
    strcpy(dataAtual, dataFormatada); // Atualiza dataAtual com o formato correto
}

// Fun��o para gerar o nome do arquivo do relat�rio
char* gerarNomeArquivoRelatorio(const char *nomeRelatorio, const char *dataAtual) {
    // Limpar caracteres inv�lidos
    char nomeRelatorioLimpo[100];
    char dataAtualLimpa[11];

    strcpy(nomeRelatorioLimpo, nomeRelatorio);
    strcpy(dataAtualLimpa, dataAtual);

    limparCaracteresInvalidos(nomeRelatorioLimpo);
    limparCaracteresInvalidos(dataAtualLimpa);

    // Alocar mem�ria dinamicamente para o nome do arquivo
    char *nomeArquivo = malloc(strlen("relatorio_") + strlen(nomeRelatorioLimpo) + strlen("_") + strlen(dataAtualLimpa) + strlen(".txt") + 1);
    if (nomeArquivo == NULL) {
        printf("Erro ao alocar mem�ria para o nome do arquivo.\n");
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

// Fun��o para verificar se a UF � v�lida
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

// Fun��o para obter informa��es sobre a localiza��o da obra
void obterLocalizacaoObra(Localizacao *localizacao) {
    printf("Informe o CEP: ");
    fgets(localizacao->cep, sizeof(localizacao->cep), stdin);
    localizacao->cep[strcspn(localizacao->cep, "\n")] = 0; // Remove a nova linha

    printf("Informe o endere�o: ");
    fgets(localizacao->endereco, sizeof(localizacao->endereco), stdin);
    localizacao->endereco[strcspn(localizacao->endereco, "\n")] = 0; // Remove a nova linha

    printf("Informe o n�mero: ");
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

    // Loop at� que uma UF v�lida seja inserida
    do {
        printf("Informe o estado (UF): ");
        fgets(localizacao->estado, sizeof(localizacao->estado), stdin);
        localizacao->estado[strcspn(localizacao->estado, "\n")] = 0; // Remove a nova linha

        if (!ufValida(localizacao->estado)) {
            fprintf(stderr, "Erro: UF inv�lida. Por favor, insira uma UF v�lida.\n");
        }
    } while (!ufValida(localizacao->estado)); // Continua pedindo at� que a UF seja v�lida
}

// Fun��o main
int main() {
    // Configura��o para o idioma portugu�s
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    char *nomeArquivo = NULL; // Declara nomeArquivo
    FILE *arquivo = NULL; // Declara arquivo aqui
    char nomeRelatorio[100];
    char dataAtual[11]; // Declare apenas uma vez
    RelatorioObra relatorio; // Declarar a vari�vel relat�rio
    
    do {
        // Exibir o menu de op��es
        char opcao_str[10]; // String para ler a op��o do menu
        printf("\n=== Menu ===\n");
        printf("1. Gerar novo relat�rio\n");
        printf("2. Visualizar relat�rios existentes\n"); // Nova op��o
        printf("0. Sair\n");
        printf("Digite a op��o desejada: ");
        fgets(opcao_str, 10, stdin);
        sscanf(opcao_str, "%d", &opcao);

        switch (opcao) {
            case 1: {
                // Coletando as informa��es
                printf("=== Gerador de Relat�rio de Obra ===\n");
                printf("Digite o nome do relat�rio: ");
                fgets(nomeRelatorio, 100, stdin); // Usar fgets para ler a string
                nomeRelatorio[strcspn(nomeRelatorio, "\n")] = 0; // Remover o caractere de nova linha

                // Definindo as vari�veis
                char dataInicio[11];
                char dataTermino[11];
                char mestredeObras[100];
                int qtdFuncionarios, diasPassados, diasRestantes;
                float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

                // Definindo categorias de despesas
                const char *categoriasDespesas[NUM_CATEGORIAS] = {
                    "Materiais",
                    "M�o de obra terceirizada",
                    "Aluguel de equipamentos",
                    "Transporte",
                    "Outros"
                };
                float despesas[NUM_CATEGORIAS] = {0};

                // Obter e validar as datas
                obterDatasValidas(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

                // Formatar a data para o nome do arquivo
                formatarDataParaArquivo(dataAtual);

                // Gerar o nome do arquivo do relat�rio
                nomeArquivo = gerarNomeArquivoRelatorio(nomeRelatorio, dataAtual);
                if (nomeArquivo == NULL) {
                    return 1; // Erro ao gerar o nome do arquivo.
                }

                printf("Relat�rio salvo. Nome do arquivo: %s\n", nomeArquivo); // Verifique o nome do arquivo

                // Abrindo o arquivo para salvar o relat�rio
                arquivo = fopen(nomeArquivo, "w"); // Atribui o novo valor ao arquivo
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo para escrita.\n");
                    free(nomeArquivo);
                    return 1;
                }

                // Usando as fun��es para obter as informa��es
                orcamentoTotal = obterOrcamentoTotal();
                obterInformacoesEquipe(mestredeObras, &qtdFuncionarios, &salarioFuncionarios);

                // Coletando informa��es dos respons�veis t�cnicos
                relatorio.numResponsaveis = 0; // Inicializa o contador de respons�veis
                do {
                    if (relatorio.numResponsaveis < MAX_RESPONSAVEIS) {
                        printf("=== Coleta de Informa��es do Respons�vel T�cnico %d ===\n", relatorio.numResponsaveis + 1);
                        obterResponsavelTecnico(&relatorio.responsaveis[relatorio.numResponsaveis]);
                        relatorio.numResponsaveis++;
                    } else {
                        printf("N�mero m�ximo de respons�veis atingido.\n");
                        break;
                    }

                    char continuar;
                    printf("Deseja adicionar outro respons�vel t�cnico? (s/n): ");
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
                            printf("Valor inv�lido. Digite um valor n�o negativo.\n");
                        }
                    } while (despesas[i] < 0);
                }

                // Calculando o gastoAtual
                gastoAtual = 0;
                for (int i = 0; i < NUM_CATEGORIAS; i++) {
                    gastoAtual += despesas[i];
                }

                // Adicionar o gasto com sal�rios dos funcion�rios
                float salarioTotal = qtdFuncionarios * salarioFuncionarios;
                gastoAtual += salarioTotal;

                // Calculando a porcentagem do or�amento gasta
                pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);

                // Calculando a porcentagem do or�amento gasta com funcion�rios
                pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);

                // Calculando o or�amento restante
                float orcamentoRestante = orcamentoTotal - gastoAtual;

                // Escrevendo os dados no arquivo
                fprintf(arquivo, "Relat�rio de Obra: %s\n", nomeRelatorio);
                fprintf(arquivo, "Data do Relat�rio: %s\n", dataAtual);
                fprintf(arquivo, "Or�amento Total: R$ %.2f\n", orcamentoTotal);
                fprintf(arquivo, "Gasto Atual: R$ %.2f\n", gastoAtual);
                fprintf(arquivo, "Or�amento Restante: R$ %.2f\n", orcamentoRestante);
                fprintf(arquivo, "Porcentagem do Or�amento Gasta: %.2f%%\n", pctGasto);
                fprintf(arquivo, "Porcentagem do Or�amento Gasta com Funcion�rios: %.2f%%\n", pctOrcGastoFuncionarios);
                fprintf(arquivo, "Dias Passados: %d\n", diasPassados);
                fprintf(arquivo, "Dias Restantes: %d\n", diasRestantes);

                // Fechar o arquivo
                fclose(arquivo);
                free(nomeArquivo); // Liberar a mem�ria alocada para o nome do arquivo

                // Mensagem de sucesso ap�s gerar o relat�rio
                printf("%s\n", SUCESSO_RELATORIO); // Usar SUCESSO_RELATORIO ap�s gerar o relat�rio
                break;

            }
            case 2:
                // L�gica para visualizar relat�rios existentes
                printf("Op��o de visualizar relat�rios ainda n�o implementada.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}