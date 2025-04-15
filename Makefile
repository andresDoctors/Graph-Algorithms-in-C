# Makefile

CC = gcc
CFLAGS = -O3 -march=native -fopenmp
SRC = src/greedy.c src/graph_io.c src/graph.c src/main.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
