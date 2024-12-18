#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

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

//Função para obter datas válidas:
void obterDatasValidas(char *dataInicio, char *dataTermino, char *dataAtual, int *diasPassados, int *diasRestantes, float *percentualPassado) {
    
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

        // Calcula a diferença em dias usando mktime e struct tm
        int diffDias = (int)difftime(tempoTermino, tempoInicio) / (60 * 60 * 24);

        return diffDias;
    }

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
    *diasPassados = calcularDuracao(dataAtual, dataInicio); // Argumentos corrigidos
    *diasRestantes = calcularDuracao(dataTermino, dataAtual); // Argumentos corrigidos

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
void obterInformacoesEquipe(char *mestredeObras, int *qtdFuncionarios, float *salarioFuncionarios) {
    printf("Informe o nome do mestre de obras responsável: ");
    scanf(" %[^\n]", mestredeObras);

    printf("Informe quantos funcionários estão trabalhando na obra: ");
    scanf("%d", qtdFuncionarios);

    printf("Informe o salário desses funcionários: R$ ");
    scanf("%f", salarioFuncionarios);
}

// Função para obter o nome do responsável técnico
void obterResponsavelTecnico(char *responsavel) {
    printf("Digite o nome do responsável técnico: ");
    scanf(" %[^\n]", responsavel);
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

    if(diasRestantes < 0) {
        fprintf(arquivo, "Tempo do prazo excedido: %d\n", diasRestantes*-1);
        printf("Tempo do prazo excedido: %d\n", diasRestantes*-1);
    }else{
        fprintf(arquivo, "Dias restantes para conclusão: %d\n", diasRestantes);
        printf("Dias restantes para conclusão: %d\n", diasRestantes);
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

//Função para exibir o relatório
void exibirRelatorio(char *nomeObra, char *dataInicio, char *dataTermino, int diasPassados, int diasRestantes, float pctPassado, char *responsavel, float orcamentoTotal, float gastoAtual, float orcamentoRestante, float pctGasto, char *mestredeObras, float salarioTotal, float pctOrcGastoFuncionarios, int faseObra) {
    printf("\n=== Relatório da Obra ===\n");
    printf("Nome da obra: %s\n", nomeObra);
    printf("Data de início: %s\n", dataInicio);
    printf("Data de término prevista: %s\n", dataTermino);
    printf("Dias de obra: %d\n", diasPassados);

    if(diasRestantes < 0) {
        printf("Tempo do prazo excedido: %d\n", diasRestantes*-1);
    }else{
        printf("Dias restantes para conclusão: %d\n", diasRestantes);
    }

    printf("Percentual do prazo decorrido: %.2f%%\n", pctPassado);
    printf("Responsável técnico: %s\n", responsavel);
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

// Função main

int main() {
    // Configuração para o idioma português
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        // Exibir o menu de opções
        printf("\n=== Menu ===\n");
        printf("1. Gerar novo relatório\n");
        printf("2. Visualizar relatórios existentes\n"); // Nova opção
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
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

                // Adicionar o gasto com salários dos funcionários
                float salarioTotal = qtdFuncionarios * salarioFuncionarios;
                gastoAtual += salarioTotal;

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

                // Chamando a função gerarRelatorio para salvar o relatório no arquivo
                gerarRelatorio(arquivo, nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

                // Chamando a função exibirRelatorio para exibir o relatório na tela
                exibirRelatorio(nomeObra, dataInicio, dataTermino, diasPassados, diasRestantes, pctPassado, responsavel, orcamentoTotal, gastoAtual, orcamentoRestante, pctGasto, mestredeObras, salarioTotal, pctOrcGastoFuncionarios, faseObra);

                // Fechando o arquivo
                fclose(arquivo);

                printf("Relatório gerado com sucesso!\n");
                break;
            }
            case 2:
                // Implementar a funcionalidade para visualizar relatórios existentes
                printf("Funcionalidade ainda não implementada.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}