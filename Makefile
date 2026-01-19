# Makefile for compiling C code using the Clang compiler

CC = clang

CCFLAGS = -Wall -Wextra -Wpedantic -lncurses -lform -lmenu

SRC = src/main.c src/util.c

PROGRAM = medqueue

$(PROGRAM): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

dev:
	$(CC) $(CCFLAGS) dev.c -o dev && ./dev