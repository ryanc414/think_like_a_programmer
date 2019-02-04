.PHONY: all, clean

CC=g++
CFLAGS=-Wall -Werror -g -Og

all: bin/p2_hashes bin/p2_isbn bin/p2_binary bin/p2_words

clean:
	rm -rf bin/*

bin/%: src/%.cc
	$(CC) $(CFLAGS) $< -o $@

