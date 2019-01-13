#include <iostream>
#include <bitset>
#include <sstream>
#include <limits>
#include <string>
#include <iomanip>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::runtime_error;
using std::ostringstream;
using std::out_of_range;
using std::stoi;

int get_base(string msg);
int get_user_input();
string itostr(int input_num, int base);
string convert_to_output(int input_num);


// Get the input in a specified base, then convert to output in another base.
// Display the result.
int main()
{
    int input_num;
    string output_repr;

    input_num = get_user_input();
    output_repr = convert_to_output(input_num);
    cout << "Output representation = " << output_repr << endl;

    return 0;
}

// Prompt user to enter a base in range 2-16.
int get_base(string msg)
{
    int base;
    string rsp;
    ostringstream ss;

    cout << msg << " (2-16):" << endl << "> ";
    cin >> rsp;
    base = stoi(rsp);
    if (base < 2 || base > 16) {
        ss << "Unexpected base " << base;
        throw out_of_range(ss.str());
    }

    return base;
}

// Get the user to enter a base and then a number in that base.
int get_user_input()
{
    string rsp;
    int base;
    int input_num;

    base = get_base("Enter input base");

    cout << "Enter number:" << endl << "> ";
    cin >> rsp;
    input_num = stoi(rsp, NULL, base);

    return input_num;
}

// Convert an integer into a string representation for a given base.
string itostr(int input_num, int base)
{
    string output_repr = "";
    const string digits = "0123456789abcdefg";

    while (input_num != 0) {
        output_repr = digits[input_num % base] + output_repr;
        input_num /= base;
    }

    return output_repr;
}

// Prompt a user to enter a base and return the converted string
// representation of the previously entered integer in that base.
string convert_to_output(int input_num)
{
    int base;
    string output_repr;

    base = get_base("Enter output base");
    output_repr = itostr(input_num, base);

    return output_repr;
}

