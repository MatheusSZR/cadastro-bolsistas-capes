#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1024
#define MAX_NOMES 10000
#define MAX_NOME 300

long long comparacoes = 0;
int nomes_inseridos = 0;

typedef struct {
    char nome[MAX_NOME];
    char linha[MAX_LINHA];
} Registro;

void removerQuebraLinha(char *texto) {
    texto[strcspn(texto, "\r\n")] = '\0';
}

void obterNome(const char *linha, char *nome) {
    int i = 0;

    while (linha[i] != ',' && linha[i] != '\0' && i < MAX_NOME - 1) {
        nome[i] = linha[i];
        i++;
    }

    nome[i] = '\0';
}

int nomeExiste(Registro registros[], int quantidade, const char *nome) {
    for (int i = 0; i < quantidade; i++) {
        comparacoes++;

        if (strcmp(registros[i].nome, nome) == 0) {
            return 1;
        }
    }

    return 0;
}

int carregarDestino(FILE *arquivo, Registro registros[]) {
    char linha[MAX_LINHA];
    int quantidade = 0;

    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        removerQuebraLinha(linha);

        if (quantidade >= MAX_NOMES) {
            break;
        }

        strcpy(registros[quantidade].linha, linha);
        obterNome(linha, registros[quantidade].nome);

        quantidade++;
    }

    return quantidade;
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Uso: %s <origem.csv> <destino.csv> <estatisticas.csv>\n", argv[0]);
        return 1;
    }

    const char *arquivoOrigem = argv[1];
    const char *arquivoDestino = argv[2];
    const char *arquivoEstatisticas = argv[3];

    FILE *origem = fopen(arquivoOrigem, "r");

    if (origem == NULL) {
        printf("Erro ao abrir o arquivo de origem.\n");
        return 1;
    }

    FILE *destino = fopen(arquivoDestino, "a+");

    if (destino == NULL) {
        printf("Erro ao abrir o arquivo de destino.\n");
        fclose(origem);
        return 1;
    }

    Registro *registros = malloc(MAX_NOMES * sizeof(Registro));

if (registros == NULL) {
    printf("Erro ao alocar memoria.\n");
    fclose(origem);
    fclose(destino);
    return 1;
}

    rewind(destino);

    int quantidadeDestino = carregarDestino(destino, registros);

    fclose(destino);

    destino = fopen(arquivoDestino, "a");

    if (destino == NULL) {
        printf("Erro ao reabrir o arquivo de destino.\n");
        fclose(origem);
        return 1;
    }

    char linha[MAX_LINHA];

    fgets(linha, sizeof(linha), origem);

    while (fgets(linha, sizeof(linha), origem) != NULL) {

        removerQuebraLinha(linha);

        char nome[MAX_NOME];

        obterNome(linha, nome);

        if (nomeExiste(registros, quantidadeDestino, nome)) {

            printf("ERRO: nome redundante encontrado: %s\n", nome);

        } else {

            fprintf(destino, "%s\n", linha);

            strcpy(registros[quantidadeDestino].linha, linha);
            strcpy(registros[quantidadeDestino].nome, nome);

            quantidadeDestino++;
            nomes_inseridos++;
        }
    }

    fclose(origem);
    fclose(destino);

    FILE *estatisticas = fopen(arquivoEstatisticas, "w");

    if (estatisticas == NULL) {
        printf("Erro ao criar o arquivo de estatisticas.\n");
        return 1;
    }

    fprintf(estatisticas, "nomes_inseridos,comparacoes\n");
    fprintf(estatisticas, "%d,%lld\n", nomes_inseridos, comparacoes);

    fclose(estatisticas);
    free(registros);

    printf("\nProcessamento concluido.\n");
    printf("Nomes inseridos: %d\n", nomes_inseridos);
    printf("Comparacoes realizadas: %lld\n", comparacoes);

    return 0;
}