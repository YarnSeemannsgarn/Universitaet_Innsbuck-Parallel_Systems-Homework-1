#include <stddef.h>

#ifndef SEQUENTIAL_ALGORITHMS_H
#define SEQUENTIAL_ALGORITHMS_H

int** createMatrix(size_t M, size_t N);
void destroyMatrix(int** arr);

int** matrix_multiplication(int *matrix1, int *matrix2, size_t rows1, size_t columns1, size_t rows2, size_t columns2);

#endif
