#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "sequential_algorithms.h"

int** createMatrix(size_t M, size_t N)
{
    int* values = calloc(M*N, sizeof(int));
    int** rows = malloc(N*sizeof(int*));
    int i;
    for (i=0; i<N; ++i)
    {
        rows[i] = values + i*M;
    }
    return rows;
}

void destroyMatrix(int** arr)
{
    free(*arr);
    free(arr);
}

int** matrix_multiplication(int *matrix1, int *matrix2, size_t rows1, size_t columns1, size_t rows2, size_t columns2){
  int **result = createMatrix(rows1, columns2);
  int sum = 0;
  int i, j, k;

  for(i=0; i<rows1; ++i){
    for(j=0; j<columns2; ++j){
      for(k=0; k<rows2; ++k){
	sum = sum + matrix1[i*rows1+k] * matrix2[k*rows2+j];
      }
      result[i][j] = sum;
      sum = 0;
    }
  }

  return result;
}
