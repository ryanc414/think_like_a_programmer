/*
 * 6-2. Consider an array representing a binary string, where every element's data
 * value is 0 or 1. Write a bool function to determine whether the binary string
 * has odd parity (an odd number of 1 bits). Hint: Remember that the recursive
 * function is going to return true (odd) or false (even), not the count of 1 bits.
 * Solve the problem first using iteration, then recursion.
 */

#include <cassert>
#include <iostream>

bool HasOddParityIter(const char *bin_str, size_t size);
bool HasOddParityRecur(const char *bin_str, size_t size);

// Test calculating the parity of a binary string iteratively and recursively.
int main() {
    constexpr size_t str_size = 10;
    const char bin_str[str_size] = {1, 1, 0, 1, 0, 0, 1, 1, 1, 1};

    const bool iter_parity = HasOddParityIter(bin_str, str_size);
    std::cout << "Iteratively: odd parity? " << iter_parity << std::endl;
    assert(iter_parity);

    const bool recur_parity = HasOddParityRecur(bin_str, str_size);
    std::cout << "Recursively: odd parity? " << recur_parity << std::endl;
    assert(recur_parity);

    // Test both functions for 0-sized arrays - they should return false.
    assert(!HasOddParityIter(nullptr, 0));
    assert(!HasOddParityRecur(nullptr, 0));

    return 0;
}

// Calculate the parity of a binary string iteratively.
bool HasOddParityIter(const char *bin_str, size_t size) {
    bool odd_parity = false;

    for (size_t i = 0; i < size; ++i) {
        switch (bin_str[i]) {
            case 0:
                break;

            case 1:
                odd_parity = not odd_parity;
                break;

            default:
                throw std::runtime_error(
                    "Only expect 0s or 1s in binary string.");
        }
    }

    return odd_parity;
}

// Calculate the parity of a binary string recursively.
bool HasOddParityRecur(const char *bin_str, size_t size) {
    if (size == 0) {
        return false;
    }

    switch (*bin_str) {
        case 0:
            return HasOddParityRecur(bin_str + 1, size - 1);

        case 1:
            return not HasOddParityRecur(bin_str + 1, size - 1);

        default:
            throw std::runtime_error(
                "Only expect 0s or 1s in binary string.");
    }
}

