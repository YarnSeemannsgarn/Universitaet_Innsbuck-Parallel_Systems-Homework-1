#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "common.h"

// https://en.wikipedia.org/wiki/Selection_sort#Implementation
void selection_sort(int *list, size_t N){
  int i, j, iMin, tmp;
  for(j=0; j<N-1; ++j){
    iMin = j;
    for(i=j+1; i<N; ++i){
      if(list[i] < list[iMin]){
	iMin = i;
      }
    }

    if(iMin != j){
      tmp = list[j];
      list[j] = list[iMin];
      list[iMin] = tmp;
    }
  }
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2){
    fprintf(stderr, "Usage: %s <problem-size>\n", argv[0]);
    return EXIT_FAILURE;
  }
  size_t N = atoi(argv[1]);

  // Create and initialise list
  int *list = (int *) malloc(N * sizeof(int));
  if(list == NULL){
    fprintf(stderr, MEMORY_MESSAGE);
    return EXIT_FAILURE;
  }
  int i;
  srand48(time(NULL));
  for(i=0; i<N; ++i){
    list[i] = lrand48() % RANGE_MAX;
  }

  // Measure time
  clock_t begin, end;
  double time_spent;
  printf("Starting selection sort for problem size %zu\n", N);
  begin = clock();
  selection_sort(list, N);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  // Check
  // for(i=0; i<N; ++i){
  //   printf("%i\n", list[i]);
  // }

  // Free memory
  free(list);

  return EXIT_SUCCESS;
}
