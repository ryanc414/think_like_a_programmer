/*
 * 8-1. Write a complete implementation for the cheating hangman problem that's
 * better than mine.
 *
 * See hangman_impl.cc for the core implemetation. This file merely provides
 * the main entry point and parses command-line arguments..
 */

#include "hangman.hh"

// Play a game of cheating hangman.
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "USAGE: "
                  << argv[0]
                  << " [word length] [number of guesses]"
                  << std::endl;
        return 1;
    }

    int word_length = atoi(argv[1]);
    if (word_length < 1) {
        std::cout << "Word length must be > 0." << std::endl;
        return 1;
    }

    int num_guesses = atoi(argv[2]);
    if (num_guesses < 1) {
        std::cout << "Number of guesses must be > 0." << std::endl;
        return 1;
    }

    std::map<size_t, std::list<std::string>> all_words =
        ReadWordsFile(kWordFile);

    if (!all_words.count(static_cast<size_t>(word_length))) {
        std::cout << "Invalid word length - no matching words found."
                  << std::endl;
        return 1;
    }

    std::list<std::string> game_words = all_words[word_length];

    PlayHangman(game_words,
                static_cast<size_t>(word_length),
                static_cast<size_t>(num_guesses));

    return 0;
}

