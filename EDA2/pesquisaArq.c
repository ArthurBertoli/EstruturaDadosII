#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define FILE_SIZE 100000 // numereo de registros no arquivo

unsigned int id_min_value, id_max_value; // valor do primeiro e último id criado

typedef struct t_register { // registro grande para fazer o arquivo ficar grande
	unsigned int id_person;
	char name[80];
	char phone_number[30];
	struct s_address {
		int type; // rua, avenida,...
		unsigned int number;
		char street[80];
		char zip_code[10];
		char state_province[50];
		int city[40];
	} address;
} Register;

int generateFile();
int linearSearch(unsigned int key);
int sentinelLinearSearch(unsigned int key);
int binarySearch(unsigned int key);
int interpolationSearch(unsigned int key);

int main() {
    int i;
    
    printf("Criando arquivo...");
    if(generateFile())
		return 1; // saida com erro ao tentar criar o arquivo

	for(i=0; i<20; i++) {
		unsigned int key = rand() % id_max_value;
		printf("\nProcurando chave %u :\n", key);
		printf("Pesquisa Sequencial: ");
		linearSearch(key);
		printf("Pesquisa Sequencial com Sentinela: ");
		sentinelLinearSearch(key);
		printf("Pesquisa Binária: ");
		binarySearch(key);
        printf("Pesquisa por Interpolação: ");
        interpolationSearch(key);
	}
}

int generateFile() {
	FILE *fileOut;
	Register r;
	int i;

	if (access("arquivo.bin", F_OK) == 0) {
		printf("\rArquivo já criado anteriormente!\n");
        
        // armazena primeiro e último id para pesquisa por interpolação
        FILE *fileIn = fopen("arquivo.bin", "rb");
        fread(&r, sizeof(Register), 1, fileIn);
        id_min_value = r.id_person;
        fseek(fileIn, -sizeof(Register), SEEK_END);
        fread(&r, sizeof(Register), 1, fileIn);
        id_max_value = r.id_person;
        fclose(fileIn);
    } else {
        // cria arquivo ordenado para pesquisas
        if((fileOut = fopen("arquivo.bin", "wb")) == NULL) {
            printf("Erro na abertura do arquivo de saída!");
            return 1; // saída com erro
        }
        id_max_value = 0;
        for(i=0; i<FILE_SIZE; i++) {
            id_max_value = r.id_person = id_max_value + 1 + (rand() % 5); // próximo id aleatório em sequencia
            if(i==0) id_min_value = r.id_person; // guarda primeiro id para pesquisa por interpolação
            fwrite(&r, sizeof(Register), 1, fileOut); // TODO: testar se conseguiu gravar (disco cheio, por exemplo)
        }
        fwrite(&r, sizeof(Register), 1, fileOut); // registro extra para sentinela
        fclose(fileOut);
        printf("Arquivo criado com sucesso.\n");
    }
	return 0; // saida sem erro
}

int linearSearch(unsigned int key) {
	FILE *fileIn;
	Register r;
	int count=0;

	if((fileIn = fopen("arquivo.bin", "rb")) == NULL) {
		printf("Erro na abertura do arquivo de entrada!");
		return 2;
	}
	while( !feof(fileIn) ) {
		fread(&r, sizeof(Register), 1, fileIn); // TODO: testar se conseguiu ler (arquivo manipulado/removido durante leitura)
		if(r.id_person == key) {
			printf("registro %u localizado na posição %d do arquivo!\n", key, count);
			return 0; // saída sem erro - registro localizado
		}
        count++;
	}
	fclose(fileIn);
	printf("registro %u NÃO localizado!\n", key);
	return 1; // saida com erro
}

int sentinelLinearSearch(unsigned int key) {
	FILE *fileIn;
	Register r;
	int count=0;
	long file_position;

	if((fileIn = fopen("arquivo.bin", "r+b")) == NULL) {
		printf("Erro na abertura do arquivo de entrada!");
		return 1;
	}

	// marca sentinela (chave de busca) no final do arquivo
	fseek(fileIn, -sizeof(Register), SEEK_END);
	r.id_person = key;
	fwrite(&r, sizeof(Register), 1, fileIn); // TODO: testar se conseguiu gravar
	fseek(fileIn, 0L, SEEK_SET);

	// pesquisa até encontrar registro
	fread(&r, sizeof(Register), 1, fileIn); // TODO: testar se conseguiu ler (arquivo manipulado/removido durante leitura)
	while( r.id_person != key ) {
		fread(&r, sizeof(Register), 1, fileIn); // TODO: testar se conseguiu ler (arquivo manipulado/removido durante leitura)
		count++;
	}
	if(count < FILE_SIZE) {
		printf("registro %u localizado na posição %d do arquivo!\n", key, count);
	} else {
		printf("registro %u NÃO localizado!\n", key);
	}
	fclose(fileIn);
	return 1; // saida com erro
}

int binarySearch(unsigned int key) {
    unsigned int low = 0, high = FILE_SIZE;
    FILE *fileIn;
    Register r;
    int count=0;

    if((fileIn = fopen("arquivo.bin", "rb")) == NULL) {
        printf("Erro na abertura do arquivo de entrada!");
        return 2;
    }
    while(low <= high) {
        unsigned int middle = (low + high) / 2;
        count++;
        fseek(fileIn, middle*sizeof(Register), SEEK_SET);
        fread(&r, sizeof(Register), 1, fileIn); // TODO: testar se conseguiu ler (arquivo manipulado/removido durante leitura)
        if(r.id_person == key) {
            printf("registro %u localizado na posição %d do arquivo em %d passos!\n", key, middle, count);
            return 0; // saída sem erro - registro localizado
        } else if (key < r.id_person) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    fclose(fileIn);
    printf("registro %u NÃO localizado - %d passos!\n", key, count);
    return 1; // saida com erro
}

int interpolationSearch(unsigned int key) {
    unsigned int low = 0, high = FILE_SIZE, min = id_min_value, max = id_max_value;
    FILE *fileIn;
    Register r;
    int count=0;

    if((fileIn = fopen("arquivo.bin", "rb")) == NULL) {
        printf("Erro na abertura do arquivo de entrada!");
        return 2;
    }
    while(low <= high) {
        unsigned int middle = low + (((double) (high - low) / (max - min)) * (key - min));
        count++;
        fseek(fileIn, middle*sizeof(Register), SEEK_SET);
        fread(&r, sizeof(Register), 1, fileIn); // deveria testar se conseguiu ler (arquivo manipulado/removido durante leitura)
        if(r.id_person == key) {
            printf("registro %u localizado na posição %d do arquivo em %d passos!\n", key, middle, count);
            return 0; // saída sem erro - registro localizado
        } else if (key < r.id_person) {
            high = middle - 1;
            max = r.id_person;
        } else {
            low = middle + 1;
            min = r.id_person;
        }
    }
    fclose(fileIn);
    printf("registro %u NÃO localizado - %d passos!\n", key, count);
    return 1; // saida com erro
}
