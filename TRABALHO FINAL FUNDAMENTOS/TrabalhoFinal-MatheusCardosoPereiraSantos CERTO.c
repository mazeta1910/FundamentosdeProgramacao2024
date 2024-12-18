#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

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

//Fun��o para obter datas v�lidas:
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    
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

    int calcularDuracao(const char *dataTermino, const char *dataInicio) {
        struct tm tmInicio, tmTermino;
        memset(&tmInicio, 0, sizeof(struct tm));
        memset(&tmTermino, 0, sizeof(struct tm));

        sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
        sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

        tmInicio.tm_mon -= 1;
        tmInicio.tm_year -= 1900;
        tmTermino.tm_mon -= 1;
        tmTermino.tm_year -= 1900;

        time_t tempoInicio = mktime(&tmInicio);
        time_t tempoTermino = mktime(&tmTermino);

        // Calcula a diferen�a em dias usando mktime e struct tm
        int diffDias = (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24);

        return diffDias;
    }

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
    *diasPassados = calcularDuracao(dataAtual, dataInicio); // Argumentos corrigidos
    *diasRestantes = calcularDuracao(dataTermino, dataAtual); // Argumentos corrigidos

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
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios, float *salarioFuncionarios) {
    printf("Informe o nome do mestre de obras respons�vel: ");
    scanf(" %[^\n]", mestredeObras);

    printf("Informe quantos funcion�rios est�o trabalhando na obra: ");
    scanf("%d", qtdFuncionarios);

    printf("Informe o sal�rio desses funcion�rios: R$ ");
    scanf("%f", salarioFuncionarios);
}

// Fun��o para obter o nome do respons�vel t�cnico
void obterResponsavelTecnico(char *responsavel) {
    printf("Digite o nome do respons�vel t�cnico: ");
    scanf(" %[^\n]", responsavel);
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

    if(diasRestantes < 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes*-1);
        printf("Tempo do prazo excedido: %d\n", diasRestantes*-1);
    }else{
        fprintf(arquivo, "Dias restantes para conclus�o: %d\n", diasRestantes);
        printf("Dias restantes para conclus�o: %d\n", diasRestantes);
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

//Fun��o para exibir o relat�rio
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    printf("\n=== Relat�rio da Obra ===\n");
    printf("Nome da obra: %s\n", nomeObra);
    printf("Data de in�cio: %s\n", dataInicio);
    printf("Data de t�rmino prevista: %s\n", dataTermino);
    printf("Dias de obra: %d\n", diasPassados);

    if(diasRestantes < 0) {
        printf("Tempo do prazo excedido: %d\n", diasRestantes*-1);
    }else{
        printf("Dias restantes para conclus�o: %d\n", diasRestantes);
    }

    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Respons�vel t�cnico: %s\n", responsavel);
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

// Fun��o main

int main() {
    // Configura��o para o idioma portugu�s
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        // Exibir o menu de op��es
        printf("\n=== Menu ===\n");
        printf("1. Gerar novo relat�rio\n");
        printf("2. Visualizar relat�rios existentes\n"); // Nova op��o
        printf("0. Sair\n");
        printf("Digite a op��o desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
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

                // Adicionar o gasto com sal�rios dos funcion�rios
                float salarioTotal = qtdFuncionarios * salarioFuncionarios;
                gastoAtual += salarioTotal;

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

                // Chamando a fun��o gerarRelatorio para salvar o relat�rio no arquivo
                gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

                // Chamando a fun��o exibirRelatorio para exibir o relat�rio na tela
                exibirRelatorio(nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

                // Fechando o arquivo
                fclose(arquivo);

                printf("Relat�rio gerado com sucesso!\n");
                break;
            }
            case 2:
                // Implementar a funcionalidade para visualizar relat�rios existentes
                printf("Funcionalidade ainda n�o implementada.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while (opcao != 0);

    return 0;
}