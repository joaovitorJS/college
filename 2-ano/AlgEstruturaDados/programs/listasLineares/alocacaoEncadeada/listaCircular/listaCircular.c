/**
 * Autor: João Vitor de Oliveira
*/

#include <stdio.h>
#include <stdlib.h>

// Defenindo a estrutura do nó
typedef struct no {
    int key;
    struct no *prox;
} NO;

void addNO(NO **, int);
void search(NO *, NO **, NO **, int);
void searchNO(NO *, int);
void removeNO(NO **, int);

int main() {
    NO *ptr = NULL;
    int opc = 1, x;

    while (opc != 0) {

        printf("\n\nMENU");
        printf("\n[1] - Search");
        printf("\n[2] - Insert");
        printf("\n[3] - Remove");
        printf("\n[4] - Exit");
        printf("\nOption: ");
        scanf("%d", &opc);
        system("clear");

        if (opc == 1) {
            printf("\nValue search: ");
            scanf("%d", &x);
            searchNO(ptr, x);
        } else if (opc == 2) {
            printf("\nValue insert: ");
            scanf("%d", &x);
            addNO(&ptr, x);
        } else if (opc == 3) {
            printf("\nValue remove: ");
            scanf("%d", &x);
            removeNO(&ptr, x);
        } else if (opc == 4) {
            opc = 0;
        }
    }

    free(ptr);

    return 0;
}

//===========================================================================//
// Objetivo da função: buscar um nó com o campo chave na lista, 
// para as inserções e remoções
//===========================================================================//
void search(NO *pt, NO **ant, NO **ptr, int x) {
    NO *ptAux;
    
    (*ant) = pt;

    if (pt->key == x) {
        // caso em que o elemento se encontra na primeira posição
        (*ptr) = pt;
    } else {
        // caso não estaja ou nao exista na lista
        ptAux = pt->prox;

        while (ptAux != pt) {
            if (ptAux->key == x) {
                (*ptr) = ptAux;
                ptAux = pt;
            } else {
                (*ant) = ptAux;
                ptAux = ptAux->prox;
            }
        }
    }
}

//===========================================================================//
// Objetivo da função: inserir um nó na lista e colocar um campo chave nele
//===========================================================================//
void addNO(NO **ptList, int x) {
    NO *ptr = NULL;
    NO *ant = NULL;

    if ( (*ptList) == NULL ) {
        // caso onde a lista está vazia e deseja ocupar o primeiro nó
        if ( (ptr = (NO*)malloc(sizeof(NO))) == NULL ) {
            return;
        } else {
            ptr->key = x;
            ptr->prox = ptr;
            (*ptList) = ptr;
            printf("\nSuccess...\n");
        } 
    } else {
        // caso tenha mais de um elemento na lista

        // buscar para ver se o elemento a ser inserido não se encontra na lista
        search((*ptList), &ant, &ptr, x);

        if (ptr == NULL) {
            // caso ele não se encontre na lista, ocupar um novo nó para ele
            if ( (ptr = (NO*)malloc(sizeof(NO))) == NULL ) {
                return;
            } else {
                ptr->key = x;
                ptr->prox = (*ptList);
                ant->prox = ptr;
                printf("\nSuccess...\n");
            }
        } else {
            // caso o elemento já esteja na lista
            printf("\nError... \nElement is already on the list\n");
        }
    }
}

//===========================================================================//
// Objetivo da função: remover um nó na lista, conforme o campo chave dele
//===========================================================================//
void removeNO(NO **ptList, int x) {
    NO *ant = NULL;
    NO *ptr = NULL;
    NO *aux = NULL;
    
    if ( (*ptList) == NULL) {
        // caso a lista esteja vazia
        printf("\nEmpty List!\n");
    } else {
        // busca pela elemento na lista
        search((*ptList), &ant, &ptr, x);

        if (ptr == ant) {            
            if (ptr == ptr->prox) {
                // caso tenha apenas um elemento na lista
                free(ptr);
                (*ptList) = NULL;
                printf("\nSuccess...\n");
            } else {
                // caso onde o elemento a ser removido se encontra na primeira posição da lista
                
                aux = ptr->prox;

                // coloca o ponteiro "ant" na ultima posição da lista
                while (aux != ptr) {
                    ant = aux;
                    aux = aux->prox;
                }

                // aujusta os ponteiros
                ant->prox = ptr->prox;
                (*ptList) = ptr->prox;
                // desocupa o nó
                free(ptr);
                printf("\nSuccess...\n");
            }
        } else {
            if (ptr != NULL) {
                // caso onde o elemnto a ser removido se encontra no meio/fim da lista

                //ajusta os ponteiros
                ant->prox = ptr->prox;

                //desocupa o nó
                free(ptr);
                printf("Success...");
            } else {
                // caso o elemento não se encontra na lista
                printf("\nError... \nElement doesn't in list\n");
            }
        }
    }
}

//===========================================================================//
// Objetivo da função: buscar um nó na lista, conforme o campo chave dele
//===========================================================================//
void searchNO(NO *pt, int x) {
    NO *ptAux = NULL;
    int flag = 0;
    
    if (pt == NULL) {
        printf("\nEmpty List!\n");
    } else {
        if (pt->key == x) {
            // caso em que o elemento se encontra na primeira posição
            printf("\nThe elementy %d is on the list!\n", x);   
        } else {
            // caso não estaja ou nao exista na lista
            ptAux = pt->prox;

            while (ptAux != pt) {
                if (ptAux->key == x) {
                    printf("\nThe elementy %d is on the list!\n", x);
                    flag = 1;   
                    ptAux = pt;
                } else {
                    ptAux = ptAux->prox;
                }
            }

            if (!flag) {
                printf("\nThe elementy %d doesn't on the list!\n", x);
            }
        }
    }
}
