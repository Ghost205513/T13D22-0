CC=gcc

CFLAGS=-Wall -Werror -Wextra -std=c11

cipher : cipher.o
	$(CC) cipher.o -o ./../build/cipher -lm
	rm -f *.o

cipher.o : cipher.c
	$(CC) $(CFLAGS) -c cipher.c -o cipher.o

clean :
	rm -f ./../build/*