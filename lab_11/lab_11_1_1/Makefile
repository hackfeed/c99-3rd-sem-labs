CC = gcc
CFLAGS = -std=c99 -w -pedantic -I. -g3

OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

test.exe: $(OBJ)
	$(CC) -o $@ $(OBJ)

run_unittests:
	./test.exe

clean:
	rm -f *.o *.exe vgcore*
