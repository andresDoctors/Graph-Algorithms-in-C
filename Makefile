# Makefile

COMPILER = gcc
WARNINGS = -Wall -Wextra -std=gnu17 -pedantic
OPTIMIZE = -Og -march=native -fopenmp
OPTIMIZE2 = -flto -funroll-loops 
INFO = -Wdisabled-optimization        \
       -fopt-info-vec=build/vec.txt   \
       -fopt-info-ipa=build/ipa.txt   \
       -fopt-info-loop=build/loop.txt \
       -fopt-info-inline=build/inline.txt
DEBUG = -g
SRC_MODULES = src/graph_io.c src/graph.c src/greedy.c
TST_MODULES = test/random.c test/test.c
BIN_MODULES = build/graph_io.o build/graph.o build/greedy.o build/random.o build/utils.o
TESTS = test/test_graph_io.c test/test_graph.c

tests: test_graph_io test_graph

clean:
	@rm -rf ./build/*

test_graph_io: graph_io.o graph.o greedy.o random.o utils.o
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) $(BIN_MODULES) unity/unity.c test/test_graph_io.c -o build/test_graph_io

test_graph: graph_io.o graph.o greedy.o random.o utils.o
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) $(BIN_MODULES) unity/unity.c test/test_graph.c -o build/test_graph

graph_io.o:
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c src/graph_io.c -o build/graph_io.o

graph.o: graph_io.o
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c src/graph.c -o build/graph.o

greedy.o: graph.o
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c src/greedy.c -o build/greedy.o

random.o:
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c test/random.c -o build/random.o

utils.o:
	$(COMPILER) $(WARNINGS) $(OPTIMIZE) $(DEBUG) -c test/utils.c -o build/utils.o
