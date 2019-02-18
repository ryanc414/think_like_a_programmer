/* Write a bool function that is passed an array and the number of elements in
 * that array and determines whether the data in the array is sorted. This should
 * require only one pass!
 */
#include <iostream>
#include <vector>
#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::range_error;

bool is_sorted(vector<int> arr);


// Read an input array from stdin and determine if it is sorted.
int main()
{
    vector<int> input_vec;
    int num_elements;
    int next_el;

    cout << "Enter number of elements:" << endl << "> ";
    cin >> num_elements;
    if (num_elements < 0) {
        throw range_error("Number of elements must be positive.");
    }

    input_vec.reserve(num_elements);
    for (int i = 0; i < num_elements; i++) {
        cout << "Enter next element:" << endl << "> ";
        cin >> next_el;
        input_vec.push_back(next_el);
    }

    cout << "Vector is sorted? " << is_sorted(input_vec) << endl;

    return 0;
}


// Determine if an array is sorted. Unlike the problem decription, use a
// std::vector here so that it can be accessed by iterarors and has a size
// determined at runtime.
//
// We only check for sorting in ascending numerical order. An empty array is
// considered to be sorted.
bool is_sorted(vector<int> arr)
{
    // No iteration will be performed for empty or single-element vectors -
    // both cases are considered to be sorted.
    for (auto cur = arr.begin() + 1; cur < arr.end(); cur++) {

        // Compare with the previous element - if the current element is
        // smaller the array cannot be sorted.
        auto prev = cur - 1;
        if (*cur < *prev) {
            return false;
        }
    }

    // If no out-of-order elements were found we conclude that the vector
    // is sorted.
    return true;
}

