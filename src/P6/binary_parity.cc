/*
 * 6-2. Consider an array representing a binary string, where every element's data
 * value is 0 or 1. Write a bool function to determine whether the binary string
 * has odd parity (an odd number of 1 bits). Hint: Remember that the recursive
 * function is going to return true (odd) or false (even), not the count of 1 bits.
 * Solve the problem first using iteration, then recursion.
 */

#include <cassert>
#include <iostream>
#include <forward_list>

void TestParityStr();
void TestParityList();
bool HasOddParityIter(const char *bin_str);
bool HasOddParityIter(const std::forward_list<char> &bin_list);
bool HasOddParityRecur(const char *bin_str);
bool HasOddParityRecur(const std::forward_list<char> &bin_list);
bool HasOddParityListRecur(std::forward_list<char>::const_iterator it,
                           std::forward_list<char>::const_iterator end);

// Test parity checks for strings and lists of characters.
int main() {
    TestParityStr();
    TestParityList();

    std::cout << "Parity tests for array and list passed." << std::endl;

    return 0;
}

// Test calculating the parity of a binary string iteratively and recursively.
void TestParityStr() {
    // Test binary string with odd and even parity.
    const char *kOddParityStr = "1101001111";
    const char *kEvenParityStr = "1101001011";

    assert(HasOddParityIter(kOddParityStr));
    assert(!HasOddParityIter(kEvenParityStr));

    assert(HasOddParityRecur(kOddParityStr));
    assert(!HasOddParityRecur(kEvenParityStr));

    // Test both functions for empty strings - they should return false.
    assert(!HasOddParityIter(""));
    assert(!HasOddParityRecur(""));

    // Test both functions for strings with bad chars.
    try {
        HasOddParityIter("1110010121");
    } catch (std::runtime_error &err) {
        std::cout << "Caught runtime_error: " << err.what() << std::endl;
    }

    try {
        HasOddParityRecur("1110010121");
    } catch (std::runtime_error &err) {
        std::cout << "Caught runtime_error: " << err.what() << std::endl;
    }
}

// Test calculating the parity of a binary list iteratively and recursively.
void TestParityList() {
    // Test binary lists with odd and even parity.
    const std::forward_list<char> kOddParityList(
        {'1', '1', '0', '1', '0', '0', '1', '1', '1', '1'});
    const std::forward_list<char> kEvenParityList(
        {'1', '1', '0', '1', '0', '0', '1', '0', '1', '1'});

    assert(HasOddParityIter(kOddParityList));
    assert(!HasOddParityIter(kEvenParityList));

    assert(HasOddParityRecur(kOddParityList));
    assert(!HasOddParityRecur(kEvenParityList));

    // Test both functions for empty strings - they should return false.
    const std::forward_list<char> kEmptyList;
    assert(!HasOddParityIter(kEmptyList));
    assert(!HasOddParityRecur(kEmptyList));

    // Test both functions for lists with bad chars.
    const std::forward_list<char> kBadList(
        {'1', '1', '0', '1', '0', '0', '1', '2', '1', '1'});

    try {
        HasOddParityIter(kBadList);
    } catch (std::runtime_error &err) {
        std::cout << "Caught runtime_error: " << err.what() << std::endl;
    }

    try {
        HasOddParityRecur(kBadList);
    } catch (std::runtime_error &err) {
        std::cout << "Caught runtime_error: " << err.what() << std::endl;
    }
}

// Calculate the parity of a binary string iteratively.
bool HasOddParityIter(const char *bin_str) {
    bool odd_parity = false;

    for (const char *ptr = bin_str; *ptr != '\0'; ++ptr) {
        switch (*ptr) {
            case '0':
                break;

            case '1':
                odd_parity = !odd_parity;
                break;

            default:
                throw std::runtime_error(
                    "Only expect 0s or 1s in binary string.");
        }
    }

    return odd_parity;
}

// Calculate if a list of binary chars has odd parity iteratively.
bool HasOddParityIter(const std::forward_list<char> &bin_list) {
    bool odd_parity = false;

    for (auto it = bin_list.begin(); it != bin_list.end(); ++it) {
        switch (*it) {
            case '0':
                break;

            case '1':
                odd_parity = !odd_parity;
                break;

            default:
                throw std::runtime_error(
                    "Only expect 0s or 1s in binary string.");
        }
    }

    return odd_parity;
}

// Calculate the parity of a binary string recursively.
bool HasOddParityRecur(const char *bin_str) {
    switch (*bin_str) {
        case '\0':
            return false;

        case '0':
            return HasOddParityRecur(bin_str + 1);

        case '1':
            return not HasOddParityRecur(bin_str + 1);

        default:
            throw std::runtime_error(
                "Only expect 0s or 1s in binary string.");
    }
}

// Calculate if a list of binary chars has odd parity recursively.
bool HasOddParityRecur(const std::forward_list<char> &bin_list) {
    return HasOddParityListRecur(bin_list.begin(), bin_list.end());
}

bool HasOddParityListRecur(std::forward_list<char>::const_iterator it,
                           std::forward_list<char>::const_iterator end) {
    if (it == end) {
        return false;
    }

    switch (*it) {
        case '0':
            return HasOddParityListRecur(++it, end);

        case '1':
            return not HasOddParityListRecur(++it, end);

        default:
            throw std::runtime_error(
                "Only expect 0s or 1s in binary string.");
    }
}

