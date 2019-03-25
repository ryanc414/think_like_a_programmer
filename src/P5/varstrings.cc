/*
 * 5-3. Take the variable-length string functions from Chapter 4 (append, concatenate,
 * and characterAt) and use them to create a class for variable-length strings,
 * making sure to implement all necessary constructors, a destructor, and an
 * overloaded assignment operator
 *
 * 5-4. For the variable-length string class of the previous exercise, replace the
 * characterAt method with an overloaded [] operator. For example, if myString
 * is an object of our class, then myString[1] should return the same result as
 * myString.characterAt(1).
 *
 * 5-5. For the variable-length string class of the previous exercises, add a remove
 * method that takes a starting position and a number of characters and removes
 * that many characters from the middle of the string. So myString.remove(5,3)
 * would remove three characters starting at the fifth position. Make sure your
 * method behaves when the value of either of the parameters is invalid.
 *
 * 5-6. Review your variable-length string class for possible refactoring. For example,
 * is there any common functionality that can be separated into a private
 * support method?
 */

#include <cstring>
#include <iostream>

// Wrapper for a variable-length string - basically a home-made version of
// std::string.
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
    char operator[](size_t index) const;

    // Other public methods.
    void Append(char next_char);
    void Concatenate(const String &other);
    void Remove(size_t start, size_t len);

    // Output stream formatter.
    friend std::ostream & operator<<(std::ostream &strm, const String &str);

  private:
    // Pointer to C string.
    char *str_;

    // Length of string. Stored for efficiency to avoid multiple calls to
    // strlen().
    size_t len_;

    // Helper methods to allocate a copy of a C string.
    void CopyStr(const char *str);
    void CopyStr(const char *str, size_t len);

    // Helper method to re-allocate to a new size.
    void Realloc(size_t new_len);
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

    // Test operator[].
    std::cout << "str_e[5] = " << str_e[5] << std::endl;
    try {
        str_e[9999];
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    // Test the Remove method, including with a couple of bad parameters.
    str_e.Remove(5, 3);
    std::cout << "After remove, str_e = " << str_e << std::endl;

    try {
        str_e.Remove(9999, 2);
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    try {
        str_e.Remove(2, 9999);
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    return 0;
}

// Construct from a C string - copies the string contents into this String.
String::String(const char *str) : str_(nullptr) {
    CopyStr(str);
}

// Copy construct one String from another.
String::String(const String &other) : str_(nullptr) {
    CopyStr(other.str_, other.len_);
}

// Move construct one String to another.
String::String(String &&other) noexcept : str_(other.str_), len_(other.len_) {
    other.str_ = nullptr;
    other.len_ = 0;
}

// String destructor.
String::~String() {
    delete[] str_;
}

// Copy-assign one String to another.
String & String::operator=(const String &other) {
    if (this != &other) {
        CopyStr(other.str_, other.len_);
    }

    return *this;
}

// Move-assign one String to another.
String & String::operator=(String &&other) noexcept {
    str_ = other.str_;
    other.str_ = nullptr;
    other.len_ = 0;
    return *this;
}

// Append another char to this String.
void String::Append(char next_char) {
    // Reallocate the string buffer to make room for the extra char.
    size_t new_len = len_ + 1;
    Realloc(new_len);

    // Append the extra char.
    str_[new_len - 1] = next_char;
}

// Concatenate another String onto the end of this one.
void String::Concatenate(const String &other) {
    // Reallocate the string buffer to make room for the concatenated string.
    size_t old_len = len_;
    size_t new_len = old_len + other.len_;
    Realloc(new_len);

    // Copy in the extra string.
    strcpy(str_ + old_len, other.str_);
}

// Removes a specified number of characters from the string.
void String::Remove(size_t start, size_t remove_len) {
    if (start >= len_ || start + remove_len >= len_) {
        throw std::out_of_range("Invalid remove parameters.");
    }

    // First make a copy of the original string.
    char *orig_str = new char[len_ + 1];
    strcpy(orig_str, str_);

    // Realloc our string to the shorter length. This will chop off some chars
    // from the end - which is why we first made a copy!
    size_t new_len = len_ - remove_len;
    Realloc(new_len);

    // Finally, copy the chars after the end of the removal point from the
    // original string into the realloc'd one.
    strcpy(str_ + start, orig_str + start + remove_len);

    // Free the temporary string.
    delete[] orig_str;
}

// Output the String to a stream.
std::ostream & operator<<(std::ostream &strm, const String &str) {
    strm << str.str_;
    return strm;
}

// Return the character at a specific index. Perform bounds checking.
char String::operator[](size_t index) const {
    if (index >= len_) {
        throw std::out_of_range("Bad index.");
    }
    return str_[index];
}

// Allocate a copy of a C string.
void String::CopyStr(const char *str) {
    size_t len = strlen(str);
    CopyStr(str, len);
}

// Allocate a copy of a C string, whose length is already known.
void String::CopyStr(const char *str, size_t len) {
    if (str_ != nullptr) {
        delete[] str_;
    }

    len_ = len;
    str_ = new char[len_ + 1];
    strcpy(str_, str);
}

// Helper function to re-allocate the string to a new size.
void String::Realloc(size_t new_len) {
    // Allocate a new string and copy the old one in. Use strncpy in case the
    // new length is less than the old length (i.e. the string is being
    // made smaller).
    char *new_str = new char[new_len + 1];
    strncpy(new_str, str_, new_len);
    new_str[new_len] = '\0';

    // Free the old string and re-assign the pointer.
    delete[] str_;
    str_ = new_str;
    len_ = new_len;
}

