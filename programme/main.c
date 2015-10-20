#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sequential_algorithms.h"

#define RANGE_MAX 10000;

int** call_matrix_multiplication(size_t N){
  int matrix1[N][N];
  int matrix2[N][N];
  int i, j;
  int** result;
  clock_t begin, end;
  double time_spent;

  // Initialise matrices 
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      matrix1[i][j] = lrand48() % RANGE_MAX;
      matrix2[i][j] = lrand48() % RANGE_MAX;
    }
  }
  
  printf("Starting matrix multiplication for problem size %zu\n", N);
  begin = clock();
  result = matrix_multiplication(&matrix1[0][0], &matrix2[0][0], N, N, N, N);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  return result;
}

double* call_gaussian_elimination(size_t N){
  double a[N*N];
  double b[N];
  double* x = calloc(N, sizeof(double));
  double random_double;
  int i, j;
  clock_t begin, end;
  double time_spent;

  // Initialise linear algebra system
  for(i=0; i<N; ++i){
    random_double = drand48() * RANGE_MAX;
    b[i] = random_double;
    for(j=0; j<N; ++j){
      random_double = drand48();
      a[i*N+j] = random_double;
    }
  }

  printf("Starting gaussian elimination for problem size %zu\n", N);
  begin = clock();
  gaussian_elimination(a, b, x, N);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  return x;
}

int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return 1;
  }
  
  // Restrict problem size to avoid segmentation faults due to memory limitations
  size_t N = atoi(argv[1]);
  if(N <= 0 || N > 1000){
    fprintf(stderr, "The problem size must be between 1 and 1000 (inclusive)\n");
    return 2;
  }
  
  srand48(time(NULL));
  
  int** result_matrix_multiplication = call_matrix_multiplication(N);
  destroy_matrix(result_matrix_multiplication);

  double* result_gaussian_elimination = call_gaussian_elimination(N);
  free(result_gaussian_elimination);

  return 0;
}
