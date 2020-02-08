CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

FUNC_C = functions/*.c
FUNC_C_UNITTESTS = tests/unit_tests/functions/*.c
FUNC_O = functions/*.o
FUNC_O_UNITTESTS = tests/unit_tests/functions/*.o

OBJ = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_UNITTESTS = $(patsubst %.c, %.o, $(wildcard $(FUNC_C_UNITTESTS)))
OBJ_MAIN = $(patsubst %.c, %.o, $(wildcard main.c))
OBJ_MAIN_UNITTESTS = $(patsubst %.c, %.o, $(wildcard main_unit_testing.c))

test.exe: func_testing.exe $(OBJ_MAIN_UNITTESTS) $(OBJ_UNITTESTS) $(OBJ)
	$(CC) -o $@ $(OBJ_MAIN_UNITTESTS) $(OBJ_UNITTESTS) $(OBJ) -lm

func_testing.exe: app.exe $(OBJ_MAIN) $(OBJ)
	$(CC) -o $@ $(OBJ_MAIN) $(OBJ) -lm 

app.exe: $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^ -lm 

run_app:
	./app.exe

run_app_valgrind:
	valgrind --leak-check=yes --track-origins=yes ./app.exe

run_unittests:
	./test.exe

run_functests:
	mv func_testing.exe tests/func_tests/ && chmod u+x \
	tests/func_tests/run_func_tests.sh && \
	cd tests/func_tests/ && ./run_func_tests.sh

clean:
	rm $(FUNC_O) $(FUNC_O_UNITTESTS) *.o *.exe tests/func_tests/*.exe

clean_valgrind:
	rm vgcore*