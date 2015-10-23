CC=gcc
CFLAGS=-c -Wall
SOURCES=matrix_multiplication.c sieve_of_erastosthenes.c common.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=matrix_multiplication sieve_of_erastosthenes

all: $(EXECUTABLES)

matrix_multiplication: $(OBJECTS)
	$(CC) matrix_multiplication.o common.o -o $@

sieve_of_erastosthenes: $(OBJECTS)
	$(CC) sieve_of_erastosthenes.o -lm -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS) 
