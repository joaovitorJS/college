/**
 * Aluno: João Vitor de Oliveira
 * Rgm: 38342
 * 
 * Trabalho 2 - Árvores binárias de busca
 * 
 * Linha de Compilação: gcc -o main main.c BinarySearchTree.c -I$(PWD)/gfx -L$(PWD)/gfx -lgfx -lSDL -lSDL_gfx -lSDL_ttf -Wall -Wextra -pedantic
**/
#include <stdio.h>
#include <stdint.h> 
#include "gfx/gfx.h"
#include "BinarySearchTree.h"
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

/*operações com arquivo*/
void openFileWrite(FILE**, char *); /*Parâmetros: (arquivo-abrir: referência, nome-aqruivo)*/
void openFileRead(FILE**, char *); /*Parâmetros: (arquivo-abrir: referência, nome-aqruivo)*/


int main() {
    S_NO *ptRoot = NULL;  /*ponteiro para a raiz*/
    int opc;
    int32_t x;
    FILE *fileBST;
    char nameFileWrite[128], nameFileRead[128];

    gfx_init(900, 600, "Arvore Binaria de Busca");

    do {
       
        printf("\nMenu\n");
        printf("[1]- Insercao\n");
        printf("[2]- Remocao\n");
        printf("[3]- Busca\n");
        printf("[4]- Grava a arvore em um arquivo\n");
        printf("[5]- Leitura da arvore em um arquivo\n");
        printf("Para SAIR um numero qualquer acima de 5!\n\n");
        printf("Qual opcao:   ");
        scanf("%d", &opc);

        if (opc == 1) {
            system("clear"); 
            printf("\nInserir:  ");
            scanf("%d", &x);
            addNoBinaryTree(&ptRoot, x);

            gfx_clear(); 
            printBinaryTreeGfx(ptRoot, 0, 900, 30);
            gfx_paint();
        }

        if (opc == 2) {
            system("clear");
            printf("\nRemover:  ");
            scanf("%d", &x);

            removeNoBinaryTree(&ptRoot, x);
            
            gfx_clear(); 
            printBinaryTreeGfx(ptRoot, 0, 900, 30);
            gfx_paint();
        }

        if (opc == 3) {
            system("clear");
            printf("Buscar:  ");
            scanf("%d", &x);
            searchBinaryTreeMsg(ptRoot, x);
        
        }

        if (opc == 4) {
            printf("\nEntre com o nome do arquivo: ");
            scanf("%s", nameFileWrite);

            /*abre o arquivo para gravação*/
            openFileWrite(&fileBST, nameFileWrite);

            if (fileBST != NULL) {
                /*grava a árvore no arquivo*/
                writeBST(ptRoot, fileBST);

                /*fecha arquivo*/
                fclose(fileBST);
            }
        }

        if (opc == 5) {
            printf("\nEntre com o nome do arquivo: ");
            scanf("%s", nameFileRead);

            /*abre o arquivo para leitura*/
            openFileRead(&fileBST, nameFileRead);

            if (fileBST != NULL) {
                /*lê árvore do arquivo*/
                S_NO *ptAux = NULL;

                readBST(&ptRoot, &ptAux, fileBST);

                gfx_clear(); 
                printBinaryTreeGfx(ptRoot, 0, 900, 30);
                gfx_paint();

                fclose(fileBST);
            }
        }
    } while (opc <= 5);
    
    gfx_quit();

    freeBinaryTree(&ptRoot, ptRoot);

    if (ptRoot == NULL)
        printf("\n\nexit...\n");


    return 0;
}

/*Abrir arquivo para gravação*/
void openFileWrite(FILE **fileBST, char *nameFile) {
    /*abrir o arquivo para escrita*/
    if ( (*fileBST = fopen((char*)nameFile, "wb")) == NULL ) {
        return;
    }

    printf("\n\nSucess...\n");
	fseek((*fileBST), 0, SEEK_SET); /*move o ponteiro para o inicio do arquivo*/
}

/*Abrir arquivo para leitura*/
void openFileRead(FILE **fileBST, char *nameFile) {
    /*abrir o arquivo para escrita*/
    if ( (*fileBST = fopen((char*)nameFile, "rb")) == NULL ) {
        printf("Error... na abertura do arquivo");
        return;
    }

    printf("\n\nSucess...\n");
	fseek((*fileBST), 0, SEEK_SET); /*move o ponteiro para o inicio do arquivo*/
}