#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

// Protótipos das funções
int validarData(const char *data);
int calcularDuracao(const char *dataTermino, const char *dataInicio);

//Função para calcular a % do orçamento gasto
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

// Função para ler e validar datas de início, término e atual.
int validarDatas(char *dataInicio, char *dataTermino, char *dataAtual) {
    // Converter as datas para o formato time_t
    struct tm tmInicio, tmTermino, tmAtual;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));
    memset(&tmAtual, 0, sizeof(struct tm));

    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);
    sscanf(dataAtual, "%d/%d/%d", &tmAtual.tm_mday, &tmAtual.tm_mon, &tmAtual.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o mês (0-11)
    tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
    tmTermino.tm_mon -= 1;
    tmTermino.tm_year -= 1900;
    tmAtual.tm_mon -= 1;
    tmAtual.tm_year -= 1900;

    time_t tempoInicio = mktime(&tmInicio);
    time_t tempoTermino = mktime(&tmTermino);
    time_t tempoAtual = mktime(&tmAtual);

    // Verificar se a data de término é posterior à data de início
    if (tempoTermino <= tempoInicio) {
        printf("Data de término inválida. A data de término deve ser posterior à data de início.\n");
        return 0; // Indicar erro na validação
    }

    // Verificar se a data atual está dentro do período da obra
    if (tempoAtual < tempoInicio || tempoAtual > tempoTermino) {
        printf("Data atual inválida. A data atual deve estar entre a data de início e a data de término.\n");
        return 0; // Indicar erro na validação
    }

    return 1; // Indicar sucesso na validação
}

// Função para ler e validar datas de início, término e atual.
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    // Função auxiliar para ler a data formatada
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
        if (calcularDuracao(dataTermino, dataInicio) < 0) {
            printf("Data de término inválida. A data de término deve ser posterior à data de início.\n");
        }
    } while (calcularDuracao(dataTermino, dataInicio) < 0);

    // Ler a data atual e validar em relação à data de início
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataAtual, dataInicio) < 0) {
            printf("Data atual inválida. A data atual deve ser posterior à data de início da obra.\n");
        }
    } while (calcularDuracao(dataAtual, dataInicio) < 0);

    // Calcular o tempo da obra
    *diasPassados = calcularDuracao(dataAtual, dataInicio);
    *diasRestantes = calcularDuracao(dataTermino, dataAtual);

    int duracaoTotal = calcularDuracao(dataTermino, dataInicio);
    if (duracaoTotal != 0) {
        *percentualPassado = (((float)*diasPassados) / duracaoTotal) * 100;
    } else {
        *percentualPassado = 0;
    }
}

// Função para calcular os dias úteis
int calcularDiasUteis(int mes, int ano) {
    struct tm data;
    time_t diasNoMes = mktime(&data); // Corrigido: usar time_t para diasNoMes
    data.tm_year = ano - 1900;
    data.tm_mon = mes - 1;

    // Calcula o número de dias no mês
    struct tm *dataPtr = localtime(&diasNoMes);
    diasNoMes = dataPtr->tm_mday;

    for (int dia = 1; dia <= diasNoMes; dia++) {
        data.tm_mday = dia;
        mktime(&data);
        if (data.tm_wday != 0) {  // 0 representa domingo
            diasUteis++;
        }
    }

    return diasUteis;
}

//Função para calcular as horas trabalhadas em um mês
int calcularHorasTrabalhadasMes(int horasTrabalhadasDia, int mes, int ano) {
    int diasUteis = calcularDiasUteis(mes, ano);
    return horasTrabalhadasDia * diasUteis;
}

// Função para obter e validar o orçamento total
float obterOrcamentoTotal() {
    float orcamentoTotal;
    do {
        printf("Digite o orçamento total da obra: R$ ");
        scanf("%f", &orcamentoTotal);
        if (orcamentoTotal <= 0) {
            printf("O orçamento total deve ser maior que zero. Digite novamente!\n");
        }
    } while (orcamentoTotal <= 0);
    return orcamentoTotal;
}

// Função para obter informações sobre a equipe
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios) {
    printf("Informe o nome do mestre de obras responsável: ");
    scanf(" %[^\n]", mestredeObras);

    printf("Informe quantos funcionários estão trabalhando na obra: ");
    scanf("%d", qtdFuncionarios);

}

// Função para calcular o salário dos funcionários
void calcularSalarioFuncionarios(float custoMaoDeObra, int horasTrabalhadasMes, int qtdFuncionarios, float *salarioTotal, float *gastoTotal) {
    // Calcular o salário mensal dos funcionários
    float salarioMensal = custoMaoDeObra * horasTrabalhadasMes;

    // Calcular o salário total dos funcionários
    *salarioTotal = qtdFuncionarios * salarioMensal;

    // Calcular o gasto total com salários
    *gastoTotal = *salarioTotal;
}

// Função para obter o nome do responsável técnico
void obterResponsavelTecnico(char *responsavel) {
    printf("Digite o nome do responsável técnico: ");
    scanf(" %[^\n]", responsavel);
}

//Função para gerar o relatório
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, int atraso, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    
    int horasTrabalhadasDia, mes, ano;

    // Calcular o total de horas trabalhadas no mês
    int horasTrabalhadasMes = calcularHorasTrabalhadasMes(horasTrabalhadasDia, mes, ano);
    
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

    if(atraso > 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes);
        printf("Tempo do prazo excedido: %d\n", diasRestantes);
    }else{
        fprintf(arquivo, "Dias restantes para conclusão: %d\n", diasRestantes);
        printf("Dias restantes para conclusão: %d\n", diasRestantes);
    }
    
    if (atraso > 0){
        fprintf(arquivo, "A obra está %d dias atrasada.\n", atraso);
        printf("A obra está %d dias atrasada.\n", atraso);
    }

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

    fprintf(arquivo, "Nome do Mestre de obras: %s\n", mestredeObras);
    printf("Mestre de obras: %s\n", mestredeObras);

    fprintf(arquivo, "Gasto total com salário de funcionários: R$ %.2f\n", salarioTotal);
    printf("Gasto total com salário de funcionários: R$ %.2f\n", salarioTotal);

    fprintf(arquivo, "Quantidade de horas trabalhadas no mês pelos funcionários: %d\n", horasTrabalhadasMes);
    printf("Quantidade de horas trabalhadas no mês pelos funcionários: %d\n", horasTrabalhadasMes);

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

// Função para determinar custo da mão de obra por hora por UF (Retirado da Tabela SINAPI)
float obterCustoMaoDeObra(const char *estado) {
    if (strcmp(estado, "AC") == 0) {
        return 0.89;
    } else if (strcmp(estado, "AL") == 0) {
        return 0.34;
    } else if (strcmp(estado, "AP") == 0) {
        return 0.01;
    } else if (strcmp(estado, "AM") == 0) {
        return 0.52;
    } else if (strcmp(estado, "BA") == 0) {
        return 0.68;
    } else if (strcmp(estado, "CE") == 0) {
        return 0.46;
    } else if (strcmp(estado, "DF") == 0) {
        return 0.52;
    } else if (strcmp(estado, "ES") == 0) {
        return 0.31;
    } else if (strcmp(estado, "GO") == 0) {
        return 0.41;
    } else if (strcmp(estado, "MA") == 0) {
        return 0.01;
    } else if (strcmp(estado, "MT") == 0) {
        return 0.95;
    } else if (strcmp(estado, "MS") == 0) {
        return 0.68;
    } else if (strcmp(estado, "MG") == 0) {
        return 0.16;
    } else if (strcmp(estado, "PA") == 0) {
        return 0.51;
    } else if (strcmp(estado, "PB") == 0) {
        return 0.38;
    } else if (strcmp(estado, "PR") == 0) {
        return 0.64;
    } else if (strcmp(estado, "PE") == 0) {
        return 0.80;
    } else if (strcmp(estado, "PI") == 0) {
        return 0.27;
    } else if (strcmp(estado, "RJ") == 0) {
        return 1.02;
    } else if (strcmp(estado, "RN") == 0) {
        return 0.61;
    } else if (strcmp(estado, "RS") == 0) {
        return 1.04;
    } else if (strcmp(estado, "RO") == 0) {
        return 0.41;
    } else if (strcmp(estado, "RR") == 0) {
        return 0.55;
    } else if (strcmp(estado, "SC") == 0) {
        return 2.29;
    } else if (strcmp(estado, "SP") == 0) {
        return 0.68;
    } else if (strcmp(estado, "SE") == 0) {
        return 0.61;
    } else if (strcmp(estado, "TO") == 0) {
        return 0.33;
    } else {
        return -1; // Estado inválido
    }
}

// Função main
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
    int faseObra, qtdFuncionarios, diasPassados, diasRestantes, atraso;
    float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

    // Definindo categorias de despesas
    #define NUM_CATEGORIAS 5
    const char *categoriasDespesas[NUM_CATEGORIAS] = {
        "Materiais",
        "Mão de obra terceirizada",
        "Aluguel de equipamentos",
        "Transporte",
        "Outros"
    };
    float despesas[NUM_CATEGORIAS] = {0};

    // Coletando as informações
    printf("=== Gerador de Relatório de Obra ===\n");
    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", nomeObra);

    // Obter e validar as datas
    obterDatasValidas(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

    // Usando as funções para obter as informações
    orcamentoTotal = obterOrcamentoTotal();
    obterInformacoesEquipe(mestredeObras, &qtdFuncionarios, &salarioFuncionarios);
    obterResponsavelTecnico(responsavel);

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

    // Calcular o salário e o gasto total com salários
    float salarioTotal, gastoComSalarios;
    calcularSalarioFuncionarios(custoMaoDeObra, horasTrabalhadasMes, qtdFuncionarios, &salarioTotal, &gastoComSalarios);

    // Adicionar o gasto com salários dos funcionários
    gastoAtual += gastoComSalarios;

    // Calculando a porcentagem do orçamento gasta
    pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);

    // Calculando a porcentagem do orçamento gasta com funcionários
    pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);

    // Calculando o orçamento restante
    float orcamentoRestante = orcamentoTotal - gastoAtual;

    // Entrada e validação da fase da obra:
    do {
        printf("Digite a fase atual da obra (1-Início, 2-Fundação, 3-Estrutura, 4-Acabamento, 5-Conclusão): ");
        scanf("%d", &faseObra);
        if (faseObra < 1 || faseObra > 5) {
            printf("Fase inválida! Digite uma fase entre 1 e 5.\n");
        }
    } while (faseObra < 1 || faseObra > 5);

    // Chamando a função gerarRelatorio
    gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, atraso, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

    // Fechando o arquivo
    fclose(arquivo);

    printf("Relatório gerado com sucesso!\n");

    return 0;
}