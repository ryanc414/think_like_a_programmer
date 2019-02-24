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
 *
 * To make the ciphertext problem even more challenging, have your pro-
 * gram randomly generate the cipher array instead of a hard-coded const array.
 * Effectively, this means placing a random character in each element of the
 * array, but remember that you can’t substitute a letter for itself. So the first
 * element can’t be A, and you can’t use the same letter for two substitutions—
 * that is, if the first element is S, no other element can be S.
 */

#include <iostream>
#include <array>
#include <string>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::array;
using std::string;

const int NUM_LETTERS = 26;

// A Cipher represents a mapping between characters in a plaintext and
// encrypted form.
class Cipher {
  public:
    // Construct by generating a random array.
    Cipher() : cipher_array_(generate_cipher_array()) {}

    // Construct from a cipher array.
    explicit Cipher(const array<char, NUM_LETTERS> cipher_array)
        : cipher_array_(cipher_array) {};

    // Construct a new cipher that inverts this cipher.
    Cipher inverse() const {
        array<char, NUM_LETTERS> inverse_arr;

        for (char c = 'A'; c <= 'Z'; ++c) {
            inverse_arr[(*this)[c] - 'A'] = c;
        }

        return Cipher(inverse_arr);
    }

    // operator[] provides read-access to the cipher value for a single letter.
    const char &operator[](const char letter) const {
        return cipher_array_[letter - 'A'];
    }

    // Convert a string using this cipher.
    const string convert_string(const string &from) const {
        string result;
        result.reserve(from.size());

        for (char c : from) {
            if (c >= 'A' && c <= 'Z') {
                result.push_back((*this)[c]);
            } else {
                result.push_back(c);
            }
        }

        return result;
    }

  private:
    // Array that defines the cipher mapping.
    const array<char, NUM_LETTERS> cipher_array_;

    // Generate a cipher array using a randomly generated shift.
    const array<char, NUM_LETTERS> generate_cipher_array() {
        array<char, NUM_LETTERS> generated;

        // Generate a random shift in the range 1-25.
        int shift = rand() % (NUM_LETTERS - 1) + 1;

        for (int i = 0; i < NUM_LETTERS; i++) {
            generated[(i + shift) % NUM_LETTERS] = 'A' + i;
        }

        return generated;
    }
};


// Encrypt and then decrypt a message entered by the user.
int main() {
    const Cipher cipher;
    const Cipher inverse_cipher = cipher.inverse();
    string plaintext;

    cout << "Enter the plaintext line:" << endl << " > ";
    getline(cin, plaintext);

    const string encrypted = cipher.convert_string(plaintext);
    cout << "Encrypted: " << encrypted << endl;

    const string decrypted = inverse_cipher.convert_string(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}

