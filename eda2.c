#include <stdlib.h>
#include <stdio.h>

//fila -> fila de banco, ordem de chegada, entra primeiro sai primeiro, elemento adicionado vai para o final.
//FIFO -> first in first out
//head/tail, head = primeiro elemento, tail = elementos da fila
#define TAMFILA 10

int fila[TAMFILA] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int head = 0;
int tail = 0;

void lista_elementos(){
    printf("\nLista atual:");
    for(int i = 0; i < TAMFILA; i++){
        printf("-");
        printf("|%d|", fila[i]);
        printf("-");
    }
    printf("\nHead: %d\n", head);
    printf("Tail: %d\n", tail);
    printf("\n\n");
}

void enqueue(){
    int val;
    if(tail < TAMFILA){
        printf("\nInforme o valor: ");
        scanf("\n%d", &val);
        fila[tail] = val;
        tail = tail + 1;
        lista_elementos();
    }else{
        printf("\nA fila esta cheia..");
    }
}

void dequeue(){
    if(head < tail){
        fila[head] = 0;
        head = head + 1;
        lista_elementos();
    }else{
        pritnf("\nA fila esta vazia..");
    }
}

void clear(){
    for(int i = 0; i < TAMFILA; i++){
        fila[i] = 0;
    }
    head = 0;
    tail = 0;
}


int main(){

    int opcao = 0

    do{
        printf("\nSelecione a opção:");
        printf("\n1. Inserir");
        printf("\n2. Remover");
        printf("\n3. Limpar a fila");
        printf("\n4. Limpar");
        printf("\n-1 Sair");
        printf("\nOpção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
            enqueue();
            break;

            case 2:
            dequeue();
            break;

            case 3:
            clear();
            break;

            case 4:
            lista_elementos();

            case -1:
            break;

            default:
            printf("\nDigite um numero valido");
        }


    }while(opcao != -1);

    return 0;
}

//pilha
//FILO -> first in last out

#define TAMPILHA 10

int pilha[TAMPILHA] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
int topo = 0;

void push(){
    int val;
    printf("\nInforme o valor:" );
    scanf("%d", &val);
    if(topo < TAMPILHA){
        pilha[topo] = val;
        topo = topo + 1;
        listaPilha();
    }else{
        printf("\nPilha cheia...");
    }
}

void pop(){
    if(topo >= 0){
        pilha[topo - 1] = 0;
        topo = topo -1;
        listaPilha();
    }else{
        printf("\nPilha vazia...");
    }
}

void clear(){
    for(int i = 0; i < TAMPILHA; i++){
        pilha[i] = 0;
    }
    topo = 0;
}

void listaPilha(){
    printf("\nPilha atual: ");
    for(int i = 0; i< TAMPILHA; i++){
        printf("-");
        printf("|%d|", pilha[i]);
        printf("-");
    }
    printf("\nTopo: %d", topo);
    printf("\n\n");
}

//lista encadeada -> linked list
//ordenada, ponteiro, nós

struct st_no
{
    int valor;
    struct st_no *prox;
};

typedef struct st_no no;

int vazia(no *le){
    if(le->prox == NULL){
        return 1;
    }else{
        return 0;
    }
}

void inicia(no *le){
    le->prox = NULL;
}

void libera(no *le){
    if(!vazia(le)){
        no *proxNo, *atual;
        atual = le->prox;
        while (atual != NULL){
            proxNo = atual->prox;
            free(atual);
            atual = proxNo;
        }
    }
}

void exibe(no *le){
    if(vazia(le)){
        printf("\nA lista esta vazia...");
        return;
    }

    no *temp;
    temp = le->prox.

    while (temp != NULL){
        pritnf("%d", temp->valor);
        temp = temp->prox;
    }
    printf("\n\n");
}

void insereInicio(no *le){
    no *novo = (no*)malloc(sizeof(no));
    if(!novo){
        printf("\nMemória indisponível...");
        exit(1);
    }
    printf("\nInforme o valor: ");
    scanf("%d", &novo->valor);

    no *oldHead = le->prox;
    le->prox = novo;
    novo->prox = oldHead;
}

void insereFim(no *le){
    no *novo = (no*)malloc(sizeof(no));
    if(!novo){
        printf("\nMemória indisponível...");
        exit(1);
    }
    printf("\nInforme o valor: ");
    scanf("%d", &novo->valor);

    novo->prox = NULL;

    if(vazia(le)){
        le->prox = novo;
    }else{
        no *temp = le->prox;
        
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void opcao(no *le, int op){
    switch (op)
    {
    case 0:
        libera(le);
        break;
    case 1:
        exibe(le);
        break;
    case 2:
        insereInicio(le);
        break;
    case 3:
        insereFim(le);
        break;
    case 4:
        inicia(le);
        break
    default:
        printf("\nNúmero inválido...");
        break;
    }
}

int menu(){
    int opt;
    printf("\nEscolha:");
    printf("\n0. libera");
    printf("\n1. exibe");
    printf("\n2. insere inicio");
    printf("\n3. insere fim");
    printf("\n4. zerar");

    return opt;
}

int main(){
    no *le = (no*)malloc(sizeof(no));

    if(!le){
        printf("Sem memoria");
        exit(1);
    }
    inica(le);
    int opt;

    do{
        opt = menu();
        opcao(le, opt);
    }while(opt);
    free(le);
    return 0;
}

//exercicio pilha implementada em uma lista encadeada
//Exercício 1, usei de base o que estava no texto:
typedef struct celula {
    char conteudo;
    struct celula *prox;
} celula;

celula *topo = NULL;

void empilha (char conteudo) {
    celula *nova;
    nova = malloc (sizeof (celula));
    if(nova == NULL){
        printf("\nErro ao alocar memória...");
    }
    nova->conteudo = conteudo;
    nova->prox = topo;
    topo = nova;
}

char desempilha (void) {
    celula *p;
    p = topo;
    char x = p->x;
    topo = topo->prox;
    free (p);
    return x;
}

int pilhavazia (void) {
    return topo == NULL;
}

//Remodelagem da função bemFormada:
int bemFormada (char s[]){
    for (int i = 0; s[i] != '\0'; ++i) {
        char c;
        switch (s[i]) {
        case ')':
            if (pilhavazia()) return 0;
            c = desempilha();
            if (c != '(') return 0;
            break;
        case ']':
            if (pilhavazia()) return 0;
            c = desempilha();
            if (c != '[') return 0;
            break;
        default: 
            empilha (s[i]);
        }
    }
    return pilhavazia();
}

//Remodelagem da função infixaParaPosfixa:
char *infixaParaPosfixa (char *inf) {
    int n = strlen (inf);
    char *posf;
    posf = malloc ((n+1) * sizeof (char));

    int j = 0;
    for (int i = 0; inf[i] != '\0'; ++i) {
        switch (inf[i]) {
            char x;
            case '(':
                empilha (inf[i]);
                break;
            case ')':
                x = desempilha ();
                while (x != '(') {
                    posf[j++] = x;
                x = desempilha ();
                }
                break;
            case '+':
            case '-':
                x = desempilha ();
                while (x != '(') {
                    posf[j++] = x;
                x = desempilha ();
                }
                empilha (x);
                empilha (inf[i])
                break;
            case '*':
            case '/':
                if(topo != NULL && (topo->conteudo == '*' || topo->conteudo == '/')){
                    x = desempilha ();
                    posf[j++] = x;
                }
                empilha (inf[i]);
                break;
            default:
            posf[j++] = inf[i];
            }
    }
    while (topo != NULL){
        posf[j++] = desempilha();
    }
    posf[j] = '\0';
    return posf;
}

//exercicio fila de prioridades
struct cel{
    struct cel *ant;
    struct cel *prox;
    int dado;
    int prioridade;
};
typedef struct cel celula;

celula* criar(int dado, int prioridade){
    celula* nova = (celula*)malloc(sizeof(celula));
    
    nova->dado = dado;
    nova->prioridade = prioridade;
    nova->ant = NULL;
    nova->prox = NULL;
    
    return nova;
}

void inserir(celula** head, int dado, int prioridade){
    
    celula* nova = criar(dado, prioridade);
    
    if(*head == NULL){
        *head = nova;
    } else {
        celula* atual = *head;
        celula* anterior = NULL;
        
        
        while (atual != NULL && atual->prioridade <= prioridade) {
            anterior = atual;
            atual = atual->prox;
        }
        
        
        if( anterior == NULL) {
            nova->prox = *head;
            (*head)->ant = nova;
            *head = nova;
        } else {
            nova->prox = anterior->prox;
            nova->ant = anterior;
            
            if (anterior->prox != NULL){
                anterior->prox->ant = nova;
            }
            
            anterior->prox = nova;
        }
    }
}

void remover(celula** head){
    if (*head == NULL){
        printf("\n Fila vazia");
        return;
    }
    
    celula* removida = *head;
    *head = (*head)->prox;
    
    if(*head != NULL){
        (*head)->ant = NULL;
    }
    
    free(removida);
}

void imprimir(celula* head){
    celula* atual = head;
    while(atual != NULL){
        printf("Dado: %d, Prioridade: %d\n", atual->dado, atual->prioridade);
        atual = atual->prox;
    }
}

int main()
{
    celula* fila = NULL;
    
    inserir(&fila, 5, 2);
    inserir(&fila, 3, 1);
    inserir(&fila, 7, 3);
    inserir(&fila, 1, 0);
    
    printf("Fila de prioridade:\n");
    imprimir(fila);
    
    printf("\nRemovendo elemento de maior prioridade:\n");
    remover(&fila);
    imprimir(fila);

    return 0;
}