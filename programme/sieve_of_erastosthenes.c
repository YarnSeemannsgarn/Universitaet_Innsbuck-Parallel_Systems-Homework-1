#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <time.h>

#include "common.h"

// Algorithms from https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Algorithm_and_variants
int *sieve_of_erastosthenes(size_t N){
  int *prime_numbers = (int *) malloc((N+1)*sizeof(int));
  if(prime_numbers == NULL){
    fprintf(stderr, MEMORY_MESSAGE);
    return NULL;
  }
  
  // Initialise
  prime_numbers[0] = 0; // 0 and 1 are no prime numbers
  prime_numbers[1] = 0;
  int i;
  for(i=2; i<=N; ++i){
    prime_numbers[i] = 1;
  }

  // Sieve
  int j;
  int end_sieve = ((int) ceil(sqrt((double) N)));
  for(i=2; i < end_sieve; ++i){
    if(prime_numbers[i] == 1){
      for(j=i*i; j<=N; j=j+i){
	prime_numbers[j] = 0;
      }
    }
  }

  return prime_numbers;
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Measure time
  clock_t begin, end;
  double time_spent;
  int *result;
  printf("Starting sieve of erastosthenes for problem size %zu\n", N);
  begin = clock();
  result = sieve_of_erastosthenes(N);
  if(result == NULL){
    return EXIT_FAILURE;
  }
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  // Free memory
  free(result);

  return EXIT_SUCCESS;
}
