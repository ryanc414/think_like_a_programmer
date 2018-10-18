/* P2.5 Calculate the check sum for and validate the check sum of 13-digit
 * ISBN numbers. The steps to calculate ISBN checksums are:
 *
 * 1. Take the first 12 digits of the 13-digit ISBN
 * 2. Multiply the second, fourth, etc. digits with by 3.
 * 3. Add all of the 12 answers.
 * 4. Do a modulo 10 division on the result from step 3.
 * 5. If the remainder is 0, the check digit is 0. Else the check digit is 10
 *    minus the remainder.
 */
#include <iostream>
#include <sstream>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;

#define NUM_DIGITS 13
#define MULTIPLIER 3

int calculate_checksum();
inline int digit_value(char digit);
int checksum_from_digit_sum(long sum);

// Calculate the cheksum, reading the first 12 digits from stdin.
int calculate_checksum()
{
    long sum = 0;
    char digit;

    for (int ii = 0; ii < (NUM_DIGITS - 1); ii++) {
        cin >> digit;

        // Skip past hyphens.
        if (digit == '-') {
            ii--;
            continue;
        }

        // For the first, third etc. digits just add the digit's value to the
        // sum. For the second, fourth etc. digits multiply the digit's value
        // by three.
        if (ii % 2 == 0) {
            sum += digit_value(digit);
        } else {
            sum += digit_value(digit) * MULTIPLIER;
        }
    }

    return checksum_from_digit_sum(sum);
}

// Convert a digit character to its integral value.
inline int digit_value(char digit)
{
    std::ostringstream string_stream;

    if (digit < '0' || digit > '9') {
        string_stream << "Invalid digit: \"" << digit << "\"" << endl;
        throw invalid_argument(string_stream.str());
    }

    return digit - '0';
}

// Given the digit sum, calculate the checksum digit.
int checksum_from_digit_sum(long sum)
{
    int remainder = sum % 10;

    if (remainder == 0) {
        return remainder;
    } else {
        return 10 - remainder;
    }
}

int main()
{
    int checksum;

    cout << "Please enter the first 12 digits of an ISBN:" <<  endl;

    try {
        checksum = calculate_checksum();
    } catch (const std::exception& err) {
        cout << err.what() << endl;
        return -1;
    }

    cout << "Checksum = " << checksum << endl;

    return 0;
}

