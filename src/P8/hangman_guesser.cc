/*
 * 8-2. Expand your hangman program so that the user can choose to be Player 1.
 * The user still selects the number of letters in the word and the number of
 * missed guesses, but the program does the guessing.
 */

#include "hangman.hh"

// Play a game of cheating hangman.
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "USAGE: " << argv[0] << "[number of misses]" << std::endl;
        return 1;
    }

    int max_misses = atoi(argv[1]);
    if (max_misses < 1) {
        std::cout << "Number of misses must be > 0" << std::endl;
        return 1;
    }

    std::map<size_t, std::list<std::string>> possible_words =
        ReadWordsFile(kWordFile);
    GuessWord(possible_words, static_cast<size_t>(max_misses));

    return 0;
}

