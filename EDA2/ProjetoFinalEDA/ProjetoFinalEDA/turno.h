#ifndef TURNO_H
#define TURNO_H

#include "personagem.h"

typedef struct NoFila {
    Personagem* personagem;
    struct NoFila* prox;
} NoFila;

void enfileirar(NoFila** fila, Personagem* p);
Personagem* desenfileirar(NoFila** fila);
int filaVazia(NoFila* fila);

#endif