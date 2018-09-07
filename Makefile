bin/main: src/main.c
	$(CC) -o bin/main src/main.c

clean:
	rm -f bin/main

.PHONY: clean
