#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Definições gerais
#define MAX_RESPONSAVEIS 10
#define MAX_NOME 100
#define MAX_EMAIL 100
#define MAX_TELEFONE 15
#define MAX_OBRA_NOME 100
#define MAX_MESTRE_OBRAS 100
#define MAX_DATA 11
#define MAX_CREA 15
#define MAX_EMAIL 100


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

// Estrutura principal para o relatório da obra
typedef struct {
    InformacoesObra infoObra;
    DatasObra datas;
    InformacoesFinanceiras financas;
    ResponsavelTecnico responsaveis[MAX_RESPONSAVEIS];
    int numResponsaveis;
    int faseObra;
} RelatorioObra;

// Prototipagem de funções:
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    processarDatas(dataInicio, dataTermino, dataAtual, diasPassados, diasRestantes, percentualPassado);
}

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
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
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
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o mês (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        return (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24); // Diferença em dias
    }

    // Função para ler uma data com validação
    void lerData(const char *mensagem, char *data) {
        do {
            printf("%s (dd/mm/aaaa): ", mensagem);
            scanf("%s", data);
            if (!validarData(data)) {
                printf("Data inválida. Digite novamente!\n");
            }
        } while (!validarData(data));
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

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal != 0) {
        *percentualPassado = (((float)*diasPassados) / duracaoTotal) * 100;
    } else {
        *percentualPassado = 0;
    }

    // Verificar se a data atual é posterior à data de término
    if (*diasRestantes < 0) {
        printf("A obra está atrasada em %d dias.\n", -(*diasRestantes));
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
    // Limpar o buffer de entrada antes de ler o nome do mestre de obras
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // Obter o nome do mestre de obras
    printf("Informe o nome do mestre de obras responsável: ");
    fgets(mestredeObras, MAX_MESTRE_OBRAS, stdin);
    
    //Remover o caractere de nova linha que o fgets adiciona
    mestredeObras[strcspn(mestredeObras, "\n")] = 0;

    //Verificar se o nome foi preenchido:
    if (strlen(mestredeObras) == 0) {
        printf("O nome do mestre de obras não pode estar vazio. Digite novamente!\n");
        while (getchar() != '\n'); // Limpa o buffer até o final da linha
        return;
    }

    //Verificar a presença de caracteres inválidos (simplificado)
    for (int i = 0; mestredeObras[i] != '\0'; i++) {
        if (!isalpha(mestredeObras[i]) && mestredeObras[i] != ' ' && mestredeObras[i] != '-' && mestredeObras[i] != '\'') {
            printf("Erro: O nome do mestre de obras contém caracteres inválidos.\n");
            return 1; // Indicar erro
        }
    }

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
    int c;
    
    //Limapr o buffer de entrada antes de ler o nome do responsável técnico
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome do responsável técnico: Eng. ");
    fgets(responsavel->nome, MAX_NOME, stdin);

    // Remover o caractere de nova linha que o fgets adiciona:
    responsavel->nome[strcspn(responsavel->nome, "\n")] = 0;

    // 1. Verificar se o nome foi preenchido
    if (strlen(responsavel->nome) == 0) {
        printf("O nome do responsável técnico não pode estar vazio. Digite novamente!\n");
        //Trata o erro, por exemplo, solicitando novamente
        return;
    }

    // 2. Verificar a presença de caracteres inválidos
    for (int i = 0; responsavel->nome[i] != '\0'; i++) {
        if (!isalpha(responsavel->nome[i]) && responsavel->nome[i] != ' ' && responsavel->nome[i] != '-' && responsavel->nome[i] != '\'') {
            printf("Erro: O nome do responsável técnico contém caracteres inválidos.\n");
            return 1; // Indicar erro
        }
    }

    // 3. Formatar o nome (primeira letra de cada palavra maiúscula)
    for (int i = 0; responsavel->nome[i] != '\0'; i++) {
        if (i == 0 || responsavel->nome[i - 1] == ' ') {
            responsavel->nome[i] = toupper(responsavel->nome[i]);
        } else {
            responsavel->nome[i] = tolower(responsavel->nome[i]);
        }
    }

    // Verificação do numero do CREA

    int valido1;
    char buffer[MAX_CREA]; // Buffer para leitura da entrada

    do {
        valido1 = 1; // Assumir que o CREA é válido inicialmente

        printf("Digite o número CREA do responsável técnico: ");
        fgets(buffer, MAX_CREA, stdin);

        // Remover o caractere de nova linha que o fgets pode adicionar
        buffer[strcspn(buffer, "\n")] = 0; 

        // Copiar o buffer para a struct, após validação
        strcpy(responsavel->numeroCREA, buffer);

        // 1. Verificar se o CREA foi preenchido
        if (strlen(responsavel->numeroCREA) == 0) {
            valido1 = 0; 
        }

        // 2. Verificar o tamanho do CREA (ajuste o tamanho conforme o estado)
        if (strlen(responsavel->numeroCREA) != 12) { 
            valido1 = 0; 
        }

        // 3. Verificar o formato do CREA (simplificado)
        for (int i = 0; responsavel->numeroCREA[i] != '\0'; i++) {
            if (!isdigit(responsavel->numeroCREA[i]) && (i != 6 || responsavel->numeroCREA[i] != '-')) { 
                valido1 = 0; 
                break; 
            }
        }

        if (!valido1) {
            printf("CREA inválido. Digite novamente. Certifique-se de que o número tem 12 dígitos. \n");
        }

    } while (!valido1);

    // Validação de emails:
    int valido2;
    do {
        // Código para ler o email
        printf("Digite o email do responsável técnico: ");
        fgets(responsavel->email, 100, stdin); // Usando fgets para ler a entrada
        responsavel->email[strcspn(responsavel->email, "\n")] = 0; // Remover o '\n'

        // Validação do email
        valido2 = 1; // Assumir que o email é válido inicialmente

        int temArroba = 0, temPonto = 0;
        int posicaoArroba = -1, posicaoPonto = -1;

        // Verificar se o email está vazio
        if (strlen(responsavel->email) == 0) {
            valido2 = 0; // Email inválido
        } else {
            // Verificar a presença e posição de "@" e "."
            for (int i = 0; responsavel->email[i] != '\0'; i++) {
                if (responsavel->email[i] == '@') {
                    if (temArroba || i == 0 || i == strlen(responsavel->email) - 1) {
                        valido2 = 0; // Email inválido
                        break;
                    }
                    temArroba = 1;
                    posicaoArroba = i;
                } else if (responsavel->email[i] == '.') {
                    if (!temArroba || i < posicaoArroba + 2 || i == strlen(responsavel->email) - 1) {
                        valido2 = 0; // Email inválido
                        break;
                    }
                    temPonto = 1;
                    posicaoPonto = i;
                }
            }

            // Verificar se tem "@" e "."
            if (!temArroba || !temPonto) {
                valido2 = 0; // Email inválido
            }
        }

        if (!valido2) {
            // Email inválido
            printf("Email inválido. Certifique-se de que o email esteja no formato nome@exemplo.com.\n");
        }
    } while (!valido2);

    // Validação do telefone
    int valido3;
    do {
        valido3 = 1; // Assumir que o telefone é válido inicialmente

        printf("Digite o telefone do responsável técnico com o DDD (ex: 046999768334): ");
        fgets(responsavel->telefone, MAX_TELEFONE, stdin);
        responsavel->telefone[strcspn(responsavel->telefone, "\n")] = 0;

        // 1. Verificar se o telefone foi preenchido
        if (strlen(responsavel->telefone) == 0) {
            valido3 = 0;
        }

        // 2. Verificar o tamanho do telefone (11 dígitos com DDD)
        if (strlen(responsavel->telefone) != 11) {
            valido3 = 0;
        }

        // 3. Verificar se contém apenas dígitos
        for (int i = 0; responsavel->telefone[i] != '\0'; i++) {
            if (!isdigit(responsavel->telefone[i])) {
                valido3 = 0;
                break;
            }
        }

        if (!valido3) {
            printf("Telefone inválido. Digite um número com 11 dígitos, incluindo o DDD.\n");
        }
    } while (!valido3);
}

// Função para gerar o relatório
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
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
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
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
        case 5: printf("Conclusão\n"); break;
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

                // Gerando o relatório
                gerarRelatorio(arquivo, relatorio.infoObra.nomeObra, relatorio.datas.dataInicio, relatorio.datas.dataTermino, relatorio.datas.diasPassados, relatorio.datas.diasRestantes, relatorio.datas.pctPassado, relatorio.responsaveis, relatorio.numResponsaveis, relatorio.financas.orcamentoTotal, relatorio.financas.gastoAtual, relatorio.financas.orcamentoRestante, relatorio.financas.pctGasto, relatorio.infoObra.mestredeObras, relatorio.financas.salarioTotal, relatorio.financas.pctOrcGastoFuncionarios, relatorio.faseObra);

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