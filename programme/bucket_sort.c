#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#include "common.h"

struct bucket_t{
  int *values;
  int counter;
};

// For quicksort
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

// Algorithm from https://en.wikipedia.org/wiki/Bucket_sort#Pseudocode
int bucket_sort(int *list, size_t N, int bucket_count){
  // Set up an array of initially empty "buckets".
  struct bucket_t buckets[bucket_count];
  int i;
  for(i=0; i<bucket_count; ++i){
    buckets[i].values = malloc(N * sizeof(int)); // allocate initial list size memory for each bucket, 
                                              // because one bucket could contain all values... 
                                              // can be optimized with linked list, but than the sorting is
                                              // more complicated
    if(buckets[i].values == NULL){
      fprintf(stderr, MEMORY_MESSAGE);
      return EXIT_FAILURE;
    }
    buckets[i].counter = 0;
  }
  
  // Scatter: Go over the original array, putting each object in its bucket.
  struct bucket_t *current_bucket;
  int bucket_size = (int) ceil(((double) RANGE_MAX) / ((double) bucket_count));
  int *elem;
  for(i=0; i<N; ++i){
    elem = &list[i];
    current_bucket = &buckets[*elem / bucket_size];
    current_bucket->values[current_bucket->counter] = *elem;
    current_bucket->counter++;
  }
  
  // Sort each non-empty bucket. (with quicksort)
  // Gather: Visit the buckets in order and put all elements back into the original array.
  int j;
  int k = 0;
  for(i=0; i<bucket_count; ++i){
    current_bucket = &buckets[i];
    qsort(current_bucket->values, current_bucket->counter, sizeof(int), cmpfunc);
    for(j=0; j<current_bucket->counter; ++j){
      list[k] = current_bucket->values[j];
      ++k;
    }
    free(current_bucket->values); // Free bucket
  }

  return EXIT_SUCCESS;
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

  // Calculate bucket count as the floored square root of N
  int bucket_count = (int) floor(sqrt(((double) N)));

  // Measure time
  clock_t begin, end;
  double time_spent;
  int bucket_sort_result;
  printf("Starting bucket sort for problem size %zu and %i buckets\n", N, bucket_count);
  begin = clock();
  bucket_sort_result = bucket_sort(list, N, bucket_count);
  if(bucket_sort_result != EXIT_SUCCESS){
    return EXIT_FAILURE;
  }
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
