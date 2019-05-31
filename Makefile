.PHONY: all, clean, P2, P3


CC=g++
CFLAGS=-Wall -Werror -g -Og --std=c++17 -Isrc/common

all: bin/P2 bin/P3 bin/P4 bin/P5 bin/P6 bin/P7 bin/P8

bin/P2: bin/P2/binary bin/P2/hashes bin/P2/isbn bin/P2/words

bin/P3: bin/P3/agents bin/P3/cipher bin/P3/is_sorted bin/P3/mode \
		bin/P3/students

bin/P4: bin/P4/substring bin/P4/size_strings bin/P4/student_collection \
		bin/P4/list_strings bin/P4/list_ints

bin/P5: bin/P5/automobile bin/P5/varstrings

bin/P6: bin/P6/sum_positives bin/P6/binary_parity bin/P6/count_targets \
        bin/P6/luhn_recur bin/P6/reverse_list bin/P6/trees

bin/P7: bin/P7/student_collection bin/P7/student_array_search \
        bin/P7/augmented_student bin/P7/boost_tree

bin/P8: bin/P8/cheating_hangman bin/P8/hangman_ut bin/P8/test_hangman

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

bin/P6/%: src/P6/%.cc
	$(CC) $(CFLAGS) $< -o $@

bin/P7/%: src/P7/%.cc
	$(CC) $(CFLAGS) $< -o $@

bin/P8/cheating_hangman: src/P8/hangman_main.cc src/P8/hangman.hh src/P8/hangman_impl.cc
	$(CC) $(CFLAGS) src/P8/hangman_main.cc src/P8/hangman_impl.cc -o $@

bin/P8/hangman_ut: src/P8/hangman_ut.cc src/P8/hangman.hh src/P8/hangman_impl.cc
	$(CC) $(CFLAGS) src/P8/hangman_ut.cc src/P8/hangman_impl.cc -o $@

bin/P8/test_hangman: src/P8/test_hangman.py
	cp $< $@

