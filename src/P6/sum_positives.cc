/*
 * 6-1. Write a function to compute the sum of just the positive numbers in an array
 * of integers. First, solve the problem using iteration. Then, using the technique
 * shown in this chapter, convert your iterative function to a recursive function.
 *
 * 6-5. Solve exercise 6-1 again, using a linked list instead of an array.
 */

#include <cassert>
#include <iostream>
#include <forward_list>

void test_sum_positives_array();
void test_sum_positives_list();
int SumPositivesIter(const int *arr, size_t size);
int SumPositivesIter(const std::forward_list<int> int_list);
int SumPositivesRecur(const int *arr, size_t size);
int SumPositivesRecur(const std::forward_list<int> int_list);

// Test the sum positives functions for both arrays and lists.
int main() {
    test_sum_positives_array();
    test_sum_positives_list();

    std::cout << "Tests passed for array and list positive sums." << std::endl;

    return 0;
}

// Test both iterative and recursive functions for summing the positive
// values in an int array.
void test_sum_positives_array() {
    constexpr size_t array_size = 10;
    const int arr[array_size] = {3, 3, 2, -1, -6, 2, -4, 9, -1, 2};

    const int iter_sum = SumPositivesIter(arr, array_size);
    assert(iter_sum == 21);

    const int recur_sum = SumPositivesRecur(arr, array_size);
    assert(recur_sum == 21);

    // Test both functions on empty arrays - they should return 0.
    assert(SumPositivesIter(nullptr, 0) == 0);
    assert(SumPositivesRecur(nullptr, 0) == 0);
}

// Test both iterative and recursive functions for summing the positive
// values in a list of ints.
void test_sum_positives_list() {
    // Test the sum of positive ints in the list defined here.
    const std::forward_list<int> int_list(
        {8, 1, 2, -12, -2, 23, -4, 1, 98, -4, 0});

    const int iter_sum = SumPositivesIter(int_list);
    std::cout << "Iterative positives sum of list = " << iter_sum << std::endl;

    const int recur_sum = SumPositivesRecur(int_list);
    std::cout << "Recursive positives sum of list = " << recur_sum
              << std::endl;

    // Test the sum of an empty list is 0.
    const std::forward_list<int> empty_list;
    assert(SumPositivesIter(empty_list) == 0);
    assert(SumPositivesRecur(empty_list) == 0);
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

// Sum the positive values in a list of ints using iteration.
int SumPositivesIter(const std::forward_list<int> int_list) {
    int positives_sum = 0;

    for (auto it = int_list.begin(); it != int_list.end(); ++it) {
        if (*it > 0) {
            positives_sum += *it;
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

// Sum the positive values in a list of ints using recursion.
int SumPositivesRecur(const std::forward_list<int> int_list) {
    // TODO
}

