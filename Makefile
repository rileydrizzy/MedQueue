# Makefile for compiling C code using the Clang compiler

CC = clang

CCFLAGS = -Wall -Wextra -Wpedantic -lncurses

SRC = src/main.c src/util.c

PROGRAM = medqueue

$(PROGRAM): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

debug:
	$(CC) $(CCFLAGS) -g $(SRC) -o $(PROGRAM)
	gdb ./$(PROGRAM)