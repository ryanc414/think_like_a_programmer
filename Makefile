.PHONY: all, clean

CC=g++
CFLAGS=-Wall -Werror

all: bin/p2_hashes bin/p2_isbn bin/p2_binary

clean:
	rm -rf bin/*

bin/%: src/%.cc
	$(CC) $(CFLAGS) $< -o $@

