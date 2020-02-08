CC = gcc

CFLAGS = -std=c99 -Wall -Werror -pedantic -c

test.exe: func_testing.exe main_unit_testing.o ds_dynamic_array.o func_array.o func_io.o func_math.o \
ds_dynamic_array_test.o func_array_test.o func_io_test.o func_math_test.o
	$(CC) -o $@ main_unit_testing.o ds_dynamic_array.o func_array.o func_io.o func_math.o \
	ds_dynamic_array_test.o func_array_test.o func_io_test.o func_math_test.o -lm 

func_testing.exe: app.exe main_func_testing.o ds_dynamic_array.o func_array.o func_io.o func_math.o
	$(CC) -o $@ main_func_testing.o ds_dynamic_array.o func_array.o func_io.o func_math.o -lm 

app.exe: main.o ds_dynamic_array.o func_array.o func_io.o func_math.o
	$(CC) -o $@ $^ -lm 

main_unit_testing.o: main_unit_testing.c tests/unit_tests/headers/ds_dynamic_array_test.h \
tests/unit_tests/headers/func_array_test.h \
tests/unit_tests/headers/func_math_test.h \
tests/unit_tests/headers/func_io_test.h
	$(CC) $(CFLAGS) $<

main_func_testing.o: main_func_testing.c headers/ds_dynamic_array.h \
headers/func_array.h \
headers/func_io.h \
headers/func_math.h
	$(CC) $(CFLAGS) $<

main.o: main.c headers/ds_dynamic_array.h \
headers/func_array.h \
headers/func_io.h \
headers/func_math.h
	$(CC) $(CFLAGS) $<

ds_dynamic_array_test.o: tests/unit_tests/functions/ds_dynamic_array_test.c \
tests/unit_tests/headers/ds_dynamic_array_test.h
	$(CC) $(CFLAGS) $<
	
func_array_test.o: tests/unit_tests/functions/func_array_test.c \
tests/unit_tests/headers/func_array_test.h
	$(CC) $(CFLAGS) $<

func_math_test.o: tests/unit_tests/functions/func_math_test.c \
tests/unit_tests/headers/func_math_test.h
	$(CC) $(CFLAGS) $<

func_io_test.o: tests/unit_tests/functions/func_io_test.c \
tests/unit_tests/headers/func_io_test.h
	$(CC) $(CFLAGS) $<

ds_dynamic_array.o: functions/ds_dynamic_array.c headers/ds_dynamic_array.h
	$(CC) $(CFLAGS) $<
	
func_array.o: functions/func_array.c headers/func_array.h
	$(CC) $(CFLAGS) $<

func_math.o: functions/func_math.c headers/func_math.h
	$(CC) $(CFLAGS) $<

func_io.o: functions/func_io.c headers/func_io.h
	$(CC) $(CFLAGS) $<

clean:
	rm *.o *.exe tests/func_tests/*.exe

move_func:
	mv func_testing.exe tests/func_tests/
