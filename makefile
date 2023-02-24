CC = gcc
CFLAGS = -O3 -march=native -funroll-loops

point_dist: point_dist.c
	$(CC) $(CFLAGS) -o point_dist.exe point_dist.c
