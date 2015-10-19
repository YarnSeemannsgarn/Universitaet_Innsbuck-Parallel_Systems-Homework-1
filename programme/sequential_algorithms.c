#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "sequential_algorithms.h"
#include <math.h>

// Helper
#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))

int** create_matrix(size_t M, size_t N)
{
    int* values = calloc(M*N, sizeof(int));
    int** rows = malloc(N*sizeof(int*));
    int i;
    for (i=0; i<N; ++i)
    {
        rows[i] = values + i*M;
    }
    return rows;
}

void destroy_matrix(int** arr)
{
    free(*arr);
    free(arr);
}

void swap_row(double *a, double *b, int r1, int r2, int n)
{
	double tmp, *p1, *p2;
	int i;
 
	if (r1 == r2) return;
	for (i = 0; i < n; i++) {
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	}
	tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}

// Algorithms
int** matrix_multiplication(int *matrix1, int *matrix2, size_t rows1, size_t columns1, size_t rows2, size_t columns2){
  int **result = create_matrix(rows1, columns2);
  int sum = 0;
  int i, j, k;

  for(i=0; i<rows1; ++i){
    for(j=0; j<columns2; ++j){
      for(k=0; k<rows2; ++k){
	sum = sum + matrix1[i*rows1+k] * matrix2[k*rows2+j];
      }
      result[i][j] = sum;
      sum = 0;
    }
  }

  return result;
}

void gaussian_elimination(double *a, double *b, double *x, int n)
{
#define A(y, x) (*mat_elem(a, y, x, n))
	int i, col, row, max_row, dia;
	double max, tmp;
 
	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);
 
		for (row = dia + 1; row < n; row++)
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;
 
		swap_row(a, b, dia, max_row, n);
 
		for (row = dia + 1; row < n; row++) {
			tmp = A(row, dia) / A(dia, dia);
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	for (row = n - 1; row >= 0; row--) {
		tmp = b[row];
		for (i = n - 1; i > row; i--)
			tmp -= x[i] * A(row, i);
		x[row] = tmp / A(row, row);
	}
#undef A
}
