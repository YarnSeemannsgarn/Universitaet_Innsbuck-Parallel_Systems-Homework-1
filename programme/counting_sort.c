#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "common.h"

// https://en.wikipedia.org/wiki/Counting_sort
int *counting_sort(int *list, size_t N, int keys){
  int *count = calloc(keys, sizeof(int));
  
  int i;
  for(i=0; i<N; ++i){
    count[list[i]%keys] += 1;
  }

  int total = 0;
  int old_count;
  for(i=0; i<keys; ++i){
    old_count = count[i];
    count[i] = total;
    total += old_count;
  }

  int *sortedList = malloc(N*sizeof(int));
  for(i=0; i<N; ++i){
    sortedList[count[list[i]%keys]] = list[i];
    count[list[i]%keys] += 1;
  }

  free(count);
  free(list);
  return sortedList;
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
  printf("Starting counting sort for problem size %zu\n", N);
  begin = clock();
  list = counting_sort(list, N, RANGE_MAX);
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
