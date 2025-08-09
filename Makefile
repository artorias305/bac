CC = gcc
CFLAGS = -g -Wall -Wextra

bac: bac.c bac.h
	$(CC) $(CFLAGS) bac.c -o bac

run:
	$(CC) $(CFLAGS) bac.c -o bac && ./bac

clean:
	rm -f bac
