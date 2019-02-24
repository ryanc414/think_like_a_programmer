/* P2.1: Using the same rule as the shapes programs from earlier in the chapter
 * (only two output statements—one that outputs the hash mark and one that
 * outputs an end-of-line), write a program that produces the following shape:
 *
 * ########
 *  ######
 *   ####
 *    ##
 *
 * P2.2:
 *    ##
 *   ####
 *  ######
 * ########
 * ########
 *  ######
 *   ####
 *    ##
 *
 * P2.3:
 * #            #
 *  ##        ##
 *   ###    ###
 *    ########
 *    ########
 *   ###    ###
 *  ##        ##
 * #            #
 *
 * P2.4:
 *      ##
 *     ####
 *    ######
 *   ########
 *  ##########
 *     ####
 *     ####
 *     ####
 *     ####
 *     ####
 *     ####
 */

#include <iostream>

constexpr int kLimit = 4;

inline void PrintNewline();
inline void PrintHash();
inline void PrintSpace();
void PrintHashes(int num);
void PrintSpaces(int num);
void SymmetricalLine(int spaces, int hashes);
void P2_1();
void P2_2();
void P2_3();
void P2_4();

// Functions to print a single character.
inline void PrintNewline() {
    std::cout << std::endl;
}

inline void PrintHash() {
    std::cout << '#';
}

inline void PrintSpace() {
    std::cout << ' ';
}

// Print a number of spaces.
void PrintSpaces(int num) {
    if (num < 0) {
        throw std::out_of_range("num must be non-negative.");
    }

    for (int ii = 0; ii < num; ii++) {
        PrintSpace();
    }
}

// Print a number of hashes.
void PrintHashes(int num) {
    if (num < 0) {
        throw std::out_of_range("num must be non-negative.");
    }

    for (int ii = 0; ii < num; ii++) {
        PrintHash();
    }
}

// Print a symmetrical line with a certain number of spaces, a certain number
// of hashes, and as many more spaces as needed to pad to the kCentre. The
// pattern in repeated in reverse on the other side of the kCentre.
void SymmetricalLine(int spaces, int hashes, int kCentre) {
    int leftover = kCentre - (spaces + hashes);
    if (leftover < 0) {
        throw std::out_of_range(
            "kCentre is too small for number of spaces and hashes.");
    }

    PrintSpaces(spaces);
    PrintHashes(hashes);
    PrintSpaces(2 * leftover);
    PrintHashes(hashes);
    PrintNewline();
}

// Print the hash pattern for P2.1.
void P2_1() {
    for (int ii = 0; ii < kLimit; ii++) {
        SymmetricalLine(ii, kLimit - ii, kLimit);
    }

    PrintNewline();
}

// Print the hash pattern for P2.2.
void P2_2() {
    for (int ii = kLimit - 1; ii >= 0; ii--) {
        SymmetricalLine(ii, kLimit - ii, kLimit);
    }

    for (int ii = 0; ii < kLimit; ii++) {
        SymmetricalLine(ii, kLimit - ii, kLimit);
    }

    PrintNewline();
}

// Print the hash pattern for P2.3.
void P2_3() {
    constexpr int kkCentre = 7;

    for (int ii = 0; ii < kLimit; ii++) {
        SymmetricalLine(ii, ii + 1, kkCentre);
    }

    for (int ii = 3; ii >= 0; ii--) {
        SymmetricalLine(ii, ii + 1, kkCentre);
    }

    PrintNewline();
}

void P2_4() {
    constexpr int kCentre = 5;
    constexpr int kTailLength = 6;

    for (int ii = 0; ii < 5; ii++) {
        SymmetricalLine(kLimit - ii, ii + 1, kCentre);
    }

    for (int ii = 0; ii < kTailLength; ii++) {
        SymmetricalLine(3, 2, kCentre);
    }

    PrintNewline();
}

// Print hash patters for all three problems.
int main() {
    P2_1();
    P2_2();
    P2_3();
    P2_4();

    return 0;
}

