/* 2-9. Write a program that reads a line of text, counting the number of
 * words, identifying the length of the longest word, the greatest number of
 * vowels in a word, and/or any other statistics you can think of. */

#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline;

int count_words(string line);
int longest_word(string line);
inline bool is_letter(char c);


int main()
{
    string line;
    int word_count;
    int longest_word_len;

    cout << "Enter a line:" << endl << "> ";
    getline(cin, line);
    cout << "Line read as: \"" << line << "\"" << endl;

    word_count = count_words(line);
    longest_word_len = longest_word(line);

    cout << "Word count: " << word_count << endl;
    cout << "Longest word length: " << longest_word_len << endl;

    return 0;
}

// Count the number of words in a string. Words are consecutive blocks of
// letters.
int count_words(string line)
{
    int count = 0;
    bool in_word = false;

    for (char &c : line) {
        if (is_letter(c)) {
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
int longest_word(string line)
{
    int longest_length = 0;
    int curr_length = 0;

    for (char &c : line) {
        if (is_letter(c)) {
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
inline bool is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

