/**
 * Aluno: João Vitor de Oliveira
 * Rgm: 38342
 * 
 * Trabalho 1 - Alocação encadeada
 * 
 * Linha de Compilação: gcc -o main main.c AllocLinked.c -I$(PWD)/gfx -L$(PWD)/gfx -lgfx -lSDL -lSDL_gfx -lSDL_ttf -Wall -Wextra -pedantic
**/
#include <stdio.h>
#include "AllocLinked.h"
#include "gfx/gfx.h"

#define TRUE 1
#define FALSE 0

int main() {
    NO *ptr = NULL;
    LDENO *ptDoubly = NULL; // para a duplamente encadeada
    NO *ptEnd = NULL; //para a fila
    int flag = FALSE, opt;
    int value;
    
    gfx_init(600, 500, "Alocação Encadeada");
    system("clear");
    printf("\nMENU\n");
    printf("\n[1]- Lista Simplesmente Encadeada (ordenada)");
    printf("\n[2]- Lista Circular Simplesmente Encadeada (ordenada)");
    printf("\n[3]- Lista Duplamente Encadeada (com no cabeca e sem ordenacao)");
    printf("\n[4]- Fila (FIFO)");
    printf("\n[5]- Pilha (LIFO)");
    printf("\nOpcao: ");
    scanf("%d", &opt);
    system("clear");

    if (opt == 1) {
        /*Lista Simplesmente Encadeada sem nó cabeça ordenada*/
        while (!flag) {
            printf("\nOperacoes:");
            printf("\n[1]-Busca");
            printf("\n[2]-Insercao");
            printf("\n[3]-Remocao");
            printf("\n[4]-Sair");
            printf("\nOpcao: ");
            scanf("%d", &opt);

            if (opt == 1) {
                /*Busca por um nó*/
                system("clear");
                printf("\n\nBuscar: ");
                scanf("%d", &value);
                searchNoLse(ptr, value);

            }

            if (opt == 2) {
                /*Inserção de um nó*/ 
                system("clear");
                printf("\n\nInserir: ");
                scanf("%d", &value);
                addNoLse(&ptr, value);
                printLse(ptr);
            }

            if (opt == 3) {
                /*Remoção de um nó*/ 
                system("clear");
                printf("\n\nRemover: ");
                scanf("%d", &value);
                removeNoLse(&ptr, value);
                printLse(ptr);
            }

            if (opt == 4) {
                /*Encerrar*/
                freeLse(&ptr);
                flag = TRUE;
            }
            printf("\n");
        }
    } 

    if (opt == 2) {
        /*Lista Circular Simpresmente Encadeada sem nó cabeça ordenada*/ 
        while (!flag) {
            printf("\nOperacoes:");
            printf("\n[1]-Busca");
            printf("\n[2]-Insercao");
            printf("\n[3]-Remocao");
            printf("\n[4]-Sair");
            printf("\nOpcao: ");
            scanf("%d", &opt);

            if (opt == 1) {
                /*Busca por um nó*/
                system("clear");
                printf("\n\nBuscar: ");
                scanf("%d", &value);
                searchNoLcse(ptr, value);
            }

            if (opt == 2) {
                /*Inserção de um nó*/ 
                system("clear");
                printf("\n\nInserir: ");
                scanf("%d", &value);
                addNoLcse(&ptr, value);
                printLcse(ptr);
            }

            if (opt == 3) {
                /*Remoção de um nó*/ 
                system("clear");
                printf("\n\nRemover: ");
                scanf("%d", &value);
                removeNoLcse(&ptr, value);
                printLcse(ptr);
            }

            if (opt == 4) {
                /*Encerrar*/ 
                freeLcse(&ptr);
                flag = TRUE;
            }
        }
    }

    if (opt == 3) {
        /*Lista Duplamente Encadeada com nó cabeça (sem ordenação)*/

        initLde(&ptDoubly);
        printLde(ptDoubly);
        while (!flag) {
            printf("\n[1]-Busca");
            printf("\n[2]-Insercao");
            printf("\n[3]-Remocao");
            printf("\n[4]-Sair");
            printf("\nOpcao: ");
            scanf("%d", &opt);

            if (opt == 1) {
                /*Busca por um nó*/
                system("clear");
                printf("\n\nBuscar: ");
                scanf("%d", &value);
                searchNoLde(ptDoubly, value);
            }

            if (opt == 2) {
                /*Inserção de um nó*/ 
                system("clear");
                printf("\n\nInserir: ");
                scanf("%d", &value);
                addNoLde(&ptDoubly, value);
                printLde(ptDoubly);               
            }

            if (opt == 3) {
                /*Remoção de um nó*/
                system("clear"); 
                printf("\n\nRemover: ");
                scanf("%d", &value);
                removeNoLde(&ptDoubly, value);
                printLde(ptDoubly);
            }

            if (opt == 4) {
                /*Encerrar*/ 
                flag = TRUE;
                freeLde(&ptDoubly);
            }
        }

    }

    if (opt == 4) {
        /*Fila (FIFO)*/
        while (!flag) {
            printf("\nOperacoes:");
            printf("\n[1]-Insercao");
            printf("\n[2]-Remocao");
            printf("\n[3]-Sair");
            printf("\nOpcao: ");
            scanf("%d", &opt);

            if (opt == 1) {
                /*Inserção de um nó*/ 
                system("clear");
                printf("\n\nInserir: ");
                scanf("%d", &value);
                addNoQueue(&ptr, &ptEnd, value);
                printQueue(ptr);
            }

            if (opt == 2) {
                /*Remoção de um nó*/ 
                system("clear");
                printf("\n\nRemovendo...");
                removeNoQueue(&ptr, &ptEnd);
                printQueue(ptr);
            }

            if (opt == 3) {
                /*Encerrar*/ 
                flag = TRUE;
                freeQueue(&ptr, &ptEnd);
            }
        }
    }

    if (opt == 5) {
        /*Pilha (LIFO)*/
        while (!flag) {
            printf("\nOperacoes:");
            printf("\n[1]-Insercao");
            printf("\n[2]-Remocao");
            printf("\n[3]-Sair");
            printf("\nOpcao: ");
            scanf("%d", &opt);

            if (opt == 1) {
                /*Inserção de um nó*/ 
                system("clear");
                printf("\n\nInserir: ");
                scanf("%d", &value);
                addNoStack(&ptr, value);
                printStack(ptr);
            }

            if (opt == 2) {
                /*Remoção de um nó*/ 
                system("clear");
                printf("\n\nRemovendo...");
                removeNoStack(&ptr);
                printStack(ptr);
            }

            if (opt == 3) {
                /*Encerrar*/ 
                flag = TRUE;
                freeStack(&ptr);
            }
        }
    }

    gfx_quit(); 

    return 0;
}
