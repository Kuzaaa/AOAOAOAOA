baseline:
	$(CC) $(FLAGS) -DBASELINE=1 driver.c kernel.c rdtsc.c -o exec

tab_1d:
	$(CC) $(FLAGS) -DTAB1D=1 driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec
