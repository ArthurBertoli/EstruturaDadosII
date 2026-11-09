#include <stdio.h>
#include "mapa.h"
#include "personagem.h"

char mapa[TAM][TAM];

void inicializarMapa() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            mapa[i][j] = '.';
}


void atualizarMapa(Personagem* raiz_avl) {
    inicializarMapa(); 
    atualizarMapaAVL(raiz_avl); 
}

void exibirMapa() {
    printf("\nMapa:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}