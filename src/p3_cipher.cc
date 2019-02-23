/* Here’s a variation on the array of const values. Write a program for creating a
 * substitution cipher problem. In a substitution cipher problem, all messages
 * are made of uppercase letters and punctuation. The original message is called
 * the plaintext, and you create the ciphertext by substituting each letter with
 * another letter (for example, each C could become an X). For this problem,
 * hard-code a const array of 26 char elements for the cipher, and have your
 * program read a plaintext message and output the equivalent ciphertext.
 */

#include <iostream>
#include <array>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::array;
using std::string;

const string encrypt_plaintext(const string &plaintext);

array<char,26> CIPHER = {
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'
};


int main() {
    string plaintext;

    cout << "Enter the plaintext:" << endl << " >";
    cin >> plaintext;

    const string encrypted = encrypt_plaintext(plaintext);
    cout << "Encrypted: " << encrypted << endl;

    return 0;
}


const string encrypt_plaintext(const string &plaintext) {
    string encrypted;
    encrypted.reserve(plaintext.size());

    for (char c : plaintext) {
        if (c >= 'A' && c <= 'Z') {
            encrypted.push_back(CIPHER[c - 'A']);
        } else {
            encrypted.push_back(c);
        }
    }

    return encrypted;
}

