# Makefile
CC = gcc
CFLAGS = -g
LDFLAGS = 
DEPS = mini_lib.h
OBJ = mini_memory.o mini_string.o mini_io.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean :
		rm -f $(OBJ) main