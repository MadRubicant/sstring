CC=gcc
CFLAGS = -std=c99



sstring.o: sstring.c
	$(CC) $(CFLAGS) $^ -c -o $@

test: test.c sstring.o
	$(CC) $(CFLAGS) $^ -o $@ 

clean:
	rm test

lib: sstring.o
	ar $^ libsstring.a
