/*
 * Change the implementation of our strings such that location[0] in the array
 * stores the size of the array (and therefore location[1] stores the first actual
 * character in the string), rather than using a null-character terminator.
 * Implement each of the three functions, Append, Concatenate, and charactertAt,
 * taking advantage of the stored size information whenever possible. Because
 * we'll no longer be using the null-termination convention expected by the
 * standard output stream, you'll need to write your own output function that
 * loops through its string parameter, displaying the characters.
 */
#include <cstring>
#include <climits>
#include <iostream>

// String implementation that stores the length of the string in the first
// element of an array and the rest of string follows in the array. This is
// not a very practically useful string since the length is limited to
// CHAR_MAX (127) but it shows an example of an alternate string
// implementation compared to standard NULL-terminated strings.
//
// The implementation of CharacterAt is fast. Append and Concatenate will
// always re-allocate the underlying buffer so are relatively inefficient.
class SizedString {
  public:
    SizedString(const char *str) {
        // Get the length of the input string. Since we store the length as
        // the first element in a char array we cannot store strings that
        // are longer than CHAR_MAX.
        int len = strlen(str);
        if (len > CHAR_MAX) {
            throw std::out_of_range("String is too long.");
        }

        // Allocate and fill the array.
        arr_ = new char[len + 1];
        arr_[0] = len;
        memcpy(arr_ + 1, str, len);
    }

    // Build an empty string.
    SizedString() {
        arr_ = new char;
        *arr_ = 0;
    }

    // Delete the allocated character buffer on destruction.
    ~SizedString() {
        delete[] arr_;
    }

    // Get the string's length.
    int GetLen() const {
        return arr_[0];
    }

    // Get a pointer to the start of the string's characters. This buffer is
    // not NULL-terminated so the length will also be required.
    //
    // NULL is returned for an empty string.
    const char *GetChars() const {
        if (GetLen() > 0) {
            return arr_ + 1;
        } else {
            return NULL;
        }
    }

    // Append a character to the end of this string.
    void Append(char Append_char) {
        // Allocate a new buffer one char bigger than the last.
        int old_len = GetLen();
        char *new_arr = new char[old_len + 2];
        int new_len = old_len + 1;
        if (new_len > CHAR_MAX) {
            throw std::out_of_range("Cannot append another char.");
        }

        // Fill up the new array with the incremented length, the old string
        // and the Appended char.
        new_arr[0] = old_len + 1;
        memcpy(new_arr + 1, arr_ + 1, old_len);
        new_arr[old_len + 1] = Append_char;

        // Finally, delete the old array and assign the new one.
        delete[] arr_;
        arr_ = new_arr;
    }

    // Concatenate another string onto this one.
    void Concatenate(const SizedString &other) {
        // Allocate a new buffer to hold the Concatenated string.
        int old_len = GetLen();
        int new_len = old_len  + other.GetLen();
        if (new_len > CHAR_MAX) {
            throw std::out_of_range("Cannot concatenate the other string.");
        }

        char *new_arr = new char[new_len + 1];

        // Fill up the new array with the new length, the old string and the
        // Concatenated string.
        new_arr[0] = new_len;
        memcpy(new_arr + 1, arr_ + 1, old_len);
        memcpy(new_arr + 1 + old_len, other.GetChars(), other.GetLen());

        // Finally, delete the old array and assign the new one.
        delete[] arr_;
        arr_ = new_arr;
    }

    char CharacterAt(int index) const {
        if (index < 0 || index >= GetLen()) {
            throw std::out_of_range("Invalid index.");
        }
        return GetChars()[index];
    }

  private:
    // The underlying buffer which stores all string data. The first element
    // of the array is the string's length and chars follow in the rest of
    // the array, with no NULL terminator.
    char *arr_;
};

std::ostream& operator<<(std::ostream &strm, SizedString const &str);

// Test the SizedString methods Append, Concatenate and CharacterAt.
int main() {
    // Allocate an empty string and concat some chars.
    SizedString empty_str;
    std::cout << "empty_str is: " << empty_str << std::endl;
    empty_str.Concatenate("Not empty any more!");
    std::cout << "empty_str is now: " << empty_str << std::endl;

    // Allocate a start string.
    SizedString start_str{"This is my start string."};
    std::cout << "start_str = " << start_str << std::endl;

    // Append a couple of chars.
    start_str.Append(' ');
    start_str.Append('A');
    std::cout << "after Append: start_str = " << start_str << std::endl;

    // Concatenate another string.
    start_str.Concatenate("nother string has been Concatenated.");
    std::cout << "after concat: start_str = " << start_str << std::endl;

    // Print the 11th char using CharacterAt. Printing the 999th char fails
    // with an out_of_range error.
    std::cout << "11th char = " << start_str.CharacterAt(11) << std::endl;
    bool caught = false;
    try {
        start_str.CharacterAt(999);
    } catch (std::out_of_range) {
        std::cout << "Caught out_of_range getting 999th char." << std::endl;
        caught = true;
    }

    if (!caught) {
        throw std::runtime_error("No out_of_range thrown.");
    }

    // Try looping and appending chars continuously. Eventually an
    // out_of_range will be thrown (it shouldn't take long).
    int i = 0;
    try {
        for (i = 0; ; ++i) {
            start_str.Append('a');
        }
    } catch (std::out_of_range) {
        std::cout << "Caught out_of_range on " << i << "th Append."
                  << std::endl;
    }

    // Concatenating an empty string at this point should be a valid no-op.
    start_str.Concatenate("");

    // Finally, try concatenating another string. Since we previously tried
    // to append the max number of chars any non-empty string should fail.
    caught = false;
    try {
        start_str.Concatenate("more");
    } catch (std::out_of_range) {
        std::cout << "Caught out_of_range on concat." << std::endl;
        caught = true;
    }

    if (!caught) {
        throw std::runtime_error("No out_of_range thrown.");
    }

    return 0;
}

// Output stream printing for SizedString.
std::ostream& operator<<(std::ostream &strm, SizedString const &str) {
    int len = str.GetLen();
    const char *buf = str.GetChars();
    for (int i = 0; i < len; ++i) {
        strm << buf[i];
    }

    return strm;
}

