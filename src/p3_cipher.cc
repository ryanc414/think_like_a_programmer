/* Here’s a variation on the array of const values. Write a program for creating a
 * substitution cipher problem. In a substitution cipher problem, all messages
 * are made of uppercase letters and punctuation. The original message is called
 * the plaintext, and you create the ciphertext by substituting each letter with
 * another letter (for example, each C could become an X). For this problem,
 * hard-code a const array of 26 char elements for the cipher, and have your
 * program read a plaintext message and output the equivalent ciphertext.
 *
 * Have the previous program convert the ciphertext back to the plaintext to
 * verify the encoding and decoding.
 */

#include <iostream>
#include <array>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::array;
using std::string;

void encrypt_user_message();
void decrypt_user_message();
const string encrypt_string(const string &plaintext);
const string decrypt_string(const string &encrypted);

const int NUM_LETTERS = 26;

// Class that gives easy access to a cipher array via operator[]
//
// Usage e.g: cipher['G'] gives cipher value for letter G.
class CipherAccess {
  public:
    // Construct from a cipher array.
    explicit CipherAccess(const array<char, NUM_LETTERS> cipher_array)
        : cipher_array_(cipher_array) {};

    // operator[] provides read-access to the cipher value for a letter.
    const char &operator[](const char letter) const {
        return cipher_array_[letter - 'A'];
    }

    // Construct a new cipher that inverts this cipher.
    CipherAccess inverse() const {
        array<char, NUM_LETTERS> inverse_arr;

        for (char c = 'A'; c < 'Z'; ++c) {
            inverse_arr[cipher_array_[c - 'A'] - 'A'] = c;
        }

        return CipherAccess(inverse_arr);
    }

  private:
    const array<char, NUM_LETTERS> cipher_array_;
};


const CipherAccess CIPHER({
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
});

const CipherAccess INVERSE_CIPHER = CIPHER.inverse();


// Either encrypt or decrypt a user's message.
int main() {
    string rsp;

    cout << "(E)ncrypt or (D)ecrypt a message?" << endl << " > ";
    getline(cin, rsp);

    if (rsp[0] == 'E' || rsp[0] == 'e') {
        cout << "Encrypting a message." << endl;
        encrypt_user_message();
    } else if (rsp[0] == 'D' || rsp[0] == 'd') {
        cout << "Decrypting a message." << endl;
        decrypt_user_message();
    }

    return 0;
}


// Read in a line of plaintext and output the encrypted line.
void encrypt_user_message() {
    string plaintext;

    cout << "Enter the plaintext line:" << endl << " > ";
    getline(cin, plaintext);

    const string encrypted = encrypt_string(plaintext);
    cout << "Encrypted: " << encrypted << endl;
}


// Read in a line containing an encrypted message and output the decrypted
// plaintext.
void decrypt_user_message() {
    string encrypted;

    cout << "Enter the encrypted line:" << endl << " > ";
    getline(cin, encrypted);

    const string plaintext = decrypt_string(encrypted);
    cout << "Plaintext: " << plaintext << endl;
}

// Convert a plaintext string into an encrypted string using the cipher.
const string encrypt_string(const string &plaintext) {
    string encrypted;
    encrypted.reserve(plaintext.size());

    for (char c : plaintext) {
        if (c >= 'A' && c <= 'Z') {
            encrypted.push_back(CIPHER[c]);
        } else {
            encrypted.push_back(c);
        }
    }

    return encrypted;
}


// Convert an encrypted string into its decrypted plaintext.
const string decrypt_string(const string &encrypted) {
    string decrypted;
    decrypted.reserve(encrypted.size());

    for (char c : encrypted) {
        if (c >= 'A' && c <= 'Z') {
            decrypted.push_back(INVERSE_CIPHER[c]);
        } else {
            decrypted.push_back(c);
        }
    }

    return decrypted;
}

