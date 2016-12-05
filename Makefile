CC=gcc
CFLAGS = -std=c99

test: test.c
	$(CC) $(CFLAGS) $^ -o $@ 
