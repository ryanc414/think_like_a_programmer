/* Write a bool function that is passed an array and the number of elements in
 * that array and determines whether the data in the array is sorted. This should
 * require only one pass!
 */
#include <iostream>
#include <vector>
#include <stdexcept>

bool IsSorted(const std::vector<int> &arr);

// Read an input array from stdin and determine if it is sorted.
int main() {
    std::vector<int> input_vec;
    int num_elements;

    std::cout << "Enter number of elements:" << std::endl << "> ";
    std::cin >> num_elements;
    if (num_elements < 0) {
        throw std::range_error("Number of elements must be positive.");
    }

    input_vec.reserve(num_elements);

    for (int i = 0; i < num_elements; i++) {
        int next_el;
        std::cout << "Enter element " << i + 1 << "/" << num_elements
             << std::endl << "> ";
        std::cin >> next_el;
        input_vec.push_back(next_el);
    }

    std::cout << "Input is sorted? " << std::boolalpha
              << IsSorted(input_vec) << std::endl;

    return 0;
}


// Determine if an array is sorted. Unlike the problem decription, use a
// std::vector here so that it can be accessed by iterarors and has a size
// determined at runtime.
//
// We only check for sorting in ascending numerical order. An empty array is
// considered to be sorted.
bool IsSorted(const std::vector<int> &arr) {
    // No iteration will be performed for empty or single-element std::vectors -
    // both cases are considered to be sorted.
    for (auto cur = arr.begin() + 1; cur < arr.end(); cur++) {

        // Compare with the previous element - if the current element is
        // smaller the array cannot be sorted.
        auto prev = cur - 1;
        if (*cur < *prev) {
            return false;
        }
    }

    // If no out-of-order elements were found we conclude that the std::vector
    // is sorted.
    return true;
}

