bin/histogram: src/main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bin/*

.PHONY: clean
