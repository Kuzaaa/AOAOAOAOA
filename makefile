CC=gcc
CC2=icc

all:
	$(CC) $(FLAGS) driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec
