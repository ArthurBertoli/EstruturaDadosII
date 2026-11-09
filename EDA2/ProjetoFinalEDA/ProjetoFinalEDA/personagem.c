#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#include "personagem.h"
#include "mapa.h" 

Personagem* criarPersonagem(const char* nome, int hp, int ataque, int x, int y, int equipe) {
    Personagem* p = (Personagem*) malloc(sizeof(Personagem));
    if (p == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para Personagem '%s'.\n", nome);
        exit(EXIT_FAILURE);
    }
    strcpy(p->nome, nome);
    p->hp = hp;
    p->ataque = ataque;
    p->x = x;
    p->y = y;
    p->equipe = equipe;
    p->left = NULL;
    p->right = NULL;
    p->height = 1; 
    return p;
}

void atacar(Personagem* atacante, Personagem* alvo) {
    printf("%s ataca %s causando %d de dano!\n", atacante->nome, alvo->nome, atacante->ataque);
    alvo->hp -= atacante->ataque;
}

void mover(Personagem* p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int getAltura(Personagem* no) {
    if (no == NULL)
        return 0;
    return no->height;
}

void atualizarAltura(Personagem* no) {
    if (no != NULL) {
        int leftHeight = getAltura(no->left);
        int rightHeight = getAltura(no->right);
        no->height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    }
}

int getBalanceamento(Personagem* no) {
    if (no == NULL)
        return 0;
    return getAltura(no->left) - getAltura(no->right);
}

Personagem* rotacaoDireita(Personagem* y) {
    Personagem* x = y->left;
    Personagem* T2 = x->right;

    x->right = y;
    y->left = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

Personagem* rotacaoEsquerda(Personagem* x) {
    Personagem* y = x->right;
    Personagem* T2 = y->left;

    y->left = x;
    x->right = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

Personagem* encontrarMinimoAVL(Personagem* no) {
    Personagem* atual = no;
    while (atual->left != NULL)
        atual = atual->left;
    return atual;
}


Personagem* inserirPersonagemAVL(Personagem* no, Personagem* novoPersonagem) {
    if (no == NULL)
        return novoPersonagem;

    int cmp = strcmp(novoPersonagem->nome, no->nome);

    if (cmp < 0)
        no->left = inserirPersonagemAVL(no->left, novoPersonagem);
    else if (cmp > 0)
        no->right = inserirPersonagemAVL(no->right, novoPersonagem);
    else 
        return no; 
    atualizarAltura(no);

    int balanceamento = getBalanceamento(no);

    if (balanceamento > 1 && strcmp(novoPersonagem->nome, no->left->nome) < 0)
        return rotacaoDireita(no);

    if (balanceamento < -1 && strcmp(novoPersonagem->nome, no->right->nome) > 0)
        return rotacaoEsquerda(no);

    if (balanceamento > 1 && strcmp(novoPersonagem->nome, no->left->nome) > 0) {
        no->left = rotacaoEsquerda(no->left);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && strcmp(novoPersonagem->nome, no->right->nome) < 0) {
        no->right = rotacaoDireita(no->right);
        return rotacaoEsquerda(no);
    }

    return no;
}

Personagem* removerPersonagemAVL(Personagem* no, const char* nome) {
    if (no == NULL)
        return no;

    int cmp = strcmp(nome, no->nome);

    if (cmp < 0)
        no->left = removerPersonagemAVL(no->left, nome);
    else if (cmp > 0)
        no->right = removerPersonagemAVL(no->right, nome);
    else {
        if ((no->left == NULL) || (no->right == NULL)) {
            Personagem* temp = no->left ? no->left : no->right;

            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else 
                *no = *temp;
            free(temp);
        } else {
            Personagem* temp = encontrarMinimoAVL(no->right);
            strcpy(no->nome, temp->nome);
            no->hp = temp->hp;
            no->ataque = temp->ataque;
            no->x = temp->x;
            no->y = temp->y;
            no->equipe = temp->equipe;
            no->right = removerPersonagemAVL(no->right, temp->nome);
        }
    }

    if (no == NULL)
        return no;
    atualizarAltura(no);

    int balanceamento = getBalanceamento(no);

    if (balanceamento > 1 && getBalanceamento(no->left) >= 0)
        return rotacaoDireita(no);

    if (balanceamento > 1 && getBalanceamento(no->left) < 0) {
        no->left = rotacaoEsquerda(no->left);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && getBalanceamento(no->right) <= 0)
        return rotacaoEsquerda(no);

    if (balanceamento < -1 && getBalanceamento(no->right) > 0) {
        no->right = rotacaoDireita(no->right);
        return rotacaoEsquerda(no);
    }

    return no;
}
void liberarArvoreAVL(Personagem* no) {
    if (no != NULL) {
        liberarArvoreAVL(no->left);
        liberarArvoreAVL(no->right);
        free(no);
    }
}

Personagem* removerMortosAVL(Personagem* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    raiz->left = removerMortosAVL(raiz->left);

    raiz->right = removerMortosAVL(raiz->right);

    if (raiz->hp <= 0) {
        printf("%s foi eliminado!\n", raiz->nome);
        return removerPersonagemAVL(raiz, raiz->nome);
    }
    return raiz;
}

double calcularDistancia(Personagem* p1, Personagem* p2) {
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

Personagem* encontrarAlvoProximoAVL(Personagem* atacante, Personagem* raizArvore) {
    Personagem* alvoMaisProximo = NULL;
    double menorDistancia = -1.0;

    void _encontrarAlvoProximoRecursivo(Personagem* no) {
        if (no == NULL) {
            return;
        }

        if (no->equipe != atacante->equipe && no->hp > 0) {
            double distancia = calcularDistancia(atacante, no);

            if (distancia <= 1.5) {
                if (alvoMaisProximo == NULL || distancia < menorDistancia) {
                    menorDistancia = distancia;
                    alvoMaisProximo = no;
                }
            }
        }
        
        _encontrarAlvoProximoRecursivo(no->left);
        
        _encontrarAlvoProximoRecursivo(no->right);
    }

    _encontrarAlvoProximoRecursivo(raizArvore);
    return alvoMaisProximo;
}

void contarEquipesAVL(Personagem* no, int* herois, int* inimigos) {
    if (no == NULL) {
        return;
    }
    contarEquipesAVL(no->left, herois, inimigos);
    if (no->hp > 0) {
        if (no->equipe == 0) {
            (*herois)++;
        } else {
            (*inimigos)++;
        }
    }
    contarEquipesAVL(no->right, herois, inimigos);
}

void atualizarMapaAVL(Personagem* no) {
    if (no == NULL) {
        return;
    }
    atualizarMapaAVL(no->left);
    if (no->hp > 0) { 
        char c = (no->equipe == 0) ? 'H' : 'I';
        if (no->x >= 0 && no->x < TAM && no->y >= 0 && no->y < TAM) {
            mapa[no->x][no->y] = c;
        }
    }
    atualizarMapaAVL(no->right);
}