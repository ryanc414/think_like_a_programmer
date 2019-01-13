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
using std::string;
using std::ostringstream;

#define NUM_DIGITS 12
#define MULTIPLIER 3

int calculate_checksum();
inline int digit_value(char digit);
int checksum_from_digit_sum(long sum);
string normalise_input(string input);
void output_checksum(string input);
void verify_checksum(string input);

// Calculate the cheksum, reading the first 12 digits from stdin.
int calculate_checksum(string input)
{
    long sum = 0;

    for (int ii = 0; ii < NUM_DIGITS; ii++) {
        // For the first, third etc. digits just add the digit's value to the
        // sum. For the second, fourth etc. digits multiply the digit's value
        // by three.
        if (ii % 2 == 0) {
            sum += digit_value(input[ii]);
        } else {
            sum += digit_value(input[ii]) * MULTIPLIER;
        }
    }

    return checksum_from_digit_sum(sum);
}

// Convert a digit character to its integral value.
inline int digit_value(char digit)
{
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

// Normalise the input - remove any hyphens and check for other invalid
// characters.
string normalise_input(string input)
{
    ostringstream normalised;
    ostringstream string_stream;

    for (char &c : input) {
        if (c == '-') {
            continue;
        } else if (c < '0' || c > '9') {
            string_stream << "Invalid digit: \"" << c << "\"" << endl;
            throw invalid_argument(string_stream.str());
        }

        normalised << c;
    }

    return normalised.str();
}

// Calculate annd output the checksum digit.
void output_checksum(string input)
{
    int checksum;

    checksum = calculate_checksum(input);
    cout << "Checksum = " << checksum << endl;
}

// Calculate the checksum digit and verify that the last digit matches.
void verify_checksum(string input)
{
    int checksum;
    checksum = calculate_checksum(input);

    if (checksum == digit_value(input[NUM_DIGITS])) {
        cout << "Checksum matches." << endl;
    } else {
        cout << "Incorrect checksum. Should be " << checksum << endl;
    }
}


// Process the input. The user may either enter a 12 or 13 digit number.
// For a 12 digit number, we calculate the checksum and print it. For 13,
// we calculate the checksum, check it against the 13th digit entered,
// and print the validation success.
int main()
{
    string input;
    string normalised;

    cout << "Input 12 digits to generate the checksum digit. "
            "Input 13 digits to verify the checksum digit." << endl;
    cin >> input;

    try {
        normalised = normalise_input(input);
    } catch (const std::exception& err) {
        cout << err.what() << endl;
        return -1;
    }

    switch (normalised.length()) {
        case NUM_DIGITS:
            output_checksum(normalised);
            break;

        case NUM_DIGITS + 1:
            verify_checksum(normalised);
            break;

        default:
            cout << "Error: wrong input length." << endl;
            return 1;
    }

    return 0;
}

