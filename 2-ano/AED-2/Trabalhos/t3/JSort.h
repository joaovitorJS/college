#ifndef JSORT_H
#define JSORT_H

/*
  Autor: João Vitor de Oliveira

  Biblioteca que implementa os seguintes algoritmos de ordenação:
    -Bubble-sort original;
    -Bubble-sort melhorado;
    -Insertion-sort;
    -Mergesort;
    -Quicksort com pivô sendo o último elemento;
    -Quicksort com pivô sendo um elemento aleatório;
    -Quicksort com pivô sendo a mediana de três;
    -Heapsort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void bubbleSortOrigin(int32_t *, long int);
void bubbleSortBest(int32_t *, long int);
void insertionSort(int32_t *, long int);
void mergeSort(int32_t *, int32_t *, long int, long int);
void quicksortLastElement(int32_t *, long int, long int);
void quicksortRandomElement(int32_t *, long int, long int);
void quicksortMedianThree(int32_t *, long int, long int);
void heapSort(int32_t *, long int);

#endif //JSORT_H



