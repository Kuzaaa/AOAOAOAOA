CC=gcc
CFLAGS=-g3 -fopenmp

baseline:
	$(CC) -DBASELINE=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

tab_1d:
	$(CC) -DTAB1D=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

independant:
	$(CC) -DINDEPENDANT=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

independant_split:
	$(CC) -DINDEPENDANT_SPLIT=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

block_cache:
	$(CC) -DBLOCK_CACHE=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

block_cache_mod:
	$(CC) -DBLOCK_CACHE_MOD=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

independant_parallel:
	$(CC) -DINDEPENDANT_PARALLEL=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

independant_split_parallel:
	$(CC) -DINDEPENDANT_SPLIT_PARALLEL=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

block_cache_parallel:
	$(CC) -DBLOCKPARALLEL=1 $(CFLAGS) $(OFLAGS) -$(FLAG) driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec *.gcda *.dyn *.dpi *.lock
