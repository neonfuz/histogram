bin/histogram: src/main.c
	mkdir -p bin/
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bin/*

.PHONY: clean
