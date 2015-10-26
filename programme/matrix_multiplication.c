#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

int **create_matrix(size_t M, size_t N)
{
    int *values = malloc(M * N * sizeof(int));
    int **rows = malloc(N * sizeof(int *));
    int i;
    for (i=0; i<N; ++i)
    {
        rows[i] = values + i*M;
    }
    return rows;
}

void destroy_matrix(int **arr)
{
    free(*arr);
    free(arr);
}

int **matrix_multiplication(int **matrix1, size_t rows1, size_t columns1, int **matrix2, size_t rows2, size_t columns2){
  int **result = create_matrix(rows1, columns2);
  int sum = 0;
  int i, j, k;
  for(i=0; i<rows1; ++i){
    for(j=0; j<columns2; ++j){
      for(k=0; k<rows2; ++k){
	sum = sum + matrix1[i][k] * matrix2[k][j];
      }
      result[i][j] = sum;
      sum = 0;
    }
  }

  return result;
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create matrices
  int **matrix1 = create_matrix(N, N);
  int **matrix2 = create_matrix(N, N);
  if(*matrix1 == NULL || *matrix2 == NULL){
    fprintf(stderr, MEMORY_MESSAGE);
    return EXIT_FAILURE;
  }

  // Initialise matrices
  int i, j;
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      matrix1[i][j] = lrand48() % RANGE_MAX;
      matrix2[i][j] = lrand48() % RANGE_MAX;
    }
  }

  // Measure time
  clock_t begin, end;
  double time_spent;
  int **result;
  printf("Starting matrix multiplication for problem size %zu\n", N);
  begin = clock();
  result = matrix_multiplication(matrix1, N, N, matrix2, N, N);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  // Free memory
  destroy_matrix(matrix1);
  destroy_matrix(matrix2);
  destroy_matrix(result);

  return EXIT_SUCCESS;
}
