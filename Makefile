all: mymalloc.c memgrind.c mymalloc.h
	gcc mymalloc.c -c
	gcc memgrind.c mymalloc.o -o memgrind
clean:
	rm mymalloc.o
	rm memgrind
