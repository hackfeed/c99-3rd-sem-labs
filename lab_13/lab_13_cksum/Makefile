CC = gcc
CFLAGS = -std=c99 -Wall -Werror -I.

OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

static_compose: libcksum.a test_static
dynamic_compose: libcksum.so test_dynamic
dynamic_load: libcksum.so test_dl
python_load: libcksum.so

test_dl: libcksum.so
	ldconfig -v -n .
	ln -sf $^.1 $^
	$(CC) -o testdl.exe testdl.o -ldl

test_dynamic: libcksum.so
	$(CC) -o test.exe test.o -L. -lcksum

test_static: libcksum.a
	$(CC) -o test.exe test.o -L. -lcksum

libcksum.so: $(OBJ)
	$(CC) -fpic -c cksum.c
	ld -shared -soname $@.1 -o $@.1.0 -lc cksum.o
	ldconfig -v -n .
	ln -sf $@.1 $@

libcksum.a: $(OBJ)
	ar cr $@ cksum.o

run_compose:
	./test.exe

run_dynamic_load:
	./testdl.exe

run_python_load:
	python test.py

clean:
	rm -f *.o *.exe *.so* *.a
