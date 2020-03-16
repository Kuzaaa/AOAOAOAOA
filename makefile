CC=gcc
CC2=icc

all:
	$(CC) $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

O2:
	$(CC) -O2 $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

O3:
	$(CC) -O3 $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

O3native:
	$(CC) -O3 -march=native $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

iccO2:
	$(CC2) -O2 $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

iccO3:
	$(CC2) -O3 $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

iccO3host:
	$(CC2) -O3 -xHost $(CFLAGS) driver.c kernel.c rdtsc.c -o exec

clean:
	rm exec
