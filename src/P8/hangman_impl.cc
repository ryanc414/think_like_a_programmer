/* hangman_impl.cc: implementation of cheating hangman core logic. */

#include <chrono>
#include <optional>
#include <thread>

#include "hangman.hh"

// Read the words file and organise words by their length.
std::map<size_t, std::list<std::string>> ReadWordsFile(std::string filename) {
    std::list<std::string> words;
    std::ifstream word_file(filename, std::ios::in);

    if (!word_file.is_open()) {
        throw std::invalid_argument("Could not open specified file.");
    }

    std::string curr_word;

    while (word_file >> curr_word) {
        words.push_back(curr_word);
    }

    return SortWordsByLength(words);
}

// Convert a list of words of different lengths size_to a map containing lists for
// each length.
std::map<size_t, std::list<std::string>>
SortWordsByLength(const std::list<std::string> &all_words) {
    std::map<size_t, std::list<std::string>> words_map;

    for (const std::string &word : all_words) {
        words_map[word.length()].push_back(word);
    }

    return words_map;
}

// Play a single game of cheating hangman using the specified list of words
// all of a given length, and with a maximum number of mistakes allowed.
void PlayHangman(std::list<std::string> words,
                 size_t word_length,
                 size_t max_misses) {
    size_t misses = 0;
    size_t discovered_letter_count = 0;
    std::string revealed_word(word_length, kPlaceHolder);
    std::array<bool, kNumLetters> guessed_letters;
    guessed_letters.fill(false);

    while ((discovered_letter_count < word_length) && (misses < max_misses)) {
        std::cout << "Discovered word: " << revealed_word << std::endl;
        char next_letter = PromptNextLetter();
        if (guessed_letters[next_letter - 'a']) {
            std::cout << "You already guessed that letter. Try again."
                      << std::endl;
            continue;
        }

        guessed_letters[next_letter - 'a'] = true;

        auto [words_without_letter, words_with_letter] =
            SplitWordsByLetter(words, next_letter);
        size_t without_letter_count = words_without_letter.size();

        auto [with_letter_count,
              most_frequent_pattern,
              matching_pattern_words] =
            MostFrequentPattern(words_with_letter, next_letter);

        if (without_letter_count > with_letter_count) {
            ++misses;
            words = words_without_letter;
            std::cout << "Bad guess" << std::endl;
        } else {
            words = matching_pattern_words;
            revealed_word = most_frequent_pattern.Reveal(revealed_word);
            discovered_letter_count += most_frequent_pattern.size();
            std::cout << "Correct guess!" << std::endl;
        }

        std::cout << "You have "
                  << max_misses - misses
                  << " guesses remaining."
                  << std::endl;
    }

    if (discovered_letter_count == word_length) {
        std::cout << "Congratulations - you guessed the word!"
                  << std::endl
                  << "Word was: "
                  << revealed_word
                  << std::endl;
    } else {
        std::cout << "Out of guesses..."
                  << std::endl
                  << "I was thinking of: "
                  << RandomChoice(words)
                  << std::endl;
    }
}

// Prompt for the next letter to be input. Loops until a valid lowercase
// letter is entered.
char PromptNextLetter() {
    std::string input;
    std::cout << "Guess a letter:" << std::endl << "> ";
    std::getline(std::cin, input);

    while ((input.size() != 1) || (input[0] < 'a') || (input[0] > 'z')) {
        std::cout << "Bad choice: only lowercase a-z is allowed."
                  << std::endl
                  << "Try again:"
                  << std::endl
                  << "> ";
        if (!std::getline(std::cin, input)) {
            abort();
        }
    }

    return input[0];
}

// Split a list of words into two lists: one that contains a letter and one
// that doesn't.
std::pair<std::list<std::string>, std::list<std::string>>
SplitWordsByLetter(std::list<std::string> words, char next_letter) {
    std::list<std::string> words_with_letter;
    std::list<std::string> words_without_letter;

    for (const std::string &word : words) {
        if (word.find(next_letter) == std::string::npos) {
            words_without_letter.push_back(word);
        } else {
            words_with_letter.push_back(word);
        }
    }

    return std::make_pair(words_without_letter, words_with_letter);
}

// Find the letter pattern that matches the most words. Return the count of the
// most frequent pattern, the pattern itself, and a list of words that match
// the pattern.
std::tuple<size_t, LetterPattern, std::list<std::string>>
MostFrequentPattern(std::list<std::string> words, char letter) {
    size_t max_pattern_count = 0;
    LetterPattern most_frequent_pattern;
    std::list<std::string> most_frequent_matching_words;

    // The algorithm for finding the most frequent pattern is as follows:
    //
    // 1. Pop the first word off the list
    // 2. Find all other words that match that word's pattern for the given
    //    letter. Remove matches from the list as an optimization.
    // 2. If the pattern is the most frequent, update the running value and
    //    its frequency.
    // 3. Repeat until list is empty.
    while (!words.empty()) {
        // Pop off the first word and store its pattern with respect to our
        // letter.
        LetterPattern next_pattern(words.front(), letter);
        assert(next_pattern.size() > 0);
        size_t next_pattern_count = 1;
        std::list<std::string> matching_words({words.front()});
        words.pop_front();

        // Loop through the rest of the list. For every word that matches
        // the current pattern, increase the count and add to the current
        // list of matching words.
        auto it = words.begin();
        while (it != words.end()) {
            if (next_pattern.Matches(*it)) {
                ++next_pattern_count;
                matching_words.push_back(*it);
                it = words.erase(it);
            } else {
                ++it;
            }
        }

        // Update the most frequent pattern and count if necessary.
        if (next_pattern_count > max_pattern_count) {
            max_pattern_count = next_pattern_count;
            most_frequent_pattern = next_pattern;
            most_frequent_matching_words = std::move(matching_words);
        }
    }

    return std::make_tuple(max_pattern_count,
                           most_frequent_pattern,
                           most_frequent_matching_words);
}

// Selects a random value from a list.
template <class T> T RandomChoice(std::list<T> in) {
    std::list<T> out;

    std::sample(in.begin(),
                in.end(),
                std::back_inserter(out),
                1,
                std::mt19937{std::random_device{}()});

    assert(out.size() == 1);

    return out.front();
}

// Constructor for an empty letter pattern.
LetterPattern::LetterPattern() : letter_('\0'), size_(0), pattern_() {};


// Construct a letter pattern for a given word and letter.
LetterPattern::LetterPattern(const std::string &word, char letter) :
    letter_(letter), size_(0), pattern_() {
    for (char c : word) {
        if (c == letter) {
            pattern_.push_back(true);
            ++size_;
        } else {
            pattern_.push_back(false);
        }
    }

    assert(pattern_.size() == word.size());
}

// Return the letter this pattern is for.
char LetterPattern::letter() const {
    return letter_;
}

// Check if a word matches this pattern.
bool LetterPattern::Matches(const std::string &word) const {
    if (word.size() != pattern_.size()) {
        throw std::length_error("Word length does not match pattern");
    }

    // Iterate through the word and pattern at the same time.
    for (size_t i = 0; i < pattern_.size(); ++i) {
        // If this position is part of the pattern, check that the letter
        // matches the word. If not we short-circuit and return false.
        if (pattern_[i] && (word[i] != letter_)) {
            return false;
        } else if (!pattern_[i] && (word[i] == letter_)) {
            return false;
        }
    }

    // If we get to here, then all letters in the word matched the pattern.
    return true;
}

// Return how many letter matches are in this pattern.
size_t LetterPattern::size() const {
    return size_;
}

// Add the letters contained in this pattern to the already revealed string.
std::string LetterPattern::Reveal(std::string already_revealed) {
    if (already_revealed.size() != pattern_.size()) {
        throw std::length_error("Revealed string does not match pattern size");
    }

    for (size_t i = 0; i < pattern_.size(); ++i) {
        if (pattern_[i]) {
            if (already_revealed[i] != kPlaceHolder) {
                throw std::runtime_error(
                    "Character has already been revealed");
            }

            already_revealed[i] = letter_;
        }
    }

    return already_revealed;
}

// Prompt for a word to be entered, then attempt to guess it within the
// specified number of misses.
void GuessWord(const std::map<size_t, std::list<std::string>> &all_words,
               size_t max_misses) {
    std::string chosen_word = PromptForWord(all_words);
    std::list<std::string> possible_words = all_words.at(chosen_word.length());

    size_t misses = 0;
    size_t discovered_letter_count = 0;
    std::string revealed_word(chosen_word.length(), kPlaceHolder);
    std::array<bool, kNumLetters> guessed_letters;
    guessed_letters.fill(false);

    while ((discovered_letter_count < chosen_word.length()) &&
           (misses < max_misses)) {
        std::cout << "Discovered word: " << revealed_word << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        char next_letter = GuessNextLetter(possible_words, guessed_letters);
        std::cout << "Guessing letter: " << next_letter << std::endl;
        assert(!guessed_letters[next_letter - 'a']);
        guessed_letters[next_letter - 'a'] = true;

        std::optional<LetterPattern> match =
            CheckGuess(next_letter, chosen_word);

        if (match) {
            std::cout << "Guess was correct!" << std::endl;
            discovered_letter_count += match->size();
            revealed_word = match->Reveal(revealed_word);
            possible_words = WordsMatchingPattern(possible_words, *match);

        } else {
            std::cout << "Incorrect guess." << std::endl;
            ++misses;
            possible_words = std::get<0>(
                SplitWordsByLetter(possible_words, next_letter));
        }

        std::cout << std::endl;
    }

    if (discovered_letter_count == chosen_word.length()) {
        std::cout << "I guessed your word was " << chosen_word << std::endl;
    } else {
        std::cout << "I couldn't guess your word - only got "
                  << revealed_word
                  << std::endl;
    }

}

// Prompt for a word to be entered. It must be a word we know about.
std::string
PromptForWord(const std::map<size_t, std::list<std::string>> &possible_words) {
    std::string word;
    std::cout << "Enter a word for me to guess: " << std::endl << "> ";

    if (!std::getline(std::cin, word)) {
        abort();
    }

    while (!ValidWord(word, possible_words)) {
        std::cout << "I don't know that word, try another."
                  << std::endl
                  << "> ";
        if (!std::getline(std::cin, word)) {
            abort();
        }
    }

    return word;
}

// Check if a word entered is valid.
bool
ValidWord(std::string chosen_word,
          const std::map<size_t, std::list<std::string>> &possible_words) {
    try {
        for (const std::string &word : possible_words.at(chosen_word.length())) {
            if (word == chosen_word) {
                return true;
            }
        }
    } catch (std::out_of_range) {
        return false;
    }

    return false;
}

// Guess the next letter from the choice of possible words, not repeating any
// letters already guessed.
char GuessNextLetter(const std::list<std::string> &possible_words,
                     std::array<bool, kNumLetters> guessed_letters) {
    std::array<size_t, kNumLetters> letters_freq;
    letters_freq.fill(0);

    for (const std::string &word : possible_words) {
        for (char c : word) {
            ++letters_freq[c - 'a'];
        }
    }

    char most_freq_letter = '\0';
    size_t most_freq_letter_count = 0;

    for (char letter = 'a'; letter <= 'z'; ++letter) {
        size_t count = letters_freq[letter - 'a'];
        if ((count > most_freq_letter_count) &&
            (!guessed_letters[letter - 'a'])) {
            most_freq_letter = letter;
            most_freq_letter_count = count;
        }
    }

    return most_freq_letter;
}

// Check if a guessed letter is within a word - if so return the pattern.
std::optional<LetterPattern>
CheckGuess(char next_letter, const std::string &chosen_word) {
    LetterPattern pattern(chosen_word, next_letter);

    if (pattern.size() > 0) {
        return pattern;
    } else {
        return std::nullopt;
    }
}

// Return all words in the input list that match the given letter pattern.
std::list<std::string>
WordsMatchingPattern(const std::list<std::string> &words,
                     const LetterPattern &pattern) {
    std::list<std::string> matching_words;

    for (const std::string &word : words) {
        if (pattern.Matches(word)) {
            matching_words.push_back(word);
        }
    }

    return matching_words;
}

