/*
 * 4-9. Imagine a linked list where instead of the node storing a character, the node
 * stores a digit: an int in the range 0-9. We could represent positive numbers
 * of any size using such a linked list; the number 149, for example, would be a
 * linked list in which the first node stores a 1, the second a 4, and the third and
 * last a 9. Write a function intToList that takes an integer value and produces a
 * linked list of this sort. Hint: You may find it easier to build the linked list
 * backward, so if the value were 149, you would create the 9 node first.
 *
 * 4-10. For the digit list of the previous exercise, write a function that takes two such
 * lists and produces a new list representing their sum.
 */

#include <iostream>
#include <forward_list>

// Stores an integer as a list of digits.
class ListInt {
  public:
    // Construct the list of digits from an integer.
    explicit ListInt(int number) {
        while (number) {
            int next_digit = number % 10;
            digits_.push_front(next_digit);
            number /= 10;
        }
    }

    // Declare the stream formatter as a friend so that it can iterate
    // through the private digits.
    friend std::ostream &
    operator<<(std::ostream &strm, ListInt const &int_list);

    // Convert back from an ListInt into a plain integer.
    int ToInt() const {
        int result = 0;
        for (auto it = digits_.begin(); it != digits_.end(); ++it) {
            result *= 10;
            result += *it;
        }
        return result;
    }

    // Implement operator+ to add two ListInts together, returning a new
    // ListInt. Instead of calculating the sum digit-by-digit we simply
    // convert both ListInts back to plain ints, calculate the sum with
    // plain int addition and convert the result back into another ListInt.
    ListInt operator+(ListInt const &other) const {
        int int_result = ToInt() + other.ToInt();
        return ListInt(int_result);
    }

  private:
    // Store the digits as a list of ints.
    std::forward_list<int> digits_;
};

// Demonstrate construction of ListInts from plain integers, output stream
// formatting of ListInts, and addition of two ListInts.
int main() {
    const ListInt int_list(149);
    std::cout << "int_list = " << int_list << std::endl;

    const ListInt other(5439);
    std::cout << "other = " << other << std::endl;

    const ListInt sum = int_list + other;
    std::cout << "sum = " << sum << std::endl;

    return 0;
}

// Output stream formatter for ListInt. Output each digit from the digit list
// in order.
std::ostream & operator<<(std::ostream &strm, ListInt const &int_list) {
    for (auto it = int_list.digits_.begin(); it != int_list.digits_.end(); ++it) {
        strm << *it;
    }

    return strm;
}

