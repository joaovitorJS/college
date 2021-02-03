/**
 * Aluno: João Vitor de Oliveira
 * Rgm: 38342
 * 
 * Trabalho 5 - Algoritmos de Ordenação
 * 
 * Linha de Compilação: gcc -o main main.c JSort.c -Wall -Wextra -pedantic
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "JSort.h"

int openFile(FILE **file, char *fileName, char *op);

int main(int argc, char const *argv[]) {
  FILE *fileIn, *fileOut;
  char nameFileIn[256], nameFileOut[256];
  int numberAlg;
  long int fileSize;
  int32_t *array;
  int32_t *arrayTmp; /*usado apenas para o mergesort*/
  /*Para calcular o tempo de execução*/
	struct timeval tv1, tv2;
	double t1, t2;

  
  if (argc != 4) {
    printf("\nFaltam argumentos!\n");
    printf("Ex.: ./main numero_do_algoritmo arquivo_de_entrada arquivo_de_saida\n\n");
    return -1;
  } 

  numberAlg = atoi(argv[1]);
  if (numberAlg < 1 || numberAlg > 8) {
    printf("\nNumero do algoritmo invalido!\n\n");
    return -1;
  }

  strcpy(nameFileIn, argv[2]);
  if (!openFile(&fileIn, nameFileIn, "rb")) {
    printf("\nNao foi possivel abrir o arquivo de entrada!\n\n");
    return -1;
  }

  strcpy(nameFileOut, argv[3]);
  if (!openFile(&fileOut, nameFileOut, "wb")) {
    printf("\nNao foi possivel abrir o arquivo de saida!\n\n");
    return -1;
  }
  
  /*Calcula o tamanho do arquivo de entrada*/
  fseek(fileIn, 0, SEEK_END);
  fileSize = ftell(fileIn);
  fileSize = fileSize/sizeof(int32_t);
  fseek(fileIn, 0, SEEK_SET);

  /*aloca o vetor com o numero de elementos que tem no arquivo*/
  if ( (array = (int32_t*)malloc(fileSize * sizeof(int32_t))) == NULL ) {
    return -1;
  }

  /*armazena os elementos do arquivo de entrada no vetor*/
  fread(array, sizeof(int32_t), fileSize, fileIn);

  /*fecha o arquivo de entrada*/
  fclose(fileIn);

  printf("\nAlgoritmo de ordenacao: ");
  switch (numberAlg) {
  case 1:
    printf("Bubble-Sort Original\n");
    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    bubbleSortOrigin(array, fileSize);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;

  case 2:
    printf("Bubble-Sort Melhorado\n");
    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    bubbleSortBest(array, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;

  case 3:
    printf("Insertion-sort\n");
    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    insertionSort(array, fileSize);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;

  case 4:
    printf("Mergesort\n");
    
    /*Aloca o vetor auxiliar para o MergeSort*/
    if ( (arrayTmp = (int32_t*)malloc(fileSize * sizeof(int32_t))) == NULL ) {
      return -1;
    }

    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    mergeSort(array, arrayTmp, 0, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;

    /*desaloca o vetor auxiliar*/
    free(arrayTmp);
    break;

  case 5:
    printf("Quicksort com pivo sendo o ultimo elemento\n");
    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    quicksortLastElement(array, 0, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;
  
  case 6:
    printf("Quicksort com pivo sendo um elemento aleatorio\n");

    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    srand(time(NULL));
    quicksortRandomElement(array, 0, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;
  
  case 7:
    printf("Quicksort com pivo sendo a mediana de tres\n");
    
    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    quicksortMedianThree(array, 0, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;

  case 8:
    printf("Heapsort\n");

    /*Primeira coleta de tempo*/
    gettimeofday(&tv1, NULL);
    t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
    
    heapSort(array, fileSize-1);
    
    /*Segunda coleta de tempo*/
    gettimeofday(&tv2, NULL); 
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/ 1000000.00;
    break;
  }

  printf("Tempo gasto para ordenar (em segundos): %.3lf\n", (t2-t1));

  /*armazena o vetor já ordenado no arquivo de saida*/
  fwrite(array, sizeof(int32_t), fileSize, fileOut);

  /*desaloca o vetor principal*/
  free(array);
  /*fecha o arquivo de saida*/
  fclose(fileOut);

  return 0;
}

int openFile(FILE **file, char *fileName, char *op) {
  if ( (*file = fopen((char*)fileName, (char*)op)) == NULL ) {
    return 0;
  }
  fseek((*file), 0, SEEK_SET); /*move o ponteiro para o inicio do arquivo*/
  return 1;
}
