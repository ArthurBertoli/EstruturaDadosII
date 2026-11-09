#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef struct Personagem {
    char nome[30];
    int hp;
    int ataque;
    int x, y;
    int equipe;
   
    struct Personagem* left;
    struct Personagem* right;
    int height; 
} Personagem;

Personagem* criarPersonagem(const char* nome, int hp, int ataque, int x, int y, int equipe);
void atacar(Personagem* atacante, Personagem* alvo);
void mover(Personagem* p, int dx, int dy);

Personagem* inserirPersonagemAVL(Personagem* no, Personagem* novoPersonagem);

Personagem* removerPersonagemAVL(Personagem* no, const char* nome);

void liberarArvoreAVL(Personagem* no);

Personagem* removerMortosAVL(Personagem* raiz);

int getAltura(Personagem* no);

int getBalanceamento(Personagem* no);

Personagem* rotacaoDireita(Personagem* y);
Personagem* rotacaoEsquerda(Personagem* x);

Personagem* encontrarAlvoProximoAVL(Personagem* atacante, Personagem* raizArvore);

void contarEquipesAVL(Personagem* no, int* herois, int* inimigos);

void atualizarMapaAVL(Personagem* no);

#endif