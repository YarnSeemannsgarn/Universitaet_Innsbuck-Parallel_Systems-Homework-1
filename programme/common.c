#include "common.h"
#include <stdlib.h>

int **create_matrix(size_t M, size_t N)
{
    int *values = malloc(M*N*sizeof(int));
    int **rows = malloc(N*sizeof(int*));
    int i;
    for (i=0; i<N; ++i)
    {
        rows[i] = values + i*M;
    }
    return rows;
}

void destroy_matrix(int **arr)
{
    free(*arr);
    free(arr);
}
