#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "common.h"

// Algorithm from https://en.wikipedia.org/wiki/Bubble_sort#Implementation
void bubble_sort(int *list, size_t N){
  int swapped = 0;
  do{
    swapped = 0;
    int i;
    for(i=1; i<N; ++i){
      if(list[i-1] > list[i]){
	swap(&list[i], &list[i-1]);
	swapped = 1;
      }
    }
  }while(swapped == 1);
}

int main(int argc, char *argv[]){
  // Handle parameter
  if(argc != 2 && argc != 3){
    fprintf(stderr, USAGE_MESSAGE, argv[0]);
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

  // Print list before sorting
  if(argc == 3){
    printf("List before sorting:\n");
    print_list(list, N);
  }

  // Measure time
  clock_t begin, end;
  double time_spent;
  printf("Starting bubble sort for problem size %zu\n", N);
  begin = clock();
  bubble_sort(list, N);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %fs\n", time_spent);

  // Print list after sorting
  if(argc == 3){
    printf("\nList after sorting:\n");
    print_list(list, N);
  }

  // Free memory
  free(list);

  return EXIT_SUCCESS;
}
