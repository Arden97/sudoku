SRC=$(wildcard *.c)
OBJ=${SRC:.c=.o}

CC=gcc
CFLAGS=-std=c99 -g -O0 -Wno-parentheses -Wno-switch-enum -Wno-unused-value
CFLAGS+=-Wno-switch
LDFLAGS+=-lm

EXEC=sudoku

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f sudoku $(OBJ)

.PHONY: clean