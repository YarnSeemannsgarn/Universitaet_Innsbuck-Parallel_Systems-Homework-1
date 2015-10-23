CC=gcc
CFLAGS=-c -Wall
SOURCES=matrix_multiplication.c common.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=matrix_multiplication 

all: $(EXECUTABLES)

matrix_multiplication: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS) 
