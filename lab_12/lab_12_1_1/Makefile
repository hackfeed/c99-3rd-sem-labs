CC = gcc
CFLAGS = -std=c99 -Wall -Werror -I. -g

FUNC_C = src/*.c
FUNC_O = src/*.o

OBJ = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_MAIN = $(patsubst %.c, %.o, $(wildcard main.c))
OBJ_TEST = $(patsubst %.c, %.o, $(wildcard test.c))

test.exe: $(OBJ_TEST) app.exe
	$(CC) -o $@ $<

app.exe: $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^ -lm 

run:
	./app.exe

runvg:
	valgrind --leak-check=yes --track-origins=yes ./app.exe

ftest:
	cp app.exe tests/func_tests/ && chmod u+x \
	tests/func_tests/run_func_tests.sh && \
	cd tests/func_tests/ && ./run_func_tests.sh && \
	rm app.exe

clean:
	rm -f $(FUNC_O) *.o *.exe *.txt vgcore*