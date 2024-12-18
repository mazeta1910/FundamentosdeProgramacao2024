#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

// Prot�tipos das fun��es
int validarData(const char *data);
int calcularDuracao(const char *dataTermino, const char *dataInicio);

//Fun��o para calcular a % do or�amento gasto
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

// Fun��o para ler e validar datas de in�cio, t�rmino e atual.
int validarDatas(char *dataInicio, char *dataTermino, char *dataAtual) {
    // Converter as datas para o formato time_t
    struct tm tmInicio, tmTermino, tmAtual;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));
    memset(&tmAtual, 0, sizeof(struct tm));

    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);
    sscanf(dataAtual, "%d/%d/%d", &tmAtual.tm_mday, &tmAtual.tm_mon, &tmAtual.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o m�s (0-11)
    tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
    tmTermino.tm_mon -= 1;
    tmTermino.tm_year -= 1900;
    tmAtual.tm_mon -= 1;
    tmAtual.tm_year -= 1900;

    time_t tempoInicio = mktime(&tmInicio);
    time_t tempoTermino = mktime(&tmTermino);
    time_t tempoAtual = mktime(&tmAtual);

    // Verificar se a data de t�rmino � posterior � data de in�cio
    if (tempoTermino <= tempoInicio) {
        printf("Data de t�rmino inv�lida. A data de t�rmino deve ser posterior � data de in�cio.\n");
        return 0; // Indicar erro na valida��o
    }

    // Verificar se a data atual est� dentro do per�odo da obra
    if (tempoAtual < tempoInicio || tempoAtual > tempoTermino) {
        printf("Data atual inv�lida. A data atual deve estar entre a data de in�cio e a data de t�rmino.\n");
        return 0; // Indicar erro na valida��o
    }

    return 1; // Indicar sucesso na valida��o
}

// Fun��o para ler e validar datas de in�cio, t�rmino e atual.
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    // Fun��o auxiliar para ler a data formatada
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
        if (calcularDuracao(dataTermino, dataInicio) < 0) {
            printf("Data de t�rmino inv�lida. A data de t�rmino deve ser posterior � data de in�cio.\n");
        }
    } while (calcularDuracao(dataTermino, dataInicio) < 0);

    // Ler a data atual e validar em rela��o � data de in�cio
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataAtual, dataInicio) < 0) {
            printf("Data atual inv�lida. A data atual deve ser posterior � data de in�cio da obra.\n");
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

// Fun��o para calcular os dias �teis
int calcularDiasUteis(int mes, int ano) {
    struct tm data;
    time_t diasNoMes = mktime(&data); // Corrigido: usar time_t para diasNoMes
    data.tm_year = ano - 1900;
    data.tm_mon = mes - 1;

    // Calcula o n�mero de dias no m�s
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

//Fun��o para calcular as horas trabalhadas em um m�s
int calcularHorasTrabalhadasMes(int horasTrabalhadasDia, int mes, int ano) {
    int diasUteis = calcularDiasUteis(mes, ano);
    return horasTrabalhadasDia * diasUteis;
}

// Fun��o para obter e validar o or�amento total
float obterOrcamentoTotal() {
    float orcamentoTotal;
    do {
        printf("Digite o or�amento total da obra: R$ ");
        scanf("%f", &orcamentoTotal);
        if (orcamentoTotal <= 0) {
            printf("O or�amento total deve ser maior que zero. Digite novamente!\n");
        }
    } while (orcamentoTotal <= 0);
    return orcamentoTotal;
}

// Fun��o para obter informa��es sobre a equipe
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios) {
    printf("Informe o nome do mestre de obras respons�vel: ");
    scanf(" %[^\n]", mestredeObras);

    printf("Informe quantos funcion�rios est�o trabalhando na obra: ");
    scanf("%d", qtdFuncionarios);

}

// Fun��o para calcular o sal�rio dos funcion�rios
void calcularSalarioFuncionarios(float custoMaoDeObra, int horasTrabalhadasMes, int qtdFuncionarios, float *salarioTotal, float *gastoTotal) {
    // Calcular o sal�rio mensal dos funcion�rios
    float salarioMensal = custoMaoDeObra * horasTrabalhadasMes;

    // Calcular o sal�rio total dos funcion�rios
    *salarioTotal = qtdFuncionarios * salarioMensal;

    // Calcular o gasto total com sal�rios
    *gastoTotal = *salarioTotal;
}

// Fun��o para obter o nome do respons�vel t�cnico
void obterResponsavelTecnico(char *responsavel) {
    printf("Digite o nome do respons�vel t�cnico: ");
    scanf(" %[^\n]", responsavel);
}

//Fun��o para gerar o relat�rio
void gerarRelatorio(FILE *arquivo, char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, int atraso, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    
    int horasTrabalhadasDia, mes, ano;

    // Calcular o total de horas trabalhadas no m�s
    int horasTrabalhadasMes = calcularHorasTrabalhadasMes(horasTrabalhadasDia, mes, ano);
    
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

    if(atraso > 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes);
        printf("Tempo do prazo excedido: %d\n", diasRestantes);
    }else{
        fprintf(arquivo, "Dias restantes para conclus�o: %d\n", diasRestantes);
        printf("Dias restantes para conclus�o: %d\n", diasRestantes);
    }
    
    if (atraso > 0){
        fprintf(arquivo, "A obra est� %d dias atrasada.\n", atraso);
        printf("A obra est� %d dias atrasada.\n", atraso);
    }

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

    fprintf(arquivo, "Nome do Mestre de obras: %s\n", mestredeObras);
    printf("Mestre de obras: %s\n", mestredeObras);

    fprintf(arquivo, "Gasto total com sal�rio de funcion�rios: R$ %.2f\n", salarioTotal);
    printf("Gasto total com sal�rio de funcion�rios: R$ %.2f\n", salarioTotal);

    fprintf(arquivo, "Quantidade de horas trabalhadas no m�s pelos funcion�rios: %d\n", horasTrabalhadasMes);
    printf("Quantidade de horas trabalhadas no m�s pelos funcion�rios: %d\n", horasTrabalhadasMes);

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

// Fun��o para determinar custo da m�o de obra por hora por UF (Retirado da Tabela SINAPI)
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
        return -1; // Estado inv�lido
    }
}

// Fun��o main
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
    int faseObra, qtdFuncionarios, diasPassados, diasRestantes, atraso;
    float orcamentoTotal, gastoAtual, pctGasto, salarioFuncionarios, pctOrcGastoFuncionarios, pctPassado;

    // Definindo categorias de despesas
    #define NUM_CATEGORIAS 5
    const char *categoriasDespesas[NUM_CATEGORIAS] = {
        "Materiais",
        "M�o de obra terceirizada",
        "Aluguel de equipamentos",
        "Transporte",
        "Outros"
    };
    float despesas[NUM_CATEGORIAS] = {0};

    // Coletando as informa��es
    printf("=== Gerador de Relat�rio de Obra ===\n");
    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", nomeObra);

    // Obter e validar as datas
    obterDatasValidas(dataInicio, dataTermino, dataAtual, &diasPassados, &diasRestantes, &pctPassado);

    // Usando as fun��es para obter as informa��es
    orcamentoTotal = obterOrcamentoTotal();
    obterInformacoesEquipe(mestredeObras, &qtdFuncionarios, &salarioFuncionarios);
    obterResponsavelTecnico(responsavel);

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

    // Calcular o sal�rio e o gasto total com sal�rios
    float salarioTotal, gastoComSalarios;
    calcularSalarioFuncionarios(custoMaoDeObra, horasTrabalhadasMes, qtdFuncionarios, &salarioTotal, &gastoComSalarios);

    // Adicionar o gasto com sal�rios dos funcion�rios
    gastoAtual += gastoComSalarios;

    // Calculando a porcentagem do or�amento gasta
    pctGasto = calculoPorcentagemOrcGasto(orcamentoTotal, gastoAtual);

    // Calculando a porcentagem do or�amento gasta com funcion�rios
    pctOrcGastoFuncionarios = calculoOrcamentoFuncionarios(orcamentoTotal, salarioTotal);

    // Calculando o or�amento restante
    float orcamentoRestante = orcamentoTotal - gastoAtual;

    // Entrada e valida��o da fase da obra:
    do {
        printf("Digite a fase atual da obra (1-In�cio, 2-Funda��o, 3-Estrutura, 4-Acabamento, 5-Conclus�o): ");
        scanf("%d", &faseObra);
        if (faseObra < 1 || faseObra > 5) {
            printf("Fase inv�lida! Digite uma fase entre 1 e 5.\n");
        }
    } while (faseObra < 1 || faseObra > 5);

    // Chamando a fun��o gerarRelatorio
    gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, atraso, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

    // Fechando o arquivo
    fclose(arquivo);

    printf("Relat�rio gerado com sucesso!\n");

    return 0;
}