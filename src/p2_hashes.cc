/*
 * P2.1: Using the same rule as the shapes programs from earlier in the chapter (only
 * two output statements—one that outputs the hash mark and one that outputs
 * an end-of-line), write a program that produces the following shape:
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
#include <cassert>
using std::cout;
using std::cin;

#define LIMIT 4

inline void print_newline();
inline void print_hash();
inline void print_space();
void print_hashes(int num);
void print_spaces(int num);
void symmetrical_line(int spaces, int hashes);
void p2_1();
void p2_2();
void p2_3();
void p2_4();

// Functions to print a single character.
inline void print_newline()
{
    cout << std::endl;
}

inline void print_hash()
{
    cout << '#';
}

inline void print_space()
{
    cout << ' ';
}

// Print a number of spaces.
void print_spaces(int num)
{
    assert(num >= 0);
    for (int ii = 0; ii < num; ii++)
    {
        print_space();
    }
}

// Print a number of hashes.
void print_hashes(int num)
{
    assert(num >= 0);
    for (int ii = 0; ii < num; ii++)
    {
        print_hash();
    }
}

// Print a symmetrical line with a certain number of spaces, a certain number
// of hashes, and as many more spaces as needed to pad to the centre. The
// pattern in repeated in reverse on the other side of the centre.
void symmetrical_line(int spaces, int hashes, int centre)
{
    int leftover = centre - (spaces + hashes);
    assert(leftover >= 0);

    print_spaces(spaces);
    print_hashes(hashes);
    print_spaces(2 * leftover);
    print_hashes(hashes);
    print_newline();
}

// Print the hash pattern for P2.1.
void p2_1()
{
    int jj;
    const int limit = 4;

    for (int ii = 0; ii < limit; ii++)
    {
        symmetrical_line(ii, limit - ii, limit);
    }

    print_newline();
}

// Print the hash pattern for P2.2.
void p2_2()
{
    const int limit = 4;

    for (int ii = limit - 1; ii >= 0; ii--)
    {
        symmetrical_line(ii, limit - ii, limit);
    }

    for (int ii = 0; ii < LIMIT; ii++)
    {
        symmetrical_line(ii, limit - ii, limit);
    }

    print_newline();
}

// Print the hash pattern for P2.3.
void p2_3()
{
    const int limit = 4;
    const int centre = 7;

    for (int ii = 0; ii < limit; ii++)
    {
        symmetrical_line(ii, ii + 1, centre);
    }

    for (int ii = 3; ii >= 0; ii--)
    {
        symmetrical_line(ii, ii + 1, centre);
    }

    print_newline();
}

void p2_4()
{
    const int centre = 5;
    const int tail_length = 6;

    for (int ii = 0; ii < 5; ii++)
    {
        symmetrical_line(LIMIT - ii, ii + 1, centre);
    }

    for (int ii = 0; ii < tail_length; ii++)
    {
        symmetrical_line(3, 2, centre);
    }

    print_newline();
}

// Print hash patters for all three problems.
int main()
{
    p2_1();
    p2_2();
    p2_3();
    p2_4();

    return 0;
}

