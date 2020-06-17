/**
 *  Autor: João Vitor de Oliveira
 *  Programa que imprementa operações com lista Ordenda em alocação sequencial
 *  Operações: Inserção, Remoção, Busca  
*/

#include <stdio.h>

//Tamanho da lista//
#define M 20

void add(int [], int *, int);
void removeElement(int [], int *, int);
void printList(int [], int);
void searchElement(int [], int *, int);

int main() {
    int List[M];
    int n = -1; // numero de elementos da lista
    int key; 

    // inserção de elementos em ordem decrescente
    for (int i = 0; i < M/2; i++) {
        add(List, &n, (M/2)-i);
    }
    
    add(List, &n, 14);
    add(List, &n, 13);
    add(List, &n, 15);
    

    searchElement(List, &n, 23);
    searchElement(List, &n, 13);


    //imprimir a lista
    printList(List, n);

    printf("\n\n");

    // remoção de elementos em ordem decrescente
    for (int i = 0; i < M/2; i++) {
        removeElement(List, &n, (M/2)-i);
    }
    
    removeElement(List, &n, 14);
    removeElement(List, &n, 13);

    searchElement(List, &n, 13);

    //imprimir a lista
    printList(List, n);

    printf("\n\n");

    removeElement(List, &n, 15);

    //imprimir a lista
    printList(List, n);

    removeElement(List, &n, 3);
    
    return 0;
}

//===========================================================//
// Objetivo da função: inserir um elemento 'x' na lista
// Parametros: (Lista, numero de elementos, valor a ser inserido)
//===========================================================//
void add(int L[], int *n, int x) {
    int i, j, temp;

    if (*n < M-1) {
        L[(*n)+1] = x;
        
        i = 0;
        while (L[i] < x) {
            i++;
        }

        if (i == (*n)+1 || L[i] != x) {
        
            //inserir elemento na ultima posição - ja que ele é maior que todos os outros
            if (i == (*n)+1) {
                L[i] = x;
            } else {
                // tira o elemento a ser inserido da ultima posição e coloca ele no lugar certo 
                for ( j = (*n)+1; j > i; j--)
                {
                    temp = L[j];
                    L[j] = L[j-1];
                    L[j-1] = temp;
                }
            }
            (*n)++;
        } else {
            printf("Elemento ja se encontra na lista\n");
        }
    } else {
        printf("Lista cheia\n");
    }
}

//===========================================================//
// Objetivo da função: remover um elemento 'x' na lista
// Parametros: (Lista, numero de elementos, valor a ser removido)
//===========================================================//
void removeElement(int L[], int *n, int x) {
    int i, j, temp;
    
    if ( (*n) >= 0) {
        L[(*n)+1] = x;

        i = 0;
        while (L[i] < x) {
            i++;
        } 

        if (i == (*n)+1 || L[i] != x ) {
            printf("Elemento nao se encontra na lista\n");
        } else {
            // retira o ultimo elemento
            if ( i == (*n)) {
                (*n)--;
            } else {
                // coloca o elemento a ser retirado na ultmia posição
                for ( j = i; j < (*n)+1; j++)
                {
                    temp = L[j];
                    L[j] = L[j+1];
                    L[j+1] = temp;
                }
                (*n)--; //retira o ultimo elemento
            }
        }
    } else {
        printf("Lista Vazia\n");
    }
}

//===========================================================//
// Objetivo da função: buscar um elemento 'x' na lista
// Parametros: (Lista, numero de elementos, valor a ser removido)
//===========================================================//
void searchElement(int L[], int *n, int x) {
    int i;

    if ((*n) >= 0 ) {
        i = 0;
        while (i <= (*n)) {
            if ( L[i] == x) {
                printf("Elemento se encontra na lista\n");
                i += (*n);
                return;
            } 
            i++;
        }

        printf("Elemento nao se encontra na lista\n");
    }
}

//===========================================================//
// Objetivo da função: imprimir os elementos que estão na lista
// Parametros: (Lista, numero de elementos)
//===========================================================//
void printList(int L[], int n) {
    int j;

    for (j = 0; j <= n; j++) {
        printf("L[%d] = %d\n", j , L[j]);
    }
}
