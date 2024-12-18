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

    int calcularDuracao(const char *dataInicio, const char *dataTermino) {
        struct tm tmInicio, tmTermino;
    memset(&tmInicio, 0, sizeof(struct tm));
    memset(&tmTermino, 0, sizeof(struct tm));

    // Converte as strings de data para o tipo struct tm
    sscanf(dataInicio, "%d/%d/%d", &tmInicio.tm_mday, &tmInicio.tm_mon, &tmInicio.tm_year);
    sscanf(dataTermino, "%d/%d/%d", &tmTermino.tm_mday, &tmTermino.tm_mon, &tmTermino.tm_year);

    tmInicio.tm_mon -= 1;  // Ajusta o m�s (0-11)
    tmInicio.tm_year -= 1900; // Ajusta o ano (anos desde 1900)
    tmTermino.tm_mon -= 1;
    tmTermino.tm_year -= 1900;

    // Converte as datas para segundos desde 1 de janeiro de 1970
    time_t tempoInicio = mktime(&tmInicio);
    time_t tempoTermino = mktime(&tmTermino);

    // Calcula a diferen�a em segundos e converte para dias
    double diffSegundos = difftime(tempoTermino, tempoInicio);
    int diffDias = (int)(diffSegundos / (60 * 60 * 24));

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
        if (calcularDuracao(dataTermino, dataInicio) <= 0) {
            printf("Data de t�rmino inv�lida. A data de t�rmino deve ser posterior � data de in�cio.\n");
        }
    } while (calcularDuracao(dataTermino, dataInicio) <= 0);

    // Ler a data atual e validar em rela��o ao intervalo
    do {
        lerData("Digite a data atual", dataAtual);
        if (calcularDuracao(dataAtual, dataInicio) <= 0 || calcularDuracao(dataTermino, dataAtual) <= 0) {
            printf("Data atual inv�lida. A data atual deve estar entre a data de in�cio e a data de t�rmino.\n");
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