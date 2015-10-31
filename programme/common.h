#include <stddef.h>
#include <stdlib.h>

#ifndef COMMON_H
#define COMMON_H

#define RANGE_MAX 10000
#define MEMORY_MESSAGE "Not enough memory. Choose a smaller problem size!\n"

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int **create_matrix(size_t M, size_t N)
{
    int *values = malloc(M * N * sizeof(int));
    int **rows = malloc(M * sizeof(int *));
    int i;
    for (i=0; i<M; ++i)
    {
        rows[i] = values + i*N;
    }
    return rows;
}

double **create_double_matrix(size_t M, size_t N)
{
    double *values = malloc(M * N * sizeof(double));
    double **rows = malloc(M * sizeof(double *));
    int i;
    for (i=0; i<M; ++i)
    {
        rows[i] = values + i*N;
    }
    return rows;
}


void destroy_matrix(int **matrix)
{
    free(*matrix);
    free(matrix);
}

void destroy_double_matrix(double **matrix){
  free(*matrix);
  free(matrix);
}

#endif
