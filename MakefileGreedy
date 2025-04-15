# Makefile
CC = gcc

# Always-used optimization flags
OPTFLAGS = -O3 -march=native -fopenmp -fopt-info-all=opt.log

# Target-specific flags
CFLAGS = -c $(OPTFLAGS)
ASMFLAGS = -S -masm=intel -fno-asynchronous-unwind-tables -fno-ident $(OPTFLAGS)

SRC_DIR = src/graph.algorithms
BUILD_DIR = greedy

SRC = $(SRC_DIR)/greedy.c
OBJ = $(BUILD_DIR)/greedy.o
ASM = $(BUILD_DIR)/greedy.s

all: $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

asm: $(ASM)

$(BUILD_DIR)/%.s: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all asm clean
