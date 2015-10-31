#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "common.h"

// https://en.wikipedia.org/wiki/Gaussian_elimination
double *gaussian_elimination(double **matrix, size_t N){
  // Transform to echelon form
  double pivot, pivot_counterpart, scalar_multiple;
  int i, j, k;
  for(i=0; i<N-2; ++i){ // Pivot counter
    pivot = matrix[i][i];
    // If pivot == 0 --> return NULL
    if(pivot == 0){
      return NULL;
    }
    for(j=i+1; j<N-1; ++j){ // Row change counter
      pivot_counterpart = matrix[j][i];
      // No change needed in row
      if(pivot_counterpart == 0){
	break;
      }
      scalar_multiple = -pivot_counterpart / pivot;
      for(k=0; k<N; ++k){ // Column counter
	if(k <= i){
	  matrix[j][k] = 0;
	}
	else{
	  matrix[j][k] = matrix[j][k] + scalar_multiple * matrix[i][k];
	}
      }
    }
  }

  // Solve linear equations
  double *coefficient, *next_coefficient, *variable_value, *next_variable_value, scalar_add;
  for(i=N-2; i>=0; --i){ // Pivot counter
    coefficient = &matrix[i][i];
    variable_value = &matrix[i][N-1];
    // coefficent is not 1
    if(*coefficient != 1.0){
      scalar_multiple = 1 / (*coefficient);
      *coefficient = scalar_multiple * (*coefficient);
      *variable_value = scalar_multiple * (*variable_value);
    }    
    // coefficient is negativ
    if(*coefficient < 0){
      *coefficient = -(*coefficient);
      *variable_value = -(*variable_value);
    }

    for(j=i-1; j>=0; --j){ // Row counter
      next_coefficient = &matrix[j][i];
      next_variable_value = &matrix[j][N-1];
      scalar_add = -((*variable_value) * (*next_coefficient));
      *next_variable_value = (*next_variable_value) + scalar_add;
      *next_coefficient = 0;
    }
  }

  // Put variable values into vector
  double *variable_values = malloc((N-1) * sizeof(double));
  for(i=0; i<N-1; ++i){
    variable_values[i] = matrix[i][N-1];
  }
  return variable_values;
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // while loop for pivot element which are 0
  while(1){
    // Create and initialise list
    double **matrix = create_double_matrix(N-1, N);
    if(*matrix == NULL){
      fprintf(stderr, MEMORY_MESSAGE);
      return EXIT_FAILURE;
    }
    int i, j;
    double tmp;
    srand48(time(NULL));
    for(i=0; i<N-1; ++i){
      for(j=0; j<N; ++j){
	tmp = (drand48() * RANGE_MAX) - (RANGE_MAX / 2);
	while(tmp == 0){
	  tmp = (drand48() * RANGE_MAX) - (RANGE_MAX / 2);
	}
	matrix[i][j] = tmp;
      }
    }

    // Matrix before gaussian elimination
    // printf("Matrix before gaussian elimination:\n");
    // for(i=0; i<N-1; ++i){
    //   for(j=0; j<N; ++j){
    // 	printf("%f ", matrix[i][j]);
    //   }
    //   printf("\n");
    // }
    // printf("\n");

    // Measure time
    clock_t begin, end;
    double time_spent;
    double *result;
    printf("Starting gaussian elimination for problem size %zu\n", N);
    begin = clock();
    result = gaussian_elimination(matrix, N);
    if(result == NULL){
      printf("A pivot element is 0, create another matrix and start again\n");
      free(matrix);
      continue;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent: %fs\n", time_spent);

    // Matrix after gaussian elimination
    // printf("\nMatrix after gaussian elimination:\n");
    // for(i=0; i<N-1; ++i){
    //   for(j=0; j<N; ++j){
    // 	printf("%f ", matrix[i][j]);
    //   }
    //   printf("\n");
    // }
    // printf("\nVariable values:\n");
    // for(i=0; i<N-1; ++i){
    //   printf("%f ", result[i]);
    // }
    // printf("\n");

    // Free memory
    free(result);
    destroy_double_matrix(matrix);
    break;
  }

  return EXIT_SUCCESS;
}
