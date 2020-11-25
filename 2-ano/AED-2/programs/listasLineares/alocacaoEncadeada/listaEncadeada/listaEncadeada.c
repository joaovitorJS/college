#include <stdio.h>
#include <stdlib.h>

// Defenindo a estrutura do nó
typedef struct no {
    int key;
    struct no *prox;
} NO;

void addNO(NO **, int);
void search(NO *, NO**, NO** , int);
void searchNO(NO *, int);
void removeNO(NO **, int);

int main() {

    NO *ptr = NULL;
    int opc = 1, x;

    while (opc != 0) {
        printf("\n\nMENU");
        printf("\n[1] - Busca");
        printf("\n[2] - Insere");
        printf("\n[3] - Remove");
        printf("\n[4] - Sair");
        printf("\nOpcao: ");
        scanf("%d", &opc);
        system("clear");

        if (opc == 1) {
            printf("\nBuscar valor: ");
            scanf("%d", &x);
            searchNO(ptr, x);
        } else if (opc == 2) {
            printf("\nInserir valor: ");
            scanf("%d", &x);
            addNO(&ptr, x);
        } else if (opc == 3) {
            printf("\nRemover valor: ");
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
void search(NO *ptr, NO **ptAux, NO **ptAnt, int x) {
    NO *aux = ptr;
    *ptAnt = ptr;

    while (aux != NULL) {
        if (aux->key == x) {
            *ptAux = aux;
            aux = NULL;
        } else {
            *ptAnt = aux;
            aux = aux->prox;
        }
    }
}

//===========================================================================//
// Objetivo da função: inserir um nó na lista e colocar um campo chave nele
//===========================================================================//
void addNO(NO **ptList, int x) {
    NO *ptAux = NULL;
    NO *ptAnt = NULL;

    // buscar para ver se o elemento ja existe na lista
    search(*ptList, &ptAux, &ptAnt, x);

    if (ptAux == NULL) {
        // alocar um 'nó'
        if ( (ptAux = (NO*)malloc(sizeof(NO))) == NULL){
            return; // caso de erro 
        } else {
            // configurar o 'nó' alocado
            ptAux->key = x;
            ptAux->prox = *ptList;
            *ptList = ptAux;
        }
        printf("\nSuccess...\n");
    } else {
        printf("\nError... \n");
        printf("elemento ja exite na lista\n");
    }
}

//===========================================================================//
// Objetivo da função: remover um nó na lista, conforme o campo chave dele
//===========================================================================//
void removeNO(NO **ptList, int x) {
    NO *ptAux = NULL;
    NO *ptAnt = NULL;

    if (*ptList != NULL) {
        // busca para ver se o elemento existe na lista
        search(*ptList, &ptAux, &ptAnt, x);

        if (ptAux != NULL) {
            if ( ptAnt != ptAux) {
                // caso for um elemento do meio/ultimo
                ptAnt->prox = ptAux->prox;
                free(ptAux);
            } else {
                if (ptAnt->prox != NULL) {
                    // caso for o primeiro elemento
                    *ptList = ptAnt->prox;
                    free(ptAnt);
                } else {
                    // caso tiver apenas um elemento
                    free(ptAnt);
                    *ptList = NULL;
                }
            }
            printf("\nSuccess...\n");
        } else {
            printf("\nError... \n");
            printf("elemento nao exite na lista\n");
        }
    } else {
        printf("Lista Vazia!\n");
    }
}


//===========================================================================//
// Objetivo da função: buscar um nó na lista, conforme o campo chave dele
//===========================================================================//
void searchNO(NO *ptr, int x) {
    NO *aux = ptr;

    if (aux != NULL) {
        while (aux != NULL) {
            if (aux->key == x) {
                printf("O elemento %d esta na lista\n", aux->key);
                aux = NULL;
                return;
            } else {
                aux = aux->prox;
            }
        }
        printf("Elemento nao encontrado!\n");
    } else {
        printf("Lista Vazia!\n");
    }
    
}