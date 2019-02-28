#include <iostream>
#include <bitset>
#include <sstream>
#include <limits>
#include <string>
#include <iomanip>
#include <stdlib.h>

int GetBase(std::string msg);
int GetUserInput();
std::string IntToString(int input_num, int base);
std::string ConvertToOutput(int input_num);

// Get the input in a specified base, then convert to output in another base.
// Display the result.
int main() {
    int input_num;
    std::string output_repr;

    input_num = GetUserInput();
    output_repr = ConvertToOutput(input_num);
    std::cout << "Output representation = " << output_repr << std::endl;

    return 0;
}

// Prompt user to enter a base in range 2-16.
int GetBase(std::string msg) {
    int base;
    std::string rsp;
    std::ostringstream ss;

    std::cout << msg << " (2-16):" << std::endl << "> ";
    std::cin >> rsp;
    base = std::stoi(rsp);
    if (base < 2 || base > 16) {
        ss << "Unexpected base " << base;
        throw std::out_of_range(ss.str());
    }

    return base;
}

// Get the user to enter a base and then a number in that base.
int GetUserInput() {
    std::string rsp;
    int base;
    int input_num;

    base = GetBase("Enter input base");

    std::cout << "Enter number:" << std::endl << "> ";
    std::cin >> rsp;
    input_num = std::stoi(rsp, NULL, base);

    return input_num;
}

// Convert an integer into a string representation for a given base.
std::string IntToString(int input_num, int base) {
    std::string output_repr = "";
    const std::string digits = "0123456789abcdefg";

    while (input_num != 0) {
        output_repr = digits[input_num % base] + output_repr;
        input_num /= base;
    }

    return output_repr;
}

// Prompt a user to enter a base and return the converted string
// representation of the previously entered integer in that base.
std::string ConvertToOutput(int input_num) {
    int base;
    std::string output_repr;

    base = GetBase("Enter output base");
    output_repr = IntToString(input_num, base);

    return output_repr;
}

