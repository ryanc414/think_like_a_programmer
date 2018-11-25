#include <iostream>
#include <bitset>
#include <sstream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::bitset;
using std::runtime_error;
using std::hex;
using std::ostringstream;


unsigned long get_user_input();
void convert_to_output(unsigned long input);
unsigned long get_binary_input();
unsigned long get_hex_input();
unsigned long get_decimal_input();


int main()
{
    unsigned long input;

    input = get_user_input();
    convert_to_output(input);

    return 0;
}

unsigned long get_user_input()
{
    string rsp;
    unsigned long converted_input;
    ostringstream ss;

    cout << "Select input format: (b)inary, (h)ex or (d)ecimal?"
         << endl
         << "> ";
    cin >> rsp;

    switch (rsp[0]) {
        case 'b':
            converted_input = get_binary_input();
            break;

        case 'h':
            converted_input = get_hex_input();
            break;

        case 'd':
            converted_input = get_decimal_input();
            break;

        default:
            ss << "Bad input: " << rsp;
            throw runtime_error(ss.str());
    }

    return converted_input;
}

unsigned long get_binary_input()
{
    bitset<8 * sizeof(long)> binary;

    cout << "Binary input selected. Enter binary number:" << endl
         << "> ";
    cin >> binary;
    return binary.to_ulong();
}

unsigned long get_hex_input()
{
    unsigned long hex_input;

    cout << "Hex input selected. Enter hex number:" << endl
         << "> ";
    cin >> hex >> hex_input;

    return hex_input;
}


unsigned long get_decimal_input()
{
    unsigned long decimal;

    cout << "Decimal input selected. Enter decimal number:" << endl
         << "> ";
    cin >> decimal;

    return decimal;
}

void convert_to_output(unsigned long input)
{
    string rsp;
    bitset<8 * sizeof(long)> binary;
    ostringstream ss;

    //cin.ignore(std::numeric_limits<std::streamsize>::max());
    cout << "Select output format: (b)inary, (h)ex or (d)ecimal?"
         << endl
         << "> ";
    cin >> rsp;

    switch(rsp[0]) {
        case 'b':
            binary = bitset<8* sizeof(long)>(input);
            cout << binary << endl;
            break;

        case 'h':
            cout << hex << input << endl;
            break;

        case 'd':
            cout << input << endl;
            break;

        default:
            ss << "Bad input: " << rsp;
            throw runtime_error(ss.str());
    }
}

