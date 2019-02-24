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

constexpr int kNumDigits = 12;
constexpr int kMultiplier = 3;

int CalculateChecksum();
inline int DigitValue(char digit);
int ChecksumFromDigitSum(long sum);
std::string NormaliseInput(std::string input);
void OutputChecksum(std::string input);
void VerifyChecksum(std::string input);

// Calculate the cheksum, reading the first 12 digits from stdin.
int CalculateChecksum(std::string input) {
    long sum = 0;

    for (int ii = 0; ii < kNumDigits; ii++) {
        // For the first, third etc. digits just add the digit's value to the
        // sum. For the second, fourth etc. digits multiply the digit's value
        // by three.
        if (ii % 2 == 0) {
            sum += DigitValue(input[ii]);
        } else {
            sum += DigitValue(input[ii]) * kMultiplier;
        }
    }

    return ChecksumFromDigitSum(sum);
}

// Convert a digit character to its integral value.
inline int DigitValue(char digit) {
    return digit - '0';
}

// Given the digit sum, calculate the checksum digit.
int ChecksumFromDigitSum(long sum) {
    int remainder = sum % 10;

    if (remainder == 0) {
        return remainder;
    } else {
        return 10 - remainder;
    }
}

// Normalise the input - remove any hyphens and check for other invalid
// characters.
std::string NormaliseInput(std::string input) {
    std::ostringstream normalised;

    for (char &c : input) {
        if (c == '-') {
            continue;
        } else if (c < '0' || c > '9') {
            std::ostringstream string_stream;
            string_stream << "Invalid digit: \"" << c << "\"" << std::endl;
            throw std::invalid_argument(string_stream.str());
        }

        normalised << c;
    }

    return normalised.str();
}

// Calculate annd output the checksum digit.
void OutputChecksum(std::string input) {
    int checksum = CalculateChecksum(input);
    std::cout << "Checksum = " << checksum << std::endl;
}

// Calculate the checksum digit and verify that the last digit matches.
void VerifyChecksum(std::string input) {
    int checksum = CalculateChecksum(input);

    if (checksum == DigitValue(input[kNumDigits])) {
        std::cout << "Checksum matches." << std::endl;
    } else {
        std::cout << "Incorrect checksum. Should be " << checksum << std::endl;
    }
}


// Process the input. The user may either enter a 12 or 13 digit number.
// For a 12 digit number, we calculate the checksum and print it. For 13,
// we calculate the checksum, check it against the 13th digit entered,
// and print the validation success.
int main() {
    std::string input;
    std::string normalised;

    std::cout << "Input 12 digits to generate the checksum digit. "
            "Input 13 digits to verify the checksum digit." << std::endl;
    std::cin >> input;

    try {
        normalised = NormaliseInput(input);
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
        return -1;
    }

    switch (normalised.length()) {
        case kNumDigits:
            OutputChecksum(normalised);
            break;

        case kNumDigits + 1:
            VerifyChecksum(normalised);
            break;

        default:
            std::cout << "Error: wrong input length." << std::endl;
            return 1;
    }

    return 0;
}

