#include <stdlib.h>
#include "turno.h"

void enfileirar(NoFila** fila, Personagem* p) {
    NoFila* novo = malloc(sizeof(NoFila));
    novo->personagem = p;
    novo->prox = NULL;

    if (*fila == NULL) {
        *fila = novo;
    } else {
        NoFila* temp = *fila;
        while (temp->prox)
            temp = temp->prox;
        temp->prox = novo;
    }
}

Personagem* desenfileirar(NoFila** fila) {
    if (*fila == NULL) return NULL;
    NoFila* temp = *fila;
    Personagem* p = temp->personagem;
    *fila = temp->prox;
    free(temp);
    return p;
}

int filaVazia(NoFila* fila) {
    return fila == NULL;
}