CC = gcc
CFLAGS = -O3 -funroll-loops

naive_primes: naive_primes.c
	$(CC) $(CFLAGS) -o naive_primes.exe naive_primes.c
