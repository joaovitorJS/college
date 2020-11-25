#ifndef ALLOCLINKED_H
#define ALLOCLINKED_H

#include <stdio.h>
#include <stdlib.h>
#include "gfx/gfx.h"

#define INITIAL_NO_X 30
#define INITIAL_NO_Y 40

/*
    Autor: João Vitor de Oliveira

    Biblioteca que implementa as operações para manipular estruturas de dados:
        - Busca, inserção e remoção em lista simplesmente encadeada sem nó cabeça ordenada;
        - Busca, inserção e remoção em lista circular simplesmente encadeada sem nó cabeça ordenada;
        - Busca, inserção e remoção em lista duplamente encadeada com nó cabeça (sem ordenação);
        - Inserção e remoção em fila (FIFO);
        - Inserção e remoção em pilha (LIFO).
*/

/*Estrutura para usar na lista simplesmente encadeada, lista circular, fila, pilha*/
typedef struct no {
    int key;
    struct no *prox;
} NO;

/*Estrutura para usar na lista duplamente encadeada*/
typedef struct ldeno {
    int key;
    struct ldeno *prev; //ponteiro para o anterior
    struct ldeno *next; //ponteiro para o próximo
} LDENO;

/*Operações com a lista simplesmente encadeada*/
void searchNoLse(NO *, int);
void addNoLse(NO **, int);
void removeNoLse(NO **, int);
void printLse(NO *);
void freeLse(NO **);

/*Operações com a lista circular simplesmente encadeada*/
void searchNoLcse(NO *, int);
void addNoLcse(NO **, int);
void removeNoLcse(NO **, int);
void printLcse(NO *);
void freeLcse(NO **);

/*Operações com a lista duplamente encadeada com nó cabeça*/
void initLde(LDENO **);
void searchNoLde(LDENO *, int);
void addNoLde(LDENO **, int);
void removeNoLde(LDENO **, int);
void printLde(LDENO *);
void freeLde(LDENO **);

/*Operações com fila (FIFO)*/
void addNoQueue(NO **, NO **, int);
void removeNoQueue(NO **, NO **);
void printQueue(NO *);
void freeQueue(NO **, NO **);

/*Operações com pilha (LIFO)*/
void addNoStack(NO **, int);
void removeNoStack(NO **);
void printStack(NO *);
void freeStack(NO **);

/*Parte Gráfica*/
void gfxNoSimple(int, int);
void gfxArrowLeftToRight(int);
void gfxLambda(int);
void gfxArrowLeftToStart(int);
void gfxNoDuo(int, int);
void gfxNoHead(int);
void gfxArrowRightToEnd(int);
void gfxArrowDuo(int);
void gfxNoStack(int, int);
void gfxArrowBottonToTop(int);
void gfxLambdaStack(int);

#endif //ALLOCLINKED