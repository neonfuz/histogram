CFLAGS=-ggdb

bin/main: src/main.c
	$(CC) $(CFLAGS) -o bin/main src/main.c

clean:
	rm -f bin/main

.PHONY: clean
