/*
 * 6-3. Write a function that is passed an array of integers and a target number
 * and that returns the number of occurrences of the target in the array. Solve
 * the problem first using iteration, then recursion
 */

#include <cassert>
#include <iostream>

int CountTargetOccurencesIter(const int *arr, size_t arr_size, int target);
int CountTargetOccurencesRecur(const int *arr, size_t arr_size, int target);


// Test both iterative and recursive implemenations for counting the number of
// values in an int array that match the target value.
int main() {
    constexpr int arr_size = 10;
    const int arr[arr_size] = {23, -2, 34, -27, -98, 23, 70, -42, 23, -21};
    const int target = 23;

    const int iter_count = CountTargetOccurencesIter(arr, arr_size, target);
    std::cout << "Counted " << iter_count << " occurences iteratively."
              << std::endl;
    assert(iter_count == 3);

    const int recur_count = CountTargetOccurencesRecur(arr, arr_size, target);
    std::cout << "Counted " << recur_count << " occurences recursively."
              << std::endl;
    assert(recur_count == 3);

    // Test the count for empty arrays is 0.
    assert(CountTargetOccurencesIter(nullptr, 0, target) == 0);
    assert(CountTargetOccurencesRecur(nullptr, 0, target) == 0);

    return 0;
}

// Count the number of occurences of the target value in an array iteratively.
int CountTargetOccurencesIter(const int *arr, size_t arr_size, int target) {
    int count = 0;

    for (size_t i = 0; i < arr_size; ++i) {
        if (arr[i] == target) {
            ++count;
        }
    }

    return count;
}

// Count the number of occurences of the target value in an array recursively.
int CountTargetOccurencesRecur(const int *arr, size_t arr_size, int target) {
    if (arr_size == 0) {
        return 0;
    } else if (*arr == target) {
        return 1 + CountTargetOccurencesRecur(arr + 1, arr_size - 1, target);
    } else {
        return CountTargetOccurencesRecur(arr + 1, arr_size - 1, target);
    }
}

