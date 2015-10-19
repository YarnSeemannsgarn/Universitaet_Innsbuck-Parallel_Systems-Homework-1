#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequential_algorithms.h"

int** call_matrix_multiplication(size_t N){
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

double* call_gaussian_elimination(size_t N){
  double a[N*N];
  double b[N];
  double* x = calloc(N, sizeof(double));
  double random_double;
  int i, j;

  for(i=0; i<N; ++i){
    random_double = ((double)rand()/(double)RAND_MAX);
    b[i] = random_double;
    for(j=0; j<N; ++j){
      random_double = ((double)rand()/(double)RAND_MAX);
      a[i*N+j] = random_double;
    }
  }

  gaussian_elimination(a, b, x, N);
  return x;
}

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: %s <array-dimension>\n", argv[0]);
    return 1;
  }
  size_t N = atoi(argv[1]);

  srand(time(NULL));

  int** result_matrix_multiplication = call_matrix_multiplication(N);
  destroy_matrix(result_matrix_multiplication);

  double* result_gaussian_elimination = call_gaussian_elimination(N);
  free(result_gaussian_elimination);

  return 0;
}
