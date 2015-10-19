#include <stddef.h>

#ifndef SEQUENTIAL_ALGORITHMS_H
#define SEQUENTIAL_ALGORITHMS_H

// Helper
int** create_matrix(size_t M, size_t N);
void destroy_matrix(int** arr);
void swap_row(double *a, double *b, int r1, int r2, int n);

// Algorithms
int** matrix_multiplication(int *matrix1, int *matrix2, size_t rows1, size_t columns1, size_t rows2, size_t columns2);
void gaussian_elimination(double *a, double *b, double *x, int n);

#endif
