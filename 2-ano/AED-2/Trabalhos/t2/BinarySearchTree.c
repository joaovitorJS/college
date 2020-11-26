#include "BinarySearchTree.h"

//***************************************************************************//
/*Operações com arvóre binária de busca*/
//***************************************************************************/

/*Objetivo da função: Buscar um nó na árvore binária de busca, o ponteiro por
referência será o nó que achou o elemento, caso ache o mesmo*/
void searchBinaryTree(S_NO *pt, S_NO **ptr , int32_t x , int *f) {

    if (pt == NULL) {
        *f = 0; /*árvore vazia*/
        (*ptr) = pt;
    } else {
        if (pt->key == x) {
            *f = 1; /*achou o nó, e o ponteiro está apontando para ele*/
        } else {
            if (pt->key > x) {
                /*ir para a esquerda*/
                if (pt->ptLeft == NULL) {
                    *f = 2;
                    (*ptr) = pt;
                } else {
                    searchBinaryTree(pt->ptLeft, &(*ptr), x, f);
                }
                
            } else {
                /*ir para a direita*/
                if (pt->ptRight == NULL) {
                    *f = 3;
                    (*ptr) = pt;
                } else {
                    searchBinaryTree(pt->ptRight, &(*ptr), x, f);
                }
            }
        } 
    }
}

/*Objetivo da função: Buscar um nó na árvore binária de busca*/
void searchBinaryTreeMsg(S_NO *ptRoot, int32_t x) {
    S_NO *pt = ptRoot;
    S_NO *ptr = NULL;
    int f;

    searchBinaryTree(pt, &ptr, x, &f);

    if (f == 0) {
        printf("\nArvore Vazia...\n");
    } else if (f == 1) {
        printf("\nO elemento %d, pertence a arvore!\n", x);
    } else {
        printf("\nO elemento %d, nao pertence a arvore!\n", x);
    }
}

/*Objetivo da funcão: adicionar um nó na árvore binária de busca*/
void addNoBinaryTree(S_NO **ptRoot, int32_t x) {
    S_NO *pt = (*ptRoot), *ptCur = NULL, *ptr = NULL;
    int f;

    searchBinaryTree(pt, &ptr, x, &f);

    if (f == 1) {
        printf("Insersao Invalida...\n\n");
    } else {
        if ((ptCur = (S_NO*)malloc(sizeof(S_NO))) == NULL) {
            return;
        }
        ptCur->key = x;
        ptCur->ptLeft = NULL;
        ptCur->ptRight = NULL;
        ptCur->reserved = 0;
        
        /*caso for o primeiro nó da árvore*/
        if (f == 0) {
            (*ptRoot) = ptCur;
        } else {
            if (f == 2) {
                /*colocar a esquerda*/
                ptr->ptLeft = ptCur;
            } else {
                /*colocar a direita*/
                ptr->ptRight = ptCur;
            }
        }
    }
}

/*busca o nó a ser removido*/
void searchNo(S_NO *ptRoot, int32_t x, S_NO **ptZ, S_NO **ptP, int *f) {
    if (ptRoot == NULL || x == ptRoot->key) {
        (*ptZ) = ptRoot;
    } else {
        if ( x < ptRoot->key) { 
            (*ptP) = ptRoot;
            *f = 0;
            searchNo(ptRoot->ptLeft, x, &(*ptZ), &(*ptP), f);
        } else {
            (*ptP) = ptRoot;
            *f = 1;
            searchNo(ptRoot->ptRight, x, &(*ptZ), &(*ptP), f);
        }
    }
}

/*busca o nó de valor minimo*/
void minimum(S_NO *pt, S_NO **succ, S_NO **parentSucc) {
    if ((*succ)->ptLeft != NULL) 
        (*parentSucc) = (*succ);
    
    if (pt != NULL) {
        (*succ) = pt;
        minimum(pt->ptLeft, &(*succ), &(*parentSucc));
    }
}

/*busca o sucessor de um nó*/
void successor(S_NO *ptZ, S_NO **succ, S_NO **parentSucc) {
    S_NO *ptAux = ptZ->ptRight;

    (*succ) = ptAux;
    if (ptAux->ptLeft != NULL) {
        minimum(ptAux, &(*succ), &(*parentSucc));
    }
}

/*remove um nó da árvore binária de busca*/
void removeNoBinaryTree(S_NO **ptRoot, int32_t x) {
    S_NO *ptZ = NULL, *ptP = NULL, *succ = NULL, *parentSucc = NULL;
    int f;

    //ptZ contém o nó a ser removido -> se for diferente de NULL
    searchNo((*ptRoot), x, &ptZ, &ptP, &f);

    if (ptZ == NULL) {
        printf("remocao invalida...\n");
        return;
    }

    //O nó a ser removido não tem nenhum filho à esquerda
    if (ptZ->ptLeft == NULL) {

        if (ptP != NULL) {
            if (f) {
                //direita
                ptP->ptRight = ptZ->ptRight;
            } else {
                //esquerda
                ptP->ptLeft = ptZ->ptRight;
            }      
        } else {
            (*ptRoot) = ptZ->ptRight;
        }

        free(ptZ);

    } else {
        //O nó a ser removido não tem nenhum filho à direita
        if (ptZ->ptRight == NULL) {
            if (ptP != NULL) { 
                if (f) {
                    //direita
                    ptP->ptRight = ptZ->ptLeft;
                } else {
                    //esquerda
                    ptP->ptLeft = ptZ->ptLeft;
                }      
            } else {
                (*ptRoot) = ptZ->ptLeft;
            }

            free(ptZ);
        
        //O nó a ser removido tem filho à direita e à esquerda
        } else {
            /*buscar o successor do nó a ser removido*/
            successor(ptZ, &succ, &parentSucc);

            /*se o sucessor do nó a ser removido é filho direito do mesmo*/
            if (ptZ->ptRight == succ) {
                succ->ptLeft = ptZ->ptLeft;

                if (ptP != NULL) {
                    if (f) {
                        //direita
                        ptP->ptRight = succ;
                    } else {
                        //esquerda
                        ptP->ptLeft = succ;
                    }   
                } else {
                    (*ptRoot) = succ;    
                }

                free(ptZ);
            
            /*senão o sucessor do nó a ser removido não é filho direito do mesmo*/
            } else {
                parentSucc->ptLeft = succ->ptRight;
                succ->ptRight = ptZ->ptRight;
                succ->ptLeft = ptZ->ptLeft;

                if (ptP != NULL) {
                    if (f) {
                        //direita
                        ptP->ptRight = succ;
                    } else {
                        //esquerda
                        ptP->ptLeft = succ;
                    }
                } else {
                    (*ptRoot) = succ;
                }

                free(ptZ);
            }
        } 
    }
}

/*Imprimir a árvore binária de busca usando biblioteca gráfica gfx , usando o percurso
em pre ordem*/
void printBinaryTreeGfx(S_NO *ptRoot, unsigned xInitial, unsigned xEnd, unsigned y) {
    char buffer[32];
    unsigned xMiddle, radius = 20, xMiddleAux;

    if (ptRoot != NULL) {
        snprintf(buffer, 32, "%d", ptRoot->key);
        
        xMiddle = (xInitial + xEnd) / 2;
       
        if (ptRoot->ptLeft != NULL) {
            gfx_set_color(255, 0, 0);//vermelho
            xMiddleAux = (xMiddle + xInitial) / 2; 
            gfx_line(xMiddle, y, xMiddleAux, y+70);
        } 

        if (ptRoot->ptRight != NULL) {
            gfx_set_color(255, 0, 0);
            xMiddleAux = (xMiddle + xEnd) / 2; 
            gfx_line(xMiddle, y, xMiddleAux, y+70);
        }
        
        gfx_set_color(255, 255, 255);
        gfx_filled_ellipse(xMiddle, y+9, radius, radius);      
        
        gfx_set_color(255, 0, 0);
        gfx_ellipse(xMiddle, y+9, radius, radius);
        gfx_set_font_size(16);
        gfx_text(xMiddle-12, y, buffer);
        

        printBinaryTreeGfx(ptRoot->ptLeft, xInitial, xMiddle, y+70);
        printBinaryTreeGfx(ptRoot->ptRight, xMiddle, xEnd, y+70);
    }   

}

/*desaloca todos os nós da árvore*/
void freeBinaryTree(S_NO **ptRoot, S_NO *pt) {
    if(pt != NULL)
	{

		if(pt->ptLeft != NULL)
			freeBinaryTree(&(*ptRoot), pt->ptLeft);

		if(pt->ptRight != NULL)
			freeBinaryTree(&(*ptRoot), pt->ptRight);
			
		/*desaloca o ponteiro*/
		free(pt);	
	}

    (*ptRoot) = NULL;
}

/*grava a árvore que está na memória em um arquivo usando o percurso em pré-ordem*/
void writeBST(S_NO *ptRoot, FILE *fileBST) {

    S_ARQ_NO *ptRootFile = NULL;

    if (ptRoot != NULL) {
        /*alocar nó do tipo S_ARQ_NO para gravar ele no arquivo*/
        if ( (ptRootFile = malloc(sizeof(S_ARQ_NO))) == NULL ) {
            return;
        }

        /*"converte" os dados do nó S_NO para S_ARQ_NO*/
        
        /*ponteiro para a esquerda*/
        if (ptRoot->ptLeft != NULL) {
            ptRootFile->left = TRUE;
        } else {
            ptRootFile->left = FALSE;
        }

        /*ponteiro para a direita*/
        if (ptRoot->ptRight != NULL) {
            ptRootFile->right = TRUE;
        } else {
            ptRootFile->right = FALSE;
        }

        /*chave*/
        ptRootFile->key = ptRoot->key;

        /*grava o nó do tipo S_ARQ_NO no arquivo*/
        fwrite(ptRootFile, sizeof(S_ARQ_NO), 1, fileBST);

        free(ptRootFile);

        /*chamadas recursivas*/
        writeBST(ptRoot->ptLeft, fileBST);
        writeBST(ptRoot->ptRight, fileBST);
    } 
}

/*leitura da árvore ques está no aquivo usando percurso em pré-ordem*/
void readBST(S_NO **ptRoot, S_NO **ptAux , FILE *fileBST) {
    S_ARQ_NO *ptRootFile = NULL;

    /*alocar nó do tipo S_ARQ_NO para receber dados do arquivo*/
    if ( (ptRootFile = malloc(sizeof(S_ARQ_NO))) == NULL ) {
        return;
    }

    /*lê do arquivo um nó*/
    if ( fread(ptRootFile, sizeof(S_ARQ_NO), 1, fileBST) == 0 ) {
        /*caso tenha chegado ao fim do arquivo*/
        free(ptRootFile);
        return;
    }
   

    /*"convertendo" os dados do nó S_ARQ_NO para S_NO*/

    /*alocar nó do tipo S_NO para usar na memória*/
    if ( ((*ptAux) = malloc(sizeof(S_NO))) == NULL ) {
        return;
    }

    if ( (*ptRoot) == NULL) {
        (*ptRoot) = (*ptAux);
    }

    /*chave*/
    (*ptAux)->key = ptRootFile->key;

    /*ponteiro para a esquerda*/
    if (ptRootFile->left == TRUE) {
        readBST(ptRoot, &(*ptAux)->ptLeft, fileBST);
    } else {
        (*ptAux)->ptLeft = NULL;
    }

    /*ponteiro para a direita*/
    if (ptRootFile->right == TRUE) {
        readBST(ptRoot, &(*ptAux)->ptRight, fileBST);
    } else {
        (*ptAux)->ptRight = NULL;
    }

    free(ptRootFile);
}
