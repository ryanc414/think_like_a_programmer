/* 2-9. Write a program that reads a line of text, counting the number of
 * words, identifying the length of the longest word, the greatest number of
 * vowels in a word, and/or any other statistics you can think of. */

#include <string>
#include <iostream>

int CountWords(std::string line);
int LongestWord(std::string line);
inline bool IsLetter(char c);

// Read a line from stdin and print the word count and longest word length.
int main() {
    std::string line;

    std::cout << "Enter a line:" << std::endl << "> ";
    std::getline(std::cin, line);
    std::cout << "Line read as: \"" << line << "\"" << std::endl;

    int word_count = CountWords(line);
    int LongestWord_len = LongestWord(line);

    std::cout << "Word count: " << word_count << std::endl;
    std::cout << "Longest word length: " << LongestWord_len << std::endl;

    return 0;
}

// Count the number of words in a string. Words are consecutive blocks of
// letters.
int CountWords(std::string line) {
    int count = 0;
    bool in_word = false;

    for (char &c : line) {
        if (IsLetter(c)) {
            in_word = true;
        } else if (in_word) {
            count++;
            in_word = false;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}

// Return the length of the longest word within a string.
int LongestWord(std::string line) {
    int longest_length = 0;
    int curr_length = 0;

    for (char &c : line) {
        if (IsLetter(c)) {
            curr_length++;
        } else {
            curr_length = 0;
        }

        if (curr_length > longest_length) {
            longest_length = curr_length;
        }
    }

    return longest_length;
}

// Check if a character is a letter or not.
inline bool IsLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

