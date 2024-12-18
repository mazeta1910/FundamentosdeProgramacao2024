#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Defini��es gerais
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

// Estrutura principal para o relat�rio da obra
typedef struct {
    InformacoesObra infoObra;
    DatasObra datas;
    InformacoesFinanceiras financas;
    ResponsavelTecnico responsaveis[MAX_RESPONSAVEIS];
    int numResponsaveis;
    int faseObra;
} RelatorioObra;

// Prototipagem de fun��es:
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    processarDatas(dataInicio, dataTermino, dataAtual, diasPassados, diasRestantes, percentualPassado);
}

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
void processarDatas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
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
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

        tmInicio.tm_mon -= 1; // Ajusta o m�s (0-11)
        tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        return (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24); // Diferen�a em dias
    }

    // Fun��o para ler uma data com valida��o
    void lerData(const char *mensagem, char *data) {
        do {
            printf("%s (dd/mm/aaaa): ", mensagem);
            scanf("%s", data);
            if (!validarData(data)) {
                printf("Data inv�lida. Digite novamente!\n");
            }
        } while (!validarData(data));
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

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal != 0) {
        *percentualPassado = (((float)*diasPassados) / duracaoTotal) * 100;
    } else {
        *percentualPassado = 0;
    }

    // Verificar se a data atual � posterior � data de t�rmino
    if (*diasRestantes < 0) {
        printf("A obra est� atrasada em %d dias.\n", -(*diasRestantes));
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
    // Limpar o buffer de entrada antes de ler o nome do mestre de obras
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // Obter o nome do mestre de obras
    printf("Informe o nome do mestre de obras respons�vel: ");
    fgets(mestredeObras, MAX_MESTRE_OBRAS, stdin);
    
    //Remover o caractere de nova linha que o fgets adiciona
    mestredeObras[strcspn(mestredeObras, "\n")] = 0;

    //Verificar se o nome foi preenchido:
    if (strlen(mestredeObras) == 0) {
        printf("O nome do mestre de obras n�o pode estar vazio. Digite novamente!\n");
        while (getchar() != '\n'); // Limpa o buffer at� o final da linha
        return;
    }

    //Verificar a presen�a de caracteres inv�lidos (simplificado)
    for (int i = 0; mestredeObras[i] != '\0'; i++) {
        if (!isalpha(mestredeObras[i]) && mestredeObras[i] != ' ' && mestredeObras[i] != '-' && mestredeObras[i] != '\'') {
            printf("Erro: O nome do mestre de obras cont�m caracteres inv�lidos.\n");
            return 1; // Indicar erro
        }
    }

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
    int c;
    
    //Limapr o buffer de entrada antes de ler o nome do respons�vel t�cnico
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome do respons�vel t�cnico: Eng. ");
    fgets(responsavel->nome, MAX_NOME, stdin);

    // Remover o caractere de nova linha que o fgets adiciona:
    responsavel->nome[strcspn(responsavel->nome, "\n")] = 0;

    // 1. Verificar se o nome foi preenchido
    if (strlen(responsavel->nome) == 0) {
        printf("O nome do respons�vel t�cnico n�o pode estar vazio. Digite novamente!\n");
        //Trata o erro, por exemplo, solicitando novamente
        return;
    }

    // 2. Verificar a presen�a de caracteres inv�lidos
    for (int i = 0; responsavel->nome[i] != '\0'; i++) {
        if (!isalpha(responsavel->nome[i]) && responsavel->nome[i] != ' ' && responsavel->nome[i] != '-' && responsavel->nome[i] != '\'') {
            printf("Erro: O nome do respons�vel t�cnico cont�m caracteres inv�lidos.\n");
            return 1; // Indicar erro
        }
    }

    // 3. Formatar o nome (primeira letra de cada palavra mai�scula)
    for (int i = 0; responsavel->nome[i] != '\0'; i++) {
        if (i == 0 || responsavel->nome[i - 1] == ' ') {
            responsavel->nome[i] = toupper(responsavel->nome[i]);
        } else {
            responsavel->nome[i] = tolower(responsavel->nome[i]);
        }
    }

    // Verifica��o do numero do CREA

    int valido1;
    char buffer[MAX_CREA]; // Buffer para leitura da entrada

    do {
        valido1 = 1; // Assumir que o CREA � v�lido inicialmente

        printf("Digite o n�mero CREA do respons�vel t�cnico: ");
        fgets(buffer, MAX_CREA, stdin);

        // Remover o caractere de nova linha que o fgets pode adicionar
        buffer[strcspn(buffer, "\n")] = 0; 

        // Copiar o buffer para a struct, ap�s valida��o
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
            printf("CREA inv�lido. Digite novamente. Certifique-se de que o n�mero tem 12 d�gitos. \n");
        }

    } while (!valido1);

    // Valida��o de emails:
    int valido2;
    do {
        // C�digo para ler o email
        printf("Digite o email do respons�vel t�cnico: ");
        fgets(responsavel->email, 100, stdin); // Usando fgets para ler a entrada
        responsavel->email[strcspn(responsavel->email, "\n")] = 0; // Remover o '\n'

        // Valida��o do email
        valido2 = 1; // Assumir que o email � v�lido inicialmente

        int temArroba = 0, temPonto = 0;
        int posicaoArroba = -1, posicaoPonto = -1;

        // Verificar se o email est� vazio
        if (strlen(responsavel->email) == 0) {
            valido2 = 0; // Email inv�lido
        } else {
            // Verificar a presen�a e posi��o de "@" e "."
            for (int i = 0; responsavel->email[i] != '\0'; i++) {
                if (responsavel->email[i] == '@') {
                    if (temArroba || i == 0 || i == strlen(responsavel->email) - 1) {
                        valido2 = 0; // Email inv�lido
                        break;
                    }
                    temArroba = 1;
                    posicaoArroba = i;
                } else if (responsavel->email[i] == '.') {
                    if (!temArroba || i < posicaoArroba + 2 || i == strlen(responsavel->email) - 1) {
                        valido2 = 0; // Email inv�lido
                        break;
                    }
                    temPonto = 1;
                    posicaoPonto = i;
                }
            }

            // Verificar se tem "@" e "."
            if (!temArroba || !temPonto) {
                valido2 = 0; // Email inv�lido
            }
        }

        if (!valido2) {
            // Email inv�lido
            printf("Email inv�lido. Certifique-se de que o email esteja no formato nome@exemplo.com.\n");
        }
    } while (!valido2);

    // Valida��o do telefone
    int valido3;
    do {
        valido3 = 1; // Assumir que o telefone � v�lido inicialmente

        printf("Digite o telefone do respons�vel t�cnico com o DDD (ex: 046999768334): ");
        fgets(responsavel->telefone, MAX_TELEFONE, stdin);
        responsavel->telefone[strcspn(responsavel->telefone, "\n")] = 0;

        // 1. Verificar se o telefone foi preenchido
        if (strlen(responsavel->telefone) == 0) {
            valido3 = 0;
        }

        // 2. Verificar o tamanho do telefone (11 d�gitos com DDD)
        if (strlen(responsavel->telefone) != 11) {
            valido3 = 0;
        }

        // 3. Verificar se cont�m apenas d�gitos
        for (int i = 0; responsavel->telefone[i] != '\0'; i++) {
            if (!isdigit(responsavel->telefone[i])) {
                valido3 = 0;
                break;
            }
        }

        if (!valido3) {
            printf("Telefone inv�lido. Digite um n�mero com 11 d�gitos, incluindo o DDD.\n");
        }
    } while (!valido3);
}

// Fun��o para gerar o relat�rio
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
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
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, ResponsavelTecnico responsaveis[], int numResponsaveis, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
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
        case 5: printf("Conclus�o\n"); break;
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

                // Gerando o relat�rio
                gerarRelatorio(arquivo, relatorio.infoObra.nomeObra, relatorio.datas.dataInicio, relatorio.datas.dataTermino, relatorio.datas.diasPassados, relatorio.datas.diasRestantes, relatorio.datas.pctPassado, relatorio.responsaveis, relatorio.numResponsaveis, relatorio.financas.orcamentoTotal, relatorio.financas.gastoAtual, relatorio.financas.orcamentoRestante, relatorio.financas.pctGasto, relatorio.infoObra.mestredeObras, relatorio.financas.salarioTotal, relatorio.financas.pctOrcGastoFuncionarios, relatorio.faseObra);

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