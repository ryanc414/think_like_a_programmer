/* hangman.hh: header file for cheating hangman game. */
#ifndef HANGMAN_H_
#define HANGMAN_H_

#include <cassert>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

// Constants.
//
// There are 26 letters in the alphabet.
constexpr size_t kNumLetters = 26;

// Placeholder char used for unguessed letters.
constexpr size_t kPlaceHolder = '_';

// The word file is relative to the repo root. Maybe make it a parameter?
const std::string kWordFile = "data/words_alpha.txt";

// Classes
class LetterPattern {
  public:
    // Constructors.
    LetterPattern();
    explicit LetterPattern(const std::string &word, char letter);

    // Attribute getters.
    char letter() const;
    size_t size() const;

    // Other methods.
    bool Matches(const std::string &word) const;
    std::string Reveal(std::string already_revealed);

  private:
    char letter_;
    size_t size_;
    std::vector<bool> pattern_;
};

// Functions.
std::map<size_t, std::list<std::string>> ReadWordsFile(std::string filename);

std::map<size_t, std::list<std::string>>
SortWordsByLength(const std::list<std::string> &words);

void PlayHangman(std::list<std::string> words,
                 size_t words_length,
                 size_t max_misses);

char PromptNextLetter();

std::pair<std::list<std::string>, std::list<std::string>>
SplitWordsByLetter(std::list<std::string> words, char next_letter);

std::tuple<size_t, LetterPattern, std::list<std::string>>
MostFrequentPattern(std::list<std::string> words, char letter);

template <class T> T RandomChoice(std::list<T> in);

void GuessWord(const std::map<size_t, std::list<std::string>> &possible_words,
               size_t max_misses);

std::string
PromptForWord(const std::map<size_t, std::list<std::string>> &possible_words);

bool ValidWord(std::string word,
               const std::map<size_t, std::list<std::string>> &possible_words);

char GuessNextLetter(const std::list<std::string> &possible_words,
                     std::array<bool, kNumLetters> guessed_letters);

std::optional<LetterPattern>
CheckGuess(char next_letter, const std::string &chosen_word);

std::list<std::string>
WordsMatchingPattern(const std::list<std::string> &words,
                     const LetterPattern &pattern);

#endif  // HANGMAN_H_

