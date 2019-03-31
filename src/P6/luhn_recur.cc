/*
 * 6-4. Design your own: Find a problem processing a one-dimension array that you
 * have already solved or that is trivial for you at your current skill level, and
 * solve the problem (or solve it again) using recursion.
 *
 * Let's solve the Luhn checksum validation problem with recursion. The algorithm is:
 *
 * Using the original number, double the value of every other digit. Then add the values of the
 * individual digits together (if a doubled value now has two digits, add the digits indi-
 * vidually). The identification number is valid if the sum is divisible by 10.
 */

#include <cassert>
#include <iostream>

bool ValidateLuhn(const char *digits);
int LuhnSum(const char *digits, bool double_next=false);
inline int DigitToInt(char digit);

// Test the Luhn checksum validation function.
int main() {
    const char valid_number[] = "79927398713";
    const char invalid_number[] = "79927398710";

    // Test validating the valid and invalid numbers.
    assert(ValidateLuhn(valid_number));
    assert(!ValidateLuhn(invalid_number));

    // Test validating an empty string.
    assert(ValidateLuhn(""));

    // Test validating a string containing bad characters.
    try {
        ValidateLuhn("1987223h123");
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    std::cout << "All numbers validated correctly." << std::endl;

    return 0;
}

// Validate the Luhn checksum recursively.
bool ValidateLuhn(const char *digits) {
    return LuhnSum(digits) % 10 == 0;
}

// Calculate the Luhn sum for a set of digits: double the value of every other
// digit and sum. If a doubled digit gives a two-digit number they are summed
// individually. The sum is performed recursively.
int LuhnSum(const char *digits, bool double_next) {
    if (*digits == '\0') {
        return 0;
    }

    if (double_next) {
        int doubled_digit = DigitToInt(*digits) * 2;
        if (doubled_digit > 9) {
            assert(doubled_digit < 100);
            int digit_sum = (doubled_digit % 10) + (doubled_digit / 10);
            return digit_sum + LuhnSum(digits + 1, false);
        } else {
            return doubled_digit + LuhnSum(digits + 1, false);
        }
    } else {
        return DigitToInt(*digits) + LuhnSum(digits + 1, true);
    }
}

// Converts a digit character into its integer value e.g. "4" => 4.
inline int DigitToInt(char digit) {
    if ((digit < '0') || digit > '9') {
        throw std::out_of_range("Invalid digit.");
    } else {
        return digit - '0';
    }
}

