CC = gcc
CFLAGS = -std=c99 -Wall -Werror -I. -g

FUNC_C = src/*.c
FUNC_O = src/*.o

OBJ = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_MAIN = $(patsubst %.c, %.o, $(wildcard main.c))

build: app.exe

run:
	./app.exe in.txt

clean:
	rm -f $(FUNC_O) *.o *.exe
	
app.exe: $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^