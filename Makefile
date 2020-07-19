SRC_LIST = ./main.c $(wildcard */*.c)
OBJ_LIST = $(SRC_LIST:.c=.o)

CC = gcc
CFLAGS = -std=c99 -g -O0 -Wall -Wno-parentheses -Wno-switch-enum -Wno-unused-value
LDFLAGS += -lm

sudoku: $(OBJ_LIST)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_LIST) sudoku