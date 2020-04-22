CC=gcc
FLAGS=-O2

baseline:
	$(CC) $(FLAGS) -DBASELINE=1 driver.c kernel.c rdtsc.c -o exec

tab_1d:
	$(CC) $(FLAGS) -DTAB1D=1 driver.c kernel.c rdtsc.c -o exec

independant:
	$(CC) $(FLAGS) -DINDEPENDANT=1 driver.c kernel.c rdtsc.c -o exec

independant_split:
	$(CC) $(FLAGS) -DINDEPENDANT_SPLIT=1 driver.c kernel.c rdtsc.c -o exec

block_cache:
	$(CC) $(FLAGS) -DBLOCK_CACHE=1 driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec
