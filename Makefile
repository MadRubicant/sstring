CC=gcc
CFLAGS = -std=c99 -Wall

INC=include
SRC=src

SOURCES= $(FILES:%.c=$(SRC)/%.c)


bin/sstring.o: src/sstring.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -c -I$(INC) -o $@

test: bin/sstring.o src/test.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -I$(INC) -o bin/$@ 

clean:
	@rm -r bin/

in/%.o: src/%.c 
	$(mkdir -p bin)
	$(CC) $(CFLAGS) $< -o $@

lib: bin/sstring.o
	@mkdir -p bin
	ar rcs bin/libsstring.a bin/sstring.o
