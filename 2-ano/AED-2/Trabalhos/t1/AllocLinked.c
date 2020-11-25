#include "AllocLinked.h"


//***************************************************************************//
/*Lista Simplesmente Encadeada ordenada sem nó cabeça*/
//***************************************************************************//

//========================================================================//
// Objetivo: buscar um nó na lse (lista simplesmente encadeada), 
// conforme seu campo chave 
//========================================================================//
void searchNoLse(NO *ptr, int x) {

    if (ptr != NULL) {
        
        while (ptr != NULL) {
            if (ptr->key == x) {
                /*Elemento Encontrado*/   
                printf("\nElemento %d esta na lista!\n", x);
                return; 
            }
            ptr = ptr->prox;
        }
        printf("\nElemento %d nao esta na lista!\n", x);
    } else {
        printf("\nLista Vazia!\n");
    }
}

//========================================================================//
// Objetivo: inserir um novo nó na lse, de forma ordenada, conforme o valor
// do campo chave
//========================================================================//
void addNoLse(NO **ptList, int x) {
    NO *pt, *ptCurrent, *ptPre, *ptAux = NULL;
    // int flag; 

    /*Alocação de um novo nó*/
    if ( (pt = (NO *)malloc(sizeof(NO))) == NULL ) {
        return;
    } 
    pt->key = x;
    
    /*"Encaixar" o nó alocado na lista de forma ordenada*/
    ptCurrent = (*ptList);
    if (ptCurrent == NULL) {
        /*Caso em que é o primeiro nó da lista*/
        (*ptList) = pt;
        pt->prox = NULL;
    
    } else {
        ptPre = (*ptList);
        ptAux = (*ptList);
        /*Busca a posição que o nó será inserido na lista*/
        while (ptCurrent != NULL) {
            if (x < ptCurrent->key) {
                ptAux = ptCurrent;
                ptCurrent = NULL;
            } else {
                ptPre = ptCurrent;
                ptCurrent = ptCurrent->prox;
            }
        }

        if ( ptAux != ptPre || x > ptAux->key) {
            /*Caso em que o nó será inserido no meio/final da lista*/
            pt->prox = ptPre->prox;
            ptPre->prox = pt;
        } else {
            /*Caso em que o nó será inserido na primeira posição da lista*/ 
            pt->prox = ptPre;
            (*ptList) = pt;
        }
    }
}

//========================================================================//
// Objetivo: remover um nó na lse, mantendo a lista ordenada, conforme o valor
// do campo chave
//========================================================================//
void removeNoLse(NO **ptList, int x) {
    NO *ptPre, *ptCur, *ptAux;

    if ( (*ptList) != NULL) {
        ptPre = (*ptList);
        ptCur = NULL;

        /*Buscar o nó a ser removido*/
        ptAux = (*ptList);
        while (ptAux != NULL) {
            if (ptAux->key == x) {
                ptCur = ptAux;
                ptAux = NULL;
            } else {
                ptPre = ptAux;
                ptAux = ptAux->prox;  
            }
        }
        
        /*Remover o nó*/
        if (ptCur != NULL) {

            if (ptCur == ptPre) {
                /*Caso o elemento esteja no primeiro nó da lista*/
                (*ptList) = ptCur->prox;
            } else {
                /*Caso o elemento esteja no meio/final da lista*/
                ptPre->prox = ptCur->prox;
            }
            /*Liberar*/
            free(ptCur);
        } else {
           printf("\nElemento %d nao esta na lista!\n", x); 
        }
    } else {
        printf("\nLista Vazia!\n");
    }
}


//========================================================================//
// Objetivo: imprimir todos os elementos da lista
//========================================================================//
void printLse(NO *ptr) {
    int count = 0;

    gfx_clear();
    if (ptr != NULL) {
        printf("\nLista: ptLista->");
        while (ptr != NULL) {
            printf("[%d]->", ptr->key);
            gfxNoSimple(count, ptr->key);
            gfxArrowLeftToRight(count);
            ptr = ptr->prox;
            count++;
        }   
        printf(" NULL");
        gfxLambda(count-1);
    } else {
        printf("\nLista Vazia!\n");
    }
    gfx_paint();
}

//========================================================================//
// Objetivo: desalocar todos os nós da lista
//========================================================================//
void freeLse(NO **ptList) {
    NO *pt, *aux;

    pt = (*ptList);
    while (pt != NULL) {
        aux = pt;
        pt = pt->prox;
        free(aux);
    }

    (*ptList) = NULL;
}




//***************************************************************************//
/*Lista Circular Simplesmente Encadeada ordenada sem nó cabeça*/
//***************************************************************************//

//========================================================================//
// Objetivo: buscar um nó na lcse (lista circular simplesmente encadeada), 
// conforme seu campo chave 
//========================================================================//
void searchNoLcse(NO *ptList, int x) {
    NO *pt;
    
    if (ptList != NULL) {
        pt = ptList;
        
        if (pt->key == x) {
            printf("\nElemento %d esta na lista!\n", x);
            return;
        } else {
            pt = pt->prox;

            while (pt != ptList) {
                if (pt->key == x) {
                    printf("\nElemento %d esta na lista!\n", x);
                    return;
                }
                pt = pt->prox;
            }
        }

        printf("\nElemento %d nao esta na lista!\n", x);
    } else {
        printf("\nLista Vazia...\n");
    }
}

//========================================================================//
// Objetivo: buscar uma posição da lista para inserir um novo nó
//========================================================================//
void searchAuxLcse(NO *ptList, int x, NO **ptPre, NO **ptSuc) {
    NO *ptAux;
    
    (*ptPre) = ptList;
    (*ptSuc) = ptList;

    if (ptList->key <= x) {
        ptAux = ptList->prox;

        while (ptAux != ptList) {
            if (x < ptAux->key) {
                (*ptSuc) = ptAux;
                ptAux = ptList;
            } else {
                (*ptPre) = ptAux;
                ptAux = ptAux->prox;
            }
        }
    }
}

//========================================================================//
// Objetivo: inserir um nó na lista mantendo a ordenação, conforme seu campo chave
//========================================================================//
void addNoLcse(NO **ptList, int x) {
    NO *pt, *ptPre, *ptAux, *ptSuc;


    /*Ocupando um novo nó*/
    if ( (pt = (NO *)malloc(sizeof(NO))) == NULL ) {
        return;
    } 
    pt->key = x;

    /*Definindo a posição do nó alocado na lista*/
    if ( (*ptList) == NULL ) {
        /*caso for o primeiro nó da lista*/
        (*ptList) = pt;
        pt->prox = pt;
    } else {
        /*caso tiver mais de um nó na lista*/

        /*buscar a posição que será inserido o nó*/
        searchAuxLcse((*ptList), x, &ptPre, &ptSuc);

        if ( ptPre == ptSuc) {
            if (x < ptPre->key) {
                /*inserir no começo da lista*/
                ptAux = (*ptList);

                /*buscar o ultimo elemento da lista*/ 
                while (ptAux->prox != (*ptList)) {
                    ptAux = ptAux->prox;
                } 

                pt->prox = ptSuc;
                ptAux->prox = pt;
                (*ptList) = pt;
            } else {
                /*inserir no segundo nó da lista*/
                pt->prox = ptSuc;
                ptPre->prox = pt; 
            }
        } else {
            /*inserir no meio/final*/
            ptPre->prox = pt;
            pt->prox = ptSuc; 
        }
    }
}   

//========================================================================//
// Objetivo: remover um nó na lista mantendo a ordenação
//========================================================================//
void removeNoLcse(NO **ptList, int x) {
    NO *ptPre, *pt, *ptAux;

    if ( (*ptList) != NULL ) {
        pt = NULL;

        if ( (*ptList)->key == x ) {
            pt = (*ptList);
            ptPre = (*ptList);
        } else {
            ptAux = (*ptList)->prox;
            ptPre = (*ptList);

            while ( ptAux != (*ptList)  ) {
                if (ptAux->key == x) {  
                    pt = ptAux;
                    ptAux = (*ptList);
                } else {
                    ptPre = ptAux;
                    ptAux = ptAux->prox;
                }
            }
        }

        if (pt != NULL) {
            if (pt == ptPre) { 
                if (pt->prox == pt) {
                    /*caso em que o nó a ser removido for o unico na lista*/ 
                    free(pt);
                    (*ptList) = NULL;
                } else {
                    /*caso em que o nó a ser removido está na primeira posição da lista*/
                    ptAux = (*ptList);

                    while (ptAux->prox != (*ptList)) {
                        ptAux = ptAux->prox;
                    }
                    ptPre = ptAux;

                    (*ptList) = pt->prox;
                    ptPre->prox = pt->prox;
                    free(pt);
                }
            } else {
                /*caso em que o nó a ser removido está no meio ou no final da lista*/ 
                ptPre->prox = pt->prox;
                free(pt);
            }
        } else {
            printf("\nErro... o elemento %d nao pertence a lista\n", x);
        }
    } else {
        printf("\nLista Vaiza..\n");
    }
}

//========================================================================//
// Objetivo: imprimir todos os elementos da lista
//========================================================================//
void printLcse(NO *ptr) {
    NO *ptFirst;
    int count = 0;

    gfx_clear();
    if (ptr != NULL) {
        ptFirst = ptr;
        printf("\nLista: ptLista->");
        do {
            printf("[%d]->", ptr->key);
            gfxNoSimple(count, ptr->key);
            ptr = ptr->prox;
            if (ptr != ptFirst)
                gfxArrowLeftToRight(count);
            count++;
        }  while (ptr != ptFirst); 
            gfxArrowLeftToStart(count-1); 
    } else {
        printf("\nLista Vazia!\n");
    }
    gfx_paint();
}

//========================================================================//
// Objetivo: desalocar todos os nós da lista
//========================================================================//
void freeLcse(NO **ptList) {
    NO *ptAux, *pt;

    if ( (*ptList) != NULL) {
        ptAux = (*ptList)->prox;

        while (ptAux != (*ptList)) {
            pt = ptAux;
            ptAux = ptAux->prox;
            free(pt);
        }

        pt = (*ptList);
        free(pt);
        (*ptList) = NULL;
    }
}




//***************************************************************************//
/*Lista Duplamente Encadeada ordenada sem nó cabeça*/
//***************************************************************************//

//========================================================================//
// Objetivo: inicializar a lista duplamente encadeada, ou seja, alocar o nó
// cabeça da lista
//========================================================================//
void initLde(LDENO **ptList) {
    LDENO *pt;

    // criar/alocar o nó cabeça
    if ( (pt = (LDENO*)malloc(sizeof(LDENO))) == NULL) {
        return;
    }

    pt->prev = pt;
    pt->next = pt;
    (*ptList) = pt;
}

//========================================================================//
// Objetivo: buscar um nó na lcse (lista circular simplesmente encadeada), 
// conforme seu campo chave 
//========================================================================//
void searchNoLde(LDENO *ptList, int x) {
    LDENO *ptAux = ptList;
    
    if (ptAux->next == ptList) {
        printf("\nLista Vazia!\n");
    } else {
        ptAux = ptAux->next;

        while (ptAux != ptList) {
            if (ptAux->key == x) {
                printf("\n%d esta na lista\n", x);
                return;
            }
            ptAux = ptAux->next;
        }

        printf("\n%d nao esta na lista\n", x);
    }
}

//========================================================================//
// Objetivo: inserir nós na lista
//========================================================================//
void addNoLde(LDENO **ptList, int x) {
    LDENO *pt, *previous;

    // criar/alocar o nó
    if ( (pt = (LDENO*)malloc(sizeof(LDENO))) == NULL) {
        return;
    }
    //colocar o campo chave
    pt->key = x;
    //ajustar os ponteiros do nó e adicioná-lo na lista
    pt->next = (*ptList);
    previous = (*ptList)->prev;
    previous->next = pt;
    pt->prev = previous;
    (*ptList)->prev = pt;    
}

//========================================================================//
// Objetivo: buscar uma posição da lista para remover um nó
//========================================================================//
void searchToRemoveLde(LDENO *ptList, LDENO **ptPre, LDENO **ptCur, int x) {
    LDENO *ptAux;

    ptAux = ptList->next;
    (*ptPre) = ptList;

    while ( ptAux != ptList) {
        if (ptAux->key == x) {
            (*ptCur) = ptAux;
            ptAux = ptList;
        } else {
            (*ptPre) = ptAux;
            ptAux = ptAux->next;
        }
    } 
}

//========================================================================//
// Objetivo: remover nós na lista
//========================================================================//
void removeNoLde(LDENO **ptList, int x) {
    LDENO *ptAux = (*ptList), *ptCur = NULL, *ptPre = NULL, *prox;

    if (ptAux->next == (*ptList) && ptAux->prev == (*ptList)) {
        printf("\nLista Vazia");
    } else {
        
        searchToRemoveLde((*ptList), &ptPre, &ptCur, x);

        if (ptCur != NULL) {
            ptPre->next = ptCur->next;
            prox = ptCur->next;
            prox->prev = ptPre;

            free(ptCur);

        } else {    
            printf("\nNao Existe na Lista");
        }
    }
}

//========================================================================//
// Objetivo: imprimir os nós/campos da lista
//========================================================================//
void printLde(LDENO *ptList) {
    LDENO *ptAux = ptList;
    int count = 0;

    gfx_clear();
    printf("\nLISTA:");
    printf("\nptLista -> NO-Cabeca -> ");
    gfxNoHead(count);
    if (ptAux->prev == ptList) {
        gfxArrowLeftToStart(count);
        gfxArrowRightToEnd(count);
    } else {
        gfxArrowDuo(count);
    }
    count++;
    if (ptAux->prev != ptList) {
        ptAux = ptAux->next;
        while (ptAux != ptList) {
            printf("[%d] <-> ", ptAux->key);
            gfxNoDuo(count, ptAux->key);
            ptAux = ptAux->next;
            if (ptAux != ptList) {
                gfxArrowDuo(count);
            }
            count++;
        }
        gfxArrowLeftToStart(count-1);
        gfxArrowRightToEnd(count-1);
    }
    gfx_paint();
}

//========================================================================//
// Objetivo: desalocar todos os nós da lista
//========================================================================//
void freeLde(LDENO **ptList) {  
    LDENO *ptAux, *pt;
    
    if ( (*ptList) != NULL ) {
        ptAux = (*ptList)->next;

        while (ptAux != (*ptList)) {
            pt = ptAux;
            ptAux = ptAux->next;
            free(pt);
        }

        pt = (*ptList);
        free(pt);
        (*ptList) = NULL;
    }
}




//***************************************************************************//
/*Fila (FIFO)*/
//***************************************************************************//

//========================================================================//
// Objetivo: inserir nós na fila
//========================================================================//
void addNoQueue(NO **ptBegin, NO **ptEnd, int x) {
    NO *pt;

    /*Alocando um novo nó*/
    if ( (pt = (NO*)malloc(sizeof(NO))) == NULL ) {
        return;
    }
    pt->key = x;
    pt->prox = NULL;

    if ( (*ptBegin) == NULL) {
        /*Caso for o primeiro nó da fila*/
        (*ptBegin) = pt;
        (*ptEnd) = pt; 
    } else {
        /*caso existir mais de um nó, inserir no final da fila*/ 
        (*ptEnd)->prox = pt;
        (*ptEnd) = (*ptEnd)->prox; 
    }
}

//========================================================================//
// Objetivo: remover nós na fila
//========================================================================//
void removeNoQueue(NO **ptBegin, NO **ptEnd) {
    NO *pt;

    if ( (*ptBegin) != NULL) {
        pt = (*ptBegin);
        if ( (*ptBegin) != (*ptEnd)) {
            (*ptBegin) = (*ptBegin)->prox;
            free(pt);
        } else {
            /*Caso tiver apenas um nó na fila*/
            free(pt);
            (*ptBegin) = NULL;
            (*ptEnd) = NULL; 
        }
    } else {
        printf("\nFila Vazia!\n");
    }

}

//========================================================================//
// Objetivo: imprimir os nós(campo chave) da fila
//========================================================================//
void printQueue(NO *ptBegin) {
    NO *pt = ptBegin;
    int count = 0;

    gfx_clear();
    if (pt != NULL) {
        printf("\nFILA:");
        printf("\nptInicio -> ");
        while (pt != NULL) {
            printf("[%d] -> ", pt->key);
            gfxNoSimple(count, pt->key);
            gfxArrowLeftToRight(count);
            pt = pt->prox;
            count++;
        }    
        printf("NULL\n\n");
        gfxLambda(count-1);
    }
    gfx_paint();
}

//========================================================================//
// Objetivo: desalocar todos os nós da fila
//========================================================================//
void freeQueue(NO **ptBegin, NO **ptEnd) {
    NO *pt, *ptAux;

    if ( (*ptBegin) != NULL) {
        pt = (*ptBegin);
        while (pt != NULL) {
            ptAux = pt;
            pt = pt->prox;
            free(ptAux);
        }

        (*ptBegin) = NULL;
        (*ptEnd) = NULL;
    }
}




//***************************************************************************//
/*Pilha (LIFO)*/
//***************************************************************************//

//========================================================================//
// Objetivo: inserir nós na pilha
//========================================================================//
void addNoStack(NO **head, int x) {
    NO *pt;

    if ( (pt = (NO*)malloc(sizeof(NO))) == NULL) {
        return;
    }
    pt->key = x;
    pt->prox = (*head);
    (*head) = pt;
}

//========================================================================//
// Objetivo: remover nós na pilha
//========================================================================//
void removeNoStack(NO **head) {
    NO *pt;

    if ( (*head) != NULL ) {
        pt = (*head);
        (*head) = (*head)->prox;
        free(pt);
    } else {
        printf("\nPilha Vazia!\n");
    }
}

//========================================================================//
// Objetivo: imprimir os nós(campo chave) da pilha
//========================================================================//
void printStack(NO *head) {
    int count = 0;

    gfx_clear();
    if ( head != NULL) {
        printf("\nPILHA:");
        printf("\ntopo->");
        while (head != NULL) {
            printf("[%d]-> ", head->key);
            gfxNoStack(count, head->key);
            gfxArrowBottonToTop(count);
            count++;
            head = head->prox;
        }
        printf("NULL\n");
        gfxLambdaStack(count-1);
    } 
    gfx_paint();
}

//========================================================================//
// Objetivo: desalocar todos os nós da pilha
//========================================================================//
void freeStack(NO **head) {
    NO *pt, *ptAux;

    if ( (*head) != NULL ) {
        pt = (*head);

        while (pt != NULL) {
            ptAux = pt;
            pt = pt->prox;
            free(ptAux);
        }

        (*head) = NULL;
    }
}




//***************************************************************************//
/*Parte Gráfica das Estruturas*/
//***************************************************************************//

//========================================================================//
// Objetivo: Desenhar um nó simples e colocar o valor nele
//========================================================================//
void gfxNoSimple(int k, int val) {
    char value[32];
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;

    sprintf(value, "%d", val);

    //Desenhando o Nó
    gfx_set_color(255,200,0);
    gfx_rectangle(0+x,0+y,60+x,30+y);
    gfx_line(50+x,0+y,50+x,30+y);

    //Colocando o valor no Nó
    gfx_set_color(200,0,0);
    gfx_set_font_size(20);
    gfx_text(5+x,2+y, value);
}

//========================================================================//
// Objetivo: Desenhar setinha no sentido da esquerda para a direita 
//========================================================================//
void gfxArrowLeftToRight(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;
    //Desenhando a setinha da esquerda para a direita
    gfx_set_color(255,200,0);
    gfx_line(55+x,15+y,90+x,15+y); 
    gfx_line(90+x,15+y,80+x,20+y);
    gfx_line(90+x,15+y,80+x,10+y); 
}

//========================================================================//
// Objetivo: Desenhar o simbolo lambda, para representar o fim da lista
//========================================================================//
void gfxLambda(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;
    //desenha o lambda
    gfx_set_color(200,0,0);
    gfx_line(105+x, 15+y, 95+x, 25+y);
    gfx_line(100+x, 5+y, 110+x, 25+y);
}

//========================================================================//
// Objetivo: Desenhar uma setinha que sai do final da lista para o final
//========================================================================//
void gfxArrowLeftToStart(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90; 
    //Desenhando a setinha da esquerda para o inicio da lista
    gfx_set_color(255,200,0);
    gfx_line(55+x,15+y,75+x,15+y); 
    gfx_line(75+x, 15+y, 75+x, 50+y);
    gfx_line(75+x, 50+y, INITIAL_NO_X+30, 50+y);
    gfx_line(INITIAL_NO_X+30, 50+y, INITIAL_NO_X+30, 30+y);

    gfx_line(INITIAL_NO_X+30,30+y,INITIAL_NO_X+25,40+y);
    gfx_line(INITIAL_NO_X+30,30+y,INITIAL_NO_X+35,40+y); 
}

//========================================================================//
// Objetivo: Desenhar um nó para a lista duplamente encadeada e colocar o valor nele
//========================================================================//
void gfxNoDuo(int k, int val) {
    char value[32];
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;

    sprintf(value, "%d", val);
    //Desenhando o Nó
    gfx_set_color(255,200,0);
    gfx_rectangle(0+x,0+y,60+x,30+y);
    gfx_line(50+x,0+y,50+x,30+y);
    gfx_line(10+x,0+y,10+x,30+y);

    //Colocando o valor no Nó
    gfx_set_color(200,0,0);
    gfx_set_font_size(20);
    gfx_text(15+x,2+y, value);
}

//========================================================================//
// Objetivo: desenhar o nó cabeça da lista duplamente encadeada
//========================================================================//
void gfxNoHead(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;
    
    //Desenhando o Nó Cabeça
    gfx_set_color(0,0,150);
    gfx_filled_rectangle(10+x,0+y,50+x,30+y);

    
    gfx_set_color(255,200,0);
    gfx_rectangle(0+x,0+y,60+x,30+y);
    gfx_line(50+x,0+y,50+x,30+y);
    gfx_line(10+x,0+y,10+x,30+y);
}

//========================================================================//
// Objetivo: Desenhar uma setinha que sai do inicio da lista para o inicio 
//========================================================================//
void gfxArrowRightToEnd(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90; 
    //Desenhando a setinha da direita para o fim da lista
    gfx_set_color(255,200,0);
    
    gfx_line(INITIAL_NO_X+5, 15+y, INITIAL_NO_X-15, 15+y );
    gfx_line(INITIAL_NO_X-15, 15+y, INITIAL_NO_X-15, y-20);
    gfx_line(INITIAL_NO_X-15, y-20, 30+x, y-20);
    gfx_line(30+x, y-20, 30+x, y);
    
    gfx_line(30+x, y, 25+x, y-10);
    gfx_line(30+x, y, 35+x, y-10);    
}

//========================================================================//
// Objetivo: Desenhar duas setinhas:
//   - uma que sai do ponteiro apontando para o proximo
//   - uma que sai do ponteiro apontando para o anterior
//========================================================================//
void gfxArrowDuo(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    x += k*90;
    //Desenhando a setinha da esquerda para a direita
    gfx_set_color(255,200,0);
    gfx_line(55+x,5+y,90+x,5+y); 
    gfx_line(90+x,5+y,80+x,y);
    gfx_line(90+x,5+y,80+x,10+y);

    //Desenhando a setinha da direita para a esquerda
    gfx_set_color(255,200,0);
    gfx_line(60+x,25+y,95+x,25+y); 
    gfx_line(60+x,25+y,70+x,30+y);
    gfx_line(60+x,25+y,70+x,20+y);
}

//========================================================================//
// Objetivo: desenhar o nó para reprensentar a pilha
//========================================================================//
void gfxNoStack(int k, int val) {
    char value[32];
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    y += k*80;

    sprintf(value, "%d", val);

    // Desenhar o nó da pilha
    gfx_set_color(255,200,0);
    gfx_rectangle(0+x,y,50+x,y+40);
    gfx_line(0+x,y+30,50+x,y+30);

    //Colocando o valor no Nó
    gfx_set_color(200,0,0);
    gfx_set_font_size(20);
    gfx_text(5+x, y+2, value);
}

//========================================================================//
// Objetivo: desenhar uma setinha que tem sentido de baixo para cima
//========================================================================//
void gfxArrowBottonToTop(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    y += k*80; 

    //desenhar a setinha
    gfx_set_color(255,200,0);
    gfx_line(25+x, y+35, 25+x, y+80);
    gfx_line(25+x, y+80, 20+x, y+70);
    gfx_line(25+x, y+80, 30+x, y+70);
}

//========================================================================//
// Objetivo: Desenhar o simbolo lambda, para representar o fim da lista
//========================================================================//
void gfxLambdaStack(int k) {
    int x = INITIAL_NO_X, y = INITIAL_NO_Y;

    y += k*80;
    //desenha o lambda
    gfx_set_color(200,0,0);
    gfx_line(25+x, 100+y, 15+x, 110+y);
    gfx_line(20+x, 90+y, 30+x, 110+y);
}
