CC=gcc
CFLAGS=-c -Wall
SOURCES=main.c sequential_algorithms.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS) 
