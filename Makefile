.PHONY: all, clean, P2, P3


CC=g++
CFLAGS=-Wall -Werror -g -Og

all: bin/P2 bin/P3 bin/P4 bin/P5

bin/P2: bin/P2/binary bin/P2/hashes bin/P2/isbn bin/P2/words

bin/P3: bin/P3/agents bin/P3/cipher bin/P3/is_sorted bin/P3/mode \
		bin/P3/students

bin/P4: bin/P4/substring bin/P4/size_strings bin/P4/student_collection \
		bin/P4/list_strings bin/P4/list_ints

bin/P5: bin/P5/automobile bin/P5/varstrings

clean:
	rm -rf bin/P*/*

bin/P2/%: src/P2/%.cc
	$(CC) $(CFLAGS) $< -o $@

bin/P3/%: src/P3/%.cc
	$(CC) $(CFLAGS) $< -o $@

bin/P4/%: src/P4/%.cc
	$(CC) $(CFLAGS) $< -o $@

bin/P5/%: src/P5/%.cc
	$(CC) $(CFLAGS) $< -o $@

