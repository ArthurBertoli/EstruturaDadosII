#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char telefone[20];
    int dn_dia, dn_mes, dn_ano;
    char cidade[30];
    char cep[12];
    char email[50];
} Contato;

void adicionarContato(const char* nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "ab");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Contato c;
    printf("Nome: ");
    fgets(c.nome, 50, stdin); strtok(c.nome, "\n");

    printf("Telefone: ");
    fgets(c.telefone, 20, stdin); strtok(c.telefone, "\n");

    printf("Data de nascimento (dia mes ano): ");
    scanf("%d %d %d", &c.dn_dia, &c.dn_mes, &c.dn_ano);
    getchar(); // Consumir \n do scanf

    printf("Cidade: ");
    fgets(c.cidade, 30, stdin); strtok(c.cidade, "\n");

    printf("CEP: ");
    fgets(c.cep, 12, stdin); strtok(c.cep, "\n");

    printf("Email: ");
    fgets(c.email, 50, stdin); strtok(c.email, "\n");

    fwrite(&c, sizeof(Contato), 1, file);
    fclose(file);
    printf("Contato salvo com sucesso.\n");
}

void buscarContato(const char* nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char nome_busca[50];
    printf("Digite o nome a buscar: ");
    fgets(nome_busca, 50, stdin); strtok(nome_busca, "\n");

    Contato c;
    int encontrado = 0;
    while (fread(&c, sizeof(Contato), 1, file)) {
        if (strcmp(c.nome, nome_busca) == 0) {
            printf("\nContato encontrado:\n");
            printf("Nome: %s\nTelefone: %s\nData de nascimento: %02d/%02d/%04d\nCidade: %s\nCEP: %s\nEmail: %s\n",
                c.nome, c.telefone, c.dn_dia, c.dn_mes, c.dn_ano, c.cidade, c.cep, c.email);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }

    fclose(file);
}

int main() {
    const char* nome_arquivo = "agenda.dat";
    int opcao;

    do {
        printf("\n1 - Adicionar contato\n2 - Buscar contato\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // Consumir \n do scanf

        switch(opcao) {
            case 1:
                adicionarContato(nome_arquivo);
                break;
            case 2:
                buscarContato(nome_arquivo);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao != 0);

    return 0;
}

//gcc -o agenda programa.c
//./agenda

