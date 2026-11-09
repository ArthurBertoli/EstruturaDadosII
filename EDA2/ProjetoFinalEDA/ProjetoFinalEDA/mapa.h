#ifndef MAPA_H
#define MAPA_H

#include "personagem.h"

#define TAM 5

extern char mapa[TAM][TAM]; 

void inicializarMapa();
void atualizarMapa(Personagem* raiz_avl);
void exibirMapa();

#endif 