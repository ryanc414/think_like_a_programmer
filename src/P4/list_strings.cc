/*
 * 4-6. Let's create an implementation for strings that uses a linked list of characters
 * instead of dynamically allocated arrays. So we'll have a linked list where the
 * data payload is a single char; this will allow strings to grow without having to recreate
 * the entire string. We'll start by implementing the append and characterAt
 * functions.
 *
 * 4-7. Following up on the previous exercise, implement the concatenate function.
 * Note that if we make a call concatenate(s1, s2), where both parameters are
 * pointers to the first nodes of their respective linked lists, the function should
 * create a copy of each of the nodes in s2 and append them to the end of s1.
 * That is, the function should not simply point the next field of the last node in
 * s1's list to the first node of s2's list.
 *
 * 4-8. Add a function to the linked-list string implementation called removeChars to
 * remove a section of characters from a string based on the position and length.
 * For example, removeChars(s1, 5, 3) would remove the three characters starting
 * at the fifth character in the string. Make sure the removed nodes are properly
 * deallocated.
 */

#include <cassert>
#include <cstring>
#include <iostream>
#include <list>
#include <iterator>

// Basic string implementation that uses a std::list to store the characters.
class ListString {
  public:
    // Construct from a string literal.
    explicit ListString(const char *str) {
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
    std::list<char>::const_iterator begin() const {
        return char_list_.begin();
    }

    std::list<char>::const_iterator end() const {
        return char_list_.end();
    }

    void Concatenate(ListString const &other) {
        for (char c : other) {
           char_list_.push_back(c);
        }
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

    ListString *heap_str = new ListString("Concat me");
    list_str.Concatenate(*heap_str);
    delete heap_str;
    heap_str = nullptr;

    std::cout << "After concat: " << list_str << std::endl;

    return 0;
}

// Output stream printing for ListString.
std::ostream& operator<<(std::ostream &strm, ListString const &str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        strm << *it;
    }

    return strm;
}

