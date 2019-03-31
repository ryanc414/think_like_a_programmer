/*
 * 6-1. Write a function to compute the sum of just the positive numbers in an array
 * of integers. First, solve the problem using iteration. Then, using the technique
 * shown in this chapter, convert your iterative function to a recursive function.
 */

#include <cassert>
#include <iostream>

int SumPositivesIter(const int *arr, size_t size);
int SumPositivesRecur(const int *arr, size_t size);


// Test both iterative and recursive functions for summing the positive
// values in an int array.
int main() {
    constexpr size_t array_size = 10;
    const int arr[array_size] = {3, 3, 2, -1, -6, 2, -4, 9, -1, 2};

    const int iter_sum = SumPositivesIter(arr, array_size);
    std::cout << "Iterative sum of positives = " << iter_sum << std::endl;
    assert(iter_sum == 21);

    const int recur_sum = SumPositivesRecur(arr, array_size);
    std::cout << "Recursive sum of positives = " << recur_sum << std::endl;
    assert(recur_sum == 21);

    // Test both functions on empty arrays - they should return 0.
    assert(SumPositivesIter(nullptr, 0) == 0);
    assert(SumPositivesRecur(nullptr, 0) == 0);

    return 0;
}

// Sum the positive values in an array of integers using iteration.
int SumPositivesIter(const int *arr, size_t size) {
    int positives_sum = 0;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            positives_sum += arr[i];
        }
    }

    return positives_sum;
}

// Sum the positive values in an array of integers using recursion.
int SumPositivesRecur(const int *arr, size_t size) {
    if (size == 0) {
        return 0;
    } else if (*arr > 0) {
        return *arr + SumPositivesRecur(arr + 1, size - 1);
    } else {
        return SumPositivesRecur(arr + 1, size - 1);
    }
}

