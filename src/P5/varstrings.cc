/*
 * 5-3. Take the variable-length string functions from Chapter 4 (append, concatenate,
 * and characterAt) and use them to create a class for variable-length strings,
 * making sure to implement all necessary constructors, a destructor, and an
 * overloaded assignment operator
 */

#include <cstring>
#include <iostream>

class String {
  public:
    // Constructors and destructors.
    String() = default;
    explicit String(const char *str);
    String(const String &other);
    String(String &&other) noexcept;
    ~String();

    // Overloaded operators.
    String & operator=(const String &other);
    String & operator=(String &&other) noexcept;

    // Other public methods.
    void Append(char next_char);
    void Concatenate(const String &other);
    char CharacterAt(int index) const;

    // Output stream formatter.
    friend std::ostream & operator<<(std::ostream &strm, const String &str);

  private:
    // Pointer to C string.
    char *str_;

    // Helper method to allocate a copy of a C string.
    char *CopyStr(const char *str);
};

int main() {
    // Construct from a string literal.
    String str_a("Starting string");
    std::cout << "str_a = " << str_a << std::endl;

    // Append.
    str_a.Append(' ');
    str_a.Append('a');
    std::cout << "After append, str_a = " << str_a << std::endl;

    // Copy construct.
    String str_b(str_a);
    std::cout << "str_b = " << str_b << std::endl;

    // Concatenate.
    str_b.Concatenate(str_a);
    std::cout << "After concat, str_b = " << str_b << std::endl;

    // Copy assign.
    String str_c = str_b;
    std::cout << "str_c = " << str_c << std::endl;

    // Move construct.
    String str_d(std::move(str_a));
    std::cout << "str_d = " << str_d << std::endl;

    // Move assign.
    String str_e = std::move(str_b);
    std::cout << "str_e = " << str_e << std::endl;

    return 0;
}

// Construct from a C string - copies the string contents into this String.
String::String(const char *str) : str_(CopyStr(str)) {}

// Copy construct one String from another.
String::String(const String &other) : str_(CopyStr(other.str_)) {}

// Move construct one String to another.
String::String(String &&other) noexcept : str_(other.str_) {
    other.str_ = nullptr;
}

// String destructor.
String::~String() {
    delete[] str_;
}

// Copy-assign one String to another.
String & String::operator=(const String &other) {
    if (this != &other) {
        delete[] str_;
        str_ = CopyStr(other.str_);
    }

    return *this;
}

// Move-assign one String to another.
String & String::operator=(String &&other) noexcept {
    str_ = other.str_;
    other.str_ = nullptr;
    return *this;
}

// Append another char to this String.
void String::Append(char next_char) {
    // Allocate a new string buffer.
    const int new_len = strlen(str_) + 1;
    char *new_str = new char[new_len + 1];

    // Copy the old string to the new buffer and append the extra char.
    strcpy(new_str, str_);
    new_str[new_len - 1] = next_char;
    new_str[new_len] = '\0';

    // Delete the old string and update the pointer to the new buffer.
    delete[] str_;
    str_ = new_str;
}

void String::Concatenate(const String &other) {
    // Allocate a new string buffer.
    const int old_len = strlen(str_);
    const int new_len = old_len + strlen(other.str_);
    char *new_str = new char[new_len + 1];

    // Copy the old string to the new buffer and concatenate the extra string.
    strcpy(new_str, str_);
    strcpy(new_str + old_len, other.str_);
    new_str[new_len] = '\0';

    // Delete the old string and update the pointer to the new buffer.
    delete[] str_;
    str_ = new_str;
}

// Output the String to a stream.
std::ostream & operator<<(std::ostream &strm, const String &str) {
    strm << str.str_;
    return strm;
}

// Return the character at a specific index.
char String::CharacterAt(int index) const {
    // Calculating strlen() each time would be slow for long strings - could
    // store the length separately for efficiency.
    if (index < 0 || index >= static_cast<int>(strlen(str_))) {
        throw std::out_of_range("Bad index.");
    }
    return str_[index];
}

// Allocate a copy of a C string.
char *String::CopyStr(const char *str) {
    const int len = strlen(str);
    char *copy = new char[len + 1];
    strcpy(copy, str);

    return copy;
}

