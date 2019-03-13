/*
 * Let's create an implementation for strings that uses a linked list of characters
 * instead of dynamically allocated arrays. So we'll have a linked list where the
 * data payload is a single char; this will allow strings to grow without having to recreate
 * the entire string. We'll start by implementing the append and characterAt
 * functions.
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <list>

// Basic string implementation that uses a std::list to store the characters.
class ListString {
  public:
    // Construct from a string literal.
    ListString(const char *str) {
        for (const char *ptr = str; *ptr != '\0'; ++ptr) {
            Append(*ptr);
        }
    }

    // Append a char to the list.
    void Append(char next_char) {
        char_list_.push_back(next_char);
    }

    // Return the character at a specified index. Since lists do not offer
    // fast random access this requires us to traverse the list.
    char CharacterAt(int index) const {
        int i = 0;
        auto it = char_list_.begin();

        while ((i < index) && (it != char_list_.end())) {
            ++it;
            ++i;
        }

        if (it != char_list_.end()) {
            return *it;
        } else {
            throw std::out_of_range("No character at specified index.");
        }
    }

    // Pass through the list's begin() and end() methods to support iteration.
    auto begin() const {
        return char_list_.begin();
    }

    auto end() const {
        return char_list_.end();
    }

  private:
    std::list<char> char_list_;
};

std::ostream& operator<<(std::ostream &strm, ListString const &str);

// Test the ListString methods.
int main() {
    ListString list_str("Starting string");
    std::cout << "list_str = " << list_str << std::endl;
    std::cout << "CharacterAt(3) = " << list_str.CharacterAt(3) << std::endl;
    assert(list_str.CharacterAt(3) == 'r');

    list_str.Append('!');
    std::cout << "CharacterAt(15) = " << list_str.CharacterAt(15) << std::endl;
    assert(list_str.CharacterAt(15) == '!');

    return 0;
}

// Output stream printing for ListString.
std::ostream& operator<<(std::ostream &strm, ListString const &str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        strm << *it;
    }

    return strm;
}

