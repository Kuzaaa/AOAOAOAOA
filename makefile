CC=gcc
CFLAGS=-O2

all:
	$(CC) $(CFLAGS) Code_source.c -o exec

clean:
	rm exec