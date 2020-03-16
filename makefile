CC=gcc

all:
	$(CC) $(FLAGS) driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec
