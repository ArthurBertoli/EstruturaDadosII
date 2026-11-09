#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO "dados.dat"

typedef struct {
    char nome[50];
    char telefone[20];
    int dn_dia, dn_mes, dn_ano;
    char cidade[30];
    char cep[12];
    char email[50];
} Contato;

typedef struct {
    char cidade[30];
    int posicoes[MAX];
    int qtd;
} IndiceCidade;

IndiceCidade indices[MAX];
int totalIndices = 0;

// Função para carregar o índice invertido
void carregarIndice() {
    FILE *fp = fopen(ARQUIVO, "rb");
    if (!fp) return;

    Contato c;
    int pos = 0;
    while (fread(&c, sizeof(Contato), 1, fp)) {
        if (strcmp(c.nome, "__REMOVIDO__") == 0) {
            pos++;
            continue;
        }

        int i;
        for (i = 0; i < totalIndices; i++) {
            if (strcmp(indices[i].cidade, c.cidade) == 0) break;
        }

        if (i == totalIndices) {
            strcpy(indices[totalIndices].cidade, c.cidade);
            indices[totalIndices].qtd = 0;
            totalIndices++;
        }

        indices[i].posicoes[indices[i].qtd++] = pos;
        pos++;
    }
    fclose(fp);
}

// Listar pessoas por cidade
void listarPorCidade(char cidade[]) {
    int i;
    for (i = 0; i < totalIndices; i++) {
        if (strcmp(indices[i].cidade, cidade) == 0) break;
    }

    if (i == totalIndices) {
        printf("Nenhum registro encontrado para a cidade %s\n", cidade);
        return;
    }

    FILE *fp = fopen(ARQUIVO, "rb");
    Contato c;
    for (int j = 0; j < indices[i].qtd; j++) {
        fseek(fp, indices[i].posicoes[j] * sizeof(Contato), SEEK_SET);
        fread(&c, sizeof(Contato), 1, fp);
        printf("Nome: %s, Email: %s\n", c.nome, c.email);
    }
    fclose(fp);
}

// Adicionar novo contato
void adicionarContato() {
    FILE *fp = fopen(ARQUIVO, "ab");
    Contato c;

    printf("Nome: "); fgets(c.nome, 50, stdin); c.nome[strcspn(c.nome, "\n")] = '\0';
    printf("Telefone: "); fgets(c.telefone, 20, stdin); c.telefone[strcspn(c.telefone, "\n")] = '\0';
    printf("Nascimento (dia mes ano): "); scanf("%d %d %d", &c.dn_dia, &c.dn_mes, &c.dn_ano); getchar();
    printf("Cidade: "); fgets(c.cidade, 30, stdin); c.cidade[strcspn(c.cidade, "\n")] = '\0';
    printf("CEP: "); fgets(c.cep, 12, stdin); c.cep[strcspn(c.cep, "\n")] = '\0';
    printf("Email: "); fgets(c.email, 50, stdin); c.email[strcspn(c.email, "\n")] = '\0';

    fwrite(&c, sizeof(Contato), 1, fp);
    fclose(fp);

    printf("Contato adicionado com sucesso!\n");
}

// Excluir contato por nome
void excluirContato(char nome[]) {
    FILE *fp = fopen(ARQUIVO, "r+b");
    if (!fp) return;

    Contato c;
    int pos = 0;
    while (fread(&c, sizeof(Contato), 1, fp)) {
        if (strcmp(c.nome, nome) == 0) {
            strcpy(c.nome, "__REMOVIDO__");
            fseek(fp, pos * sizeof(Contato), SEEK_SET);
            fwrite(&c, sizeof(Contato), 1, fp);
            printf("Contato excluído com sucesso.\n");
            fclose(fp);
            return;
        }
        pos++;
    }

    printf("Contato não encontrado.\n");
    fclose(fp);
}

int main() {
    int opcao;
    char entrada[50];

    carregarIndice();

    do {
        printf("\n=== MENU ===\n");
        printf("1. Listar por cidade\n");
        printf("2. Adicionar contato\n");
        printf("3. Excluir contato por nome\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao); getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                printf("Digite a cidade: ");
                fgets(entrada, 30, stdin);
                entrada[strcspn(entrada, "\n")] = '\0';
                listarPorCidade(entrada);
                break;

            case 2:
                adicionarContato();
                break;

            case 3:
                printf("Digite o nome da pessoa a excluir: ");
                fgets(entrada, 50, stdin);
                entrada[strcspn(entrada, "\n")] = '\0';
                excluirContato(entrada);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
