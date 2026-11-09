#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char nome[50];
    char telefone[20];
    int dn_dia, dn_mes, dn_ano;
    char cidade[30];
    char cep[12];
    char email[50];
} Contato;

// Função para comparação ignorando maiúsculas/minúsculas
int comparar(const void *a, const void *b) {
    return strcasecmp(((Contato *)a)->nome, ((Contato *)b)->nome);
}

// Carrega todos os contatos do arquivo
int carregarContatos(const char *arquivo, Contato contatos[], int *qtd) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return 0;

    *qtd = 0;
    while (fread(&contatos[*qtd], sizeof(Contato), 1, f) == 1) {
        (*qtd)++;
    }
    fclose(f);
    return 1;
}

// Salva todos os contatos no arquivo
void salvarContatos(const char *arquivo, Contato contatos[], int qtd) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    fwrite(contatos, sizeof(Contato), qtd, f);
    fclose(f);
}

// Buscar por nome (retorna índice ou -1)
int buscarContato(Contato contatos[], int qtd, const char *nome) {
    for (int i = 0; i < qtd; i++) {
        if (strcasecmp(contatos[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void imprimirContato(Contato *c) {
    printf("\nNome: %s\nTelefone: %s\nData Nasc: %02d/%02d/%04d\nCidade: %s\nCEP: %s\nEmail: %s\n",
        c->nome, c->telefone, c->dn_dia, c->dn_mes, c->dn_ano, c->cidade, c->cep, c->email);
}

void incluirContato(const char *arquivo) {
    Contato contatos[MAX];
    int qtd;

    carregarContatos(arquivo, contatos, &qtd);

    Contato novo;
    printf("Nome: "); fgets(novo.nome, 50, stdin); strtok(novo.nome, "\n");
    printf("Telefone: "); fgets(novo.telefone, 20, stdin); strtok(novo.telefone, "\n");
    printf("Data Nasc (dd mm aaaa): "); scanf("%d %d %d", &novo.dn_dia, &novo.dn_mes, &novo.dn_ano); getchar();
    printf("Cidade: "); fgets(novo.cidade, 30, stdin); strtok(novo.cidade, "\n");
    printf("CEP: "); fgets(novo.cep, 12, stdin); strtok(novo.cep, "\n");
    printf("Email: "); fgets(novo.email, 50, stdin); strtok(novo.email, "\n");

    contatos[qtd++] = novo;

    qsort(contatos, qtd, sizeof(Contato), comparar);
    salvarContatos(arquivo, contatos, qtd);
    printf("Contato adicionado e arquivo reordenado.\n");
}

void excluirContato(const char *arquivo) {
    Contato contatos[MAX];
    int qtd;

    carregarContatos(arquivo, contatos, &qtd);

    char nome[50];
    printf("Nome a excluir: ");
    fgets(nome, 50, stdin); strtok(nome, "\n");

    int i = buscarContato(contatos, qtd, nome);
    if (i == -1) {
        printf("Contato não encontrado.\n");
        return;
    }

    for (; i < qtd - 1; i++) {
        contatos[i] = contatos[i + 1];
    }
    qtd--;

    salvarContatos(arquivo, contatos, qtd);
    printf("Contato removido com sucesso.\n");
}

void buscar(const char *arquivo) {
    Contato contatos[MAX];
    int qtd;
    carregarContatos(arquivo, contatos, &qtd);

    char nome[50];
    printf("Nome a buscar: ");
    fgets(nome, 50, stdin); strtok(nome, "\n");

    int i = buscarContato(contatos, qtd, nome);
    if (i != -1) {
        imprimirContato(&contatos[i]);
    } else {
        printf("Contato não encontrado.\n");
    }
}

int main() {
    const char *arquivo = "agenda_ordenada.dat";
    int opcao;

    do {
        printf("\n1 - Incluir\n2 - Buscar\n3 - Excluir\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao); getchar();

        switch (opcao) {
            case 1: incluirContato(arquivo); break;
            case 2: buscar(arquivo); break;
            case 3: excluirContato(arquivo); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida\n");
        }
    } while (opcao != 0);

    return 0;
}
