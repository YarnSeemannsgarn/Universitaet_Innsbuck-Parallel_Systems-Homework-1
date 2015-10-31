CC=gcc
CFLAGS=-c -Wall
SOURCES=matrix_multiplication.c gaussian_elimination.c dijkstra.c sieve_of_erastosthenes.c bubble_sort.c bucket_sort.c counting_sort.c insertion_sort.c selection_sort.c quicksort.c common.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=matrix_multiplication gaussian_elimination dijkstra sieve_of_erastosthenes bubble_sort bucket_sort counting_sort insertion_sort selection_sort quicksort

all: $(EXECUTABLES)

matrix_multiplication: $(OBJECTS)
	$(CC) matrix_multiplication.o common.o -o $@

gaussian_elimination: $(OBJECTS)
	$(CC) gaussian_elimination.o common.o -o $@

dijkstra: $(OBJECTS)
	$(CC) dijkstra.o common.o -o $@

sieve_of_erastosthenes: $(OBJECTS)
	$(CC) sieve_of_erastosthenes.o common.o -lm -o $@

bubble_sort: $(OBJECTS)
	$(CC) bubble_sort.o common.o -o $@

bucket_sort: $(OBJECTS)
	$(CC) bucket_sort.o common.o -lm -o $@

counting_sort: $(OBJECTS)
	$(CC) counting_sort.o common.o -o $@

insertion_sort: $(OBJECTS)
	$(CC) insertion_sort.o common.o -o $@

selection_sort: $(OBJECTS)
	$(CC) selection_sort.o common.o -o $@

quicksort: $(OBJECTS)
	$(CC) quicksort.o common.o -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS) 
