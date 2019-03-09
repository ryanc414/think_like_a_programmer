/* Write a bool function that is passed an array and the number of elements in
 * that array and determines whether the data in the array is sorted. This should
 * require only one pass!
 *
 * 4-1. Design your own: Take a problem that you already know how to solve using
 * an array but that is limited by the size of the array. Rewrite the code to remove
 * that limitation using a dynamically allocated array.
 */
#include <iostream>
#include <stdexcept>
#include <array>

bool IsSorted(int *arr, int num_elements);

// Read an input array from stdin and determine if it is sorted.
int main() {
    int num_elements;

    std::cout << "Enter number of elements:" << std::endl << "> ";
    std::cin >> num_elements;
    if (num_elements < 0) {
        throw std::range_error("Number of elements must be positive.");
    }

    int input_arr[num_elements];

    for (int i = 0; i < num_elements; i++) {
        int next_el;
        std::cout << "Enter element " << i + 1 << "/" << num_elements
             << std::endl << "> ";
        std::cin >> next_el;
        input_arr[i] = next_el;
    }

    std::cout << "Input is sorted? " << std::boolalpha
              << IsSorted(input_arr, num_elements) << std::endl;

    return 0;
}


// Determine if an array is sorted. Unlike the problem decription, use a
// std::vector here so that it can be accessed by iterarors and has a size
// determined at runtime.
//
// We only check for sorting in ascending numerical order. An empty array is
// considered to be sorted.
bool IsSorted(int *arr, int num_elements) {
    // No iteration will be performed for empty or single-element std::vectors -
    // both cases are considered to be sorted.
    for (int i = 1; i < num_elements; i++) {

        // Compare with the previous element - if the current element is
        // smaller the array cannot be sorted.
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }

    // If no out-of-order elements were found we conclude that the std::vector
    // is sorted.
    return true;
}

