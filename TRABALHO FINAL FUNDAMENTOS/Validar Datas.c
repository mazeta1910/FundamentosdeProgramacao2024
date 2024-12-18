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

    int calcularDuracao(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));

    // Converte as strings de data para o tipo struct tm
    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o mês (0-11)
    tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
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
        if (calcularDuracao(dataTermino, dataInicio) <= 0) {
            printf("Data de término inválida. A data de término deve ser posterior à data de início.\n");
        }
    } while (calcularDuracao(dataTermino, dataInicio) <= 0);

    // Ler a data atual e validar em relação ao intervalo
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataAtual, dataInicio) <= 0 || calcularDuracao(dataTermino, dataAtual) <= 0) {
            printf("Data atual inválida. A data atual deve estar entre a data de início e a data de término.\n");
        }
    } while (calcularDuracao(dataAtual, dataInicio) <= 0 || calcularDuracao(dataTermino, dataAtual) <= 0);

    // Calcular o tempo da obra
    *diasPassados = calcularDuracao(dataInicio, dataAtual);
    *diasRestantes = calcularDuracao(dataAtual, dataTermino);

    int duracaoTotal = calcularDuracao(dataInicio, dataTermino);
    if (duracaoTotal > 0) {
        *percentualPassado = (*diasPassados * 100.0f) / duracaoTotal;
    } else {
        *percentualPassado = 0.0f;
    }
}