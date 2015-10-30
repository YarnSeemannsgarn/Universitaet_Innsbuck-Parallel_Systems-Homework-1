#ifndef COMMON_H
#define COMMON_H

#define RANGE_MAX 10000
#define MEMORY_MESSAGE "Not enough memory. Choose a smaller problem size!\n"

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

#endif
