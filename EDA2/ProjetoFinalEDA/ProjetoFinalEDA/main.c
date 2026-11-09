#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include "personagem.h" 
#include "mapa.h" 
#include "turno.h" 

int checarFim(Personagem* raiz_avl) {
    int herois = 0, inimigos = 0;
    contarEquipesAVL(raiz_avl, &herois, &inimigos); 
    return (herois == 0 || inimigos == 0);
}

int main() {
    srand(time(NULL)); 

    Personagem* raiz_avl = NULL; 
    NoFila* fila = NULL; 

    inicializarMapa(); 

    Personagem* h1 = criarPersonagem("Heroi1", 10, 3, 0, 0, 0);
    Personagem* h2 = criarPersonagem("Heroi2", 10, 2, 0, 1, 0);
    Personagem* i1 = criarPersonagem("Inimigo1", 8, 2, 4, 4, 1);
    Personagem* i2 = criarPersonagem("Inimigo2", 9, 3, 4, 3, 1);

    raiz_avl = inserirPersonagemAVL(raiz_avl, h1);
    raiz_avl = inserirPersonagemAVL(raiz_avl, h2);
    raiz_avl = inserirPersonagemAVL(raiz_avl, i1);
    raiz_avl = inserirPersonagemAVL(raiz_avl, i2);

    enfileirar(&fila, h1);
    enfileirar(&fila, h2);
    enfileirar(&fila, i1);
    enfileirar(&fila, i2);

    int turno_num = 1; 
    while (!checarFim(raiz_avl)) { 
        printf("\n--- TURNO %d ---\n", turno_num++);
        atualizarMapa(raiz_avl); 
        exibirMapa(); 
        Personagem* atual = desenfileirar(&fila); 
        if (atual->hp > 0) {
            printf("\nTurno de %s (HP: %d - Pos: (%d,%d)): ", atual->nome, atual->hp, atual->x, atual->y);
            Personagem* alvo = encontrarAlvoProximoAVL(atual, raiz_avl); 
            if (alvo != NULL) {
                atacar(atual, alvo); 
            } else {
                int dx = (rand() % 3) - 1; 
                int dy = (rand() % 3) - 1; 

                int nova_x = atual->x + dx;
                int nova_y = atual->y + dy;

                if (nova_x >= 0 && nova_x < TAM && nova_y >= 0 && nova_y < TAM) {
                    mover(atual, dx, dy); 
                    printf("%s moveu para (%d, %d).\n", atual->nome, atual->x, atual->y);
                } else {
                    printf("%s nao pode se mover para fora do mapa.\n", atual->nome);
                }
            }
        } else {
            printf("%s foi removido da fila (ja estava morto).\n", atual->nome);
        }
        raiz_avl = removerMortosAVL(raiz_avl); 
        if (atual->hp > 0) {
            enfileirar(&fila, atual); 
        } else {
        }
    }
    printf("\nFim de jogo!\n");
    int herois_restantes = 0, inimigos_restantes = 0;
    contarEquipesAVL(raiz_avl, &herois_restantes, &inimigos_restantes);
    if(herois_restantes > 0) {
        printf("Vitoria dos Herois!\n");
    } else if (inimigos_restantes > 0) {
        printf("Vitoria dos Inimigos!\n");
    } else {
        printf("Empate (todos foram eliminados).\n");
    }
    liberarArvoreAVL(raiz_avl);

    return 0; 
}