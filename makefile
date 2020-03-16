CC=gcc
CFLAGS=-O2

all:
	$(CC) $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec