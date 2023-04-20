CC      = gcc
CFLAGS  = -c -O2 -Wall
LDFLAGS =

all: main

main: lib_ppm.o main.o
	$(CC) $(LDFLAGS) lib_ppm.o main.o -o main

lib_ppm.o: lib_ppm.c
	$(CC) $(CFLAGS) -c lib_ppm.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	-rm -f *.o *~ zoom main lena_copy.ppm test.ppm
