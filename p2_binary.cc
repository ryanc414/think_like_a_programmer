#include <iostream>
#include <bitset>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::bitset;
using std::runtime_error;

void decimal_to_binary();
void binary_to_decimal();


int main()
{
    string rsp;

    cout << "Convert from binary (b) or decimal (d)?" << endl << "> ";
    cin >> rsp;
    switch (rsp[0]) {
        case 'b':
            binary_to_decimal();
            break;

        case 'd':
            decimal_to_binary();
            break;

        default:
            throw runtime_error("Bad input.");
    }

    return 0;
}

void decimal_to_binary()
{
    unsigned long decimal;
    bitset<8 * sizeof(long)> binary;

    cout << "Decimal -> binary selected. Enter decimal number:" << endl
         << "> ";
    cin >> decimal;
    binary = bitset<8 * sizeof(long)>(decimal);
    cout << "In binary: " << binary << endl;
}

void binary_to_decimal()
{
    unsigned long decimal;
    bitset<8 * sizeof(long)> binary;

    cout << "Binary -> decimal selected. Enter decimal number:" << endl
         << "> ";
    cin >> binary;
    decimal = binary.to_ulong();
    cout << "In decimal: " << decimal << endl;
}

