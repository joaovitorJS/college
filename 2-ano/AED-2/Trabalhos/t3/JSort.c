#include "JSort.h"

/**
 * Procedimento swapNumbers
 * Objetivo: Fazer a troca entre dois numeros
 * Parâmetros: - int32_t *a -> primeiro número passado por referência
 *             - int32_t *b -> segundo número passado por referência
 */
void swapNumbers(int32_t *a, int32_t *b) {
  int32_t temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Procedimento bubbleSortOrigin
 * Objetivo: fazer a ordenação por bolha sem critério de parada
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int len -> número de elementos desse vetor
 */
void bubbleSortOrigin(int32_t *array, long int len) {
  long int i, j;
  for (i = 0; i < len; i++) {
    for (j = 0; j < len-1; j++) {
      if (array[j] > array[j+1])
        swapNumbers(&array[j], &array[j+1]);
    }
  }
}

/**
 * Procedimento bubbleSortBest
 * Objetivo: fazer a ordenação por bolha com critério de parada
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int len -> número de elementos desse vetor - 1 
 */
void bubbleSortBest(int32_t *array, long int len) {
  long int change = 1, tempLen = len, guard = len, i;
  while (change) {
    i = 0;
    change = 0;
    while (i < tempLen) {
      if (array[i] > array[i+1]) {
        swapNumbers(&array[i], &array[i+1]);
        change = 1;
        guard = i;
      }
      i++;
    }
    tempLen = guard;
  }
}

/**
 * Procedimento insertionSort
 * Objetivo: fazer a ordenação por inserção
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int len -> número de elementos desse vetor
 */
void insertionSort(int32_t * array, long int len) {
  long int i, j, value;

  for (i = 1; i < len; i++) {
    value = array[i];
    j = i - 1;
    while (j >= 0 && value < array[j]) {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = value;
  }
}

/**
 * Procedimento merge
 * Objetivo: fazer a intercalação dos vetores
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - int32_t *arrayTmp -> vetor temporário
 *             - long int initial1 -> índice de inicio do vetor/subvetor, esse será o inicio do subvetor esquerdo
 *             - long int initial2 -> índice do centro+1 do vetor/subvetor, esse será o inicio do subvetor direito
 *             - long int end2 -> índice do fim do vetor/subvetor, esse será o fim do subvetor direito 
 */
void merge(int32_t *array, int32_t *arrayTmp, long int initial1, long int initial2, long int end2) {
  long int end1 = initial2-1, index = initial1, i, start = initial1;

  while (initial1 <= end1 && initial2 <= end2) {
    if (array[initial1] < array[initial2]) {
      arrayTmp[index] = array[initial1];
      initial1++;
    } else {
      arrayTmp[index] = array[initial2];
      initial2++;
    }
    index++;
  }

  while (initial1 <= end1) {
    arrayTmp[index] = array[initial1];
    initial1++;
    index++;
  }

  while (initial2 <= end2) {
    arrayTmp[index] = array[initial2];
    initial2++;
    index++;
  }

  for (i = start; i <= end2; i++) {
    array[i] = arrayTmp[i];
  }
}

/**
 * Procedimento mergeSort
 * Objetivo: fazer a ordenação por intercalação
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - int32_t *arrayTmp -> vetor temporário
 *             - long int left -> índice de inicio do vetor
 *             - long int right -> índice do fim do vetor 
 */
void mergeSort(int32_t *array, int32_t *arrayTmp, long int left, long int right) {
  long int center;

  if (left < right) {
    center = (left + right) / 2;
    mergeSort(array, arrayTmp, left, center);
    mergeSort(array, arrayTmp, center+1, right);

    merge(array, arrayTmp, left, center+1, right);
  }
}

/**
 * Procedimento quicksortLastElement
 * Objetivo: fazer a ordenação rápida, com o pivo sendo o último elemento
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int start -> índice de inicio do vetor
 *             - long int end -> índice do fim do vetor 
 */
void quicksortLastElement(int32_t array[],long  int start,long  int end) {
	int32_t value;
	long int i, j;

	if ((end - start) < 2) {
		if ((end-start) == 1) {
			if (array[start] > array[end]) {
				/*Troca de elementos*/
        swapNumbers(&array[start], &array[end]);
			}
		}

	} else {

		i = start;
		j = end-1;
		value = array[end];

		while (j > i) {
			while (array[i] < value) {
				i++;
			}
			while ((array[j] > value) && i<j) {
				j--;
			}

			if (j >	i) {
				/*Troca de elementos*/
        swapNumbers(&array[i], &array[j]);
				i++;
				j--;
			}
		}

		if (array[i] < array[end])
			i++;

		/*Troca de elementos*/
    swapNumbers(&array[i], &array[end]);

    quicksortLastElement(array, start, i-1);
    quicksortLastElement(array, i+1, end);
	}
}


/**
 * Procedimento quicksortRandomElement
 * Objetivo: fazer a ordenação rápida, com o pivo sendo um elemento aleatório
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int start -> índice de inicio do vetor
 *             - long int end -> índice do fim do vetor 
 */
void quicksortRandomElement(int32_t *array, long int start, long int end) {
  long int i = 0, j = 0;
  int32_t value = 0; 
  long int pivot = 0;

  if((end - start) < 2) {
    if((end - start) == 1)
      if(array[start] > array[end])
        swapNumbers(&array[start],&array[end]);
 
  } else {
    pivot = start + rand() % (end - start);
    swapNumbers(&array[pivot],&array[end]);

    i = start;
    j = end - 1;
    value = array[end];

    while(j >= i)
    {
      while(array[i] < value)
        i++;

      while(j >= 0 && array[j] > value)
        j--;

      if(j >= i) {
        swapNumbers(&array[i],&array[j]);
        i++;
        j--;
      }
    }
    swapNumbers(&array[i], &array[end]);
    quicksortRandomElement(array, start, i-1);
    quicksortRandomElement(array,i+1,end);
  }
}

/**
 * Procedimento calculeMedianOfThree
 * Objetivo: calcula a mediana de 3
 * Parâmetros: - long int start -> índice de inicio do subvetor    
 *             - long int end -> índice do fim do subvetor 
 *             - int32_t *array -> vetor a ser ordenado
 */
long int calculeMedianOfThree(long int start, long int end, int32_t *array) {
  long int middle = (start + end) / 2, medianIndex = 0;

  if (array[start] < array[middle]) {
    if (array[middle] < array[end]) {
      medianIndex = middle;
    } else {
      if (array[start] < array[end]) {
        medianIndex = end;
      } else {
        medianIndex = start;
      }
    }
  } else {
    if (array[end] < array[middle]) {
      medianIndex = middle;
    } else {
      if (array[end] < array[start]) {
        medianIndex = end;
      } else {
        medianIndex = start;
      }
    }
  }  

  return medianIndex;
}

/**
 * Procedimento quicksortMedianThree
 * Objetivo: fazer a ordenação rápida, com o pivo sendo um elemento obtido a partir da mediana de 3
 * Parâmetros: - int32_t *array -> vetor a ser ordenado
 *             - long int start -> índice de inicio do vetor
 *             - long int end -> índice do fim do vetor 
 */
void quicksortMedianThree(int32_t *array, long int start, long int end) {
  int32_t value;
	long int pivot, i, j;

	if ((end - start) < 2) {
		if ((end-start) == 1) {
			if (array[start] > array[end]) {
				/*Troca de elementos*/
				swapNumbers(&array[start], &array[end]);
			}
		}
	} else {
		/*Escolha de um pivo -> usando a mediana de 3*/
		pivot = calculeMedianOfThree(start, end, array);
    /*Troca de elementos*/
		swapNumbers(&array[pivot], &array[end]);
 
		i = start;
		j = end - 1;
		value = array[end];

		while (j >= i) {
			while (array[i] < value) {
				i++;
			}

			while (j > 0 && array[j] > value) {
				j--;
			}

			if (j >= i) {
				swapNumbers(&array[i], &array[j]);
				i++;
				j--;
			}
		}
    swapNumbers(&array[i], &array[end]);
    
    quicksortMedianThree(array, start, i-1);
  	quicksortMedianThree(array, i, end);
	}
}
/**
 * Procedimento siftDown ou descer
 * Objetivo: diminui a prioridade de um elemento
 * Parâmetros: - int32_t *array -> vetor representando um heap
 *             - long int i -> indice corrente
 *             - long int n -> número de elementos do heap
 */
void siftDown(int32_t *array, long int i, long int n) {
  long int j = 2 * i;
  
  if (j <= n) {
    if (j < n) {
      if (array[j+1] > array[j]) 
        j++;
    }

    if (array[i] < array[j]) {
      swapNumbers(&array[i], &array[j]);
      siftDown(array, j, n);
    }
  }
}

/**
 * Procedimento createHeap ou arrajar
 * Objetivo: fazer a construção do heap
 * Parametros: int32_t *array -> vetor com números inteiros
 *             long int n -> tamanho do vetor - 1
 */   
void createHeap(int32_t *array, long int n) {
  long int i = n / 2;
  while (i >= 0) {
    siftDown(array, i, n);
    i--;
  }
}

/**
 * Procedimento createHeap ou arrajar
 * Objetivo: fazer a ordenação em heap
 * Parametros: int32_t *array -> vetor a ser ordenado
 *             long int len -> números de elementos no vetor - 1
 */
void heapSort(int32_t *array, long int len) {
  long int i = len;
  createHeap(array, len);
  while (i > 0) {
    swapNumbers(&array[0], &array[i]);
    i--;
    siftDown(array, 0, i);    
  }
}