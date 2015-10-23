#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define RANGE_MAX 10000

int **create_matrix(size_t M, size_t N);
void destroy_matrix(int **arr);

#endif
