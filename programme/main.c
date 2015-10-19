#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequential_algorithms.h"

int **call_matrix_multiplication(size_t N){
  int matrix1[N][N];
  int matrix2[N][N];
  int i, j;

  // Initialise matrices 
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      matrix1[i][j] = rand();
      matrix2[i][j] = rand();
    }
  }

  return matrix_multiplication(&matrix1[0][0], &matrix2[0][0], N, N, N, N);  
}

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: %s <array-dimension>\n", argv[0]);
    return 1;
  }
  size_t N = atoi(argv[1]);

  srand(time(NULL));

  int** result_matrix_multiplication = call_matrix_multiplication(N);
  destroyMatrix(result_matrix_multiplication);

  return 0;
}
