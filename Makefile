.PHONY: all, clean

CC=g++
CFLAGS=-Wall -Werror -g -Og

all: bin/p2_hashes bin/p2_isbn bin/p2_binary bin/p2_words bin/p3_sort \
	 bin/p3_agents bin/p3_is_sorted bin/p3_cipher bin/p3_mode

clean:
	rm -rf bin/*

bin/%: src/%.cc
	$(CC) $(CFLAGS) $< -o $@

