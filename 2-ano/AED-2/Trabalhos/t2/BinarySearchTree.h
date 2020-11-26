#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "gfx/gfx.h"

#define TRUE 1
#define FALSE 0

/*
    Autor: João Vitor de Oliveira

    Biblioteca que implementa as operações para manipular árvores binárias de busca:
        - Busca, inserção e remoção de chaves inteiras;
        - Visualização da árvore em modo gráfico usando a biblioteca gfx;
        - Leitura e gravação da árvore em arquivo formato binário usando percurso em pré-ordem. A árvore não deve ser reconstruída através de operações de inserção;
        - Desalocação da árvore completa.  
*/

/*estrutura de dados utilizada para representar na memória cada nó da árvore*/
typedef struct s_no {
    
    int32_t key:30;
    int32_t reserved:2; /* sem uso, mas deve ter sempre o valor 0 (zero) */
    struct s_no* ptLeft;
    struct s_no* ptRight;

} S_NO;

/*estrutura de dados utilizada para representar no arquivo cada nó da árvore*/
typedef struct s_arq_no {

    int32_t key:30;
    uint32_t left:1;
    uint32_t right:1;

} S_ARQ_NO;

/*Operações com a árvore binária de busca*/
void addNoBinaryTree(S_NO **, int32_t); /*Parâmetros: (ponteiro-raiz:referência, chave)*/
void searchBinaryTreeMsg(S_NO *, int32_t); /*Parâmetros: (ponteiro-raiz, chave)*/
void removeNoBinaryTree(S_NO**, int32_t); /*Parâmetros: (ponteiro-raiz:referência, chave)*/
void printBinaryTreeGfx(S_NO*, unsigned, unsigned, unsigned); /*Parâmetros: (ponteiro-raiz, x-inicial, x-final, y-inicial)*/ 
void freeBinaryTree(S_NO **, S_NO *); /*Parâmetros: (ponteiro-raiz:referência, ponteiro-raiz)*/

void writeBST(S_NO *, FILE *); /*Parâmetros: (ponteiro-raiz, arquivo)*/
void readBST(S_NO **, S_NO **,FILE *); /*Parâmetros: (ponteiro-raiz: referência, ponteiro-raiz:referencia,arquivo)*/

#endif // BINARYSEARCHTREE_H