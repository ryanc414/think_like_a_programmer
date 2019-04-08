/*
 * 6-3. Write a function that is passed an array of integers and a target number
 * and that returns the number of occurrences of the target in the array. Solve
 * the problem first using iteration, then recursion.
 *
 * 6-7. Solve exercise 6-3 again, using a linked list instead of an array.
 */

#include <cassert>
#include <iostream>
#include <forward_list>

void TestArrayCount();
void TestListCount();
int CountTargetOccurencesIter(const int *arr, size_t arr_size, int target);
int CountTargetOccurencesIter(const std::forward_list<int> &int_list,
                              int target);
int CountTargetOccurencesRecur(const int *arr, size_t arr_size, int target);
int CountTargetOccurencesRecur(const std::forward_list<int> &int_list,
                               int target);
int CountTargetOccurencesRecur(std::forward_list<int>::const_iterator it,
                               std::forward_list<int>::const_iterator end,
                               int target);

// Test the target count functions for both arrays and lists.
int main() {
    TestArrayCount();
    TestListCount();

    std::cout << "All tests passed." << std::endl;

    return 0;
}

// Test both iterative and recursive implemenations for counting the number of
// values in an int array that match the target value.
void TestArrayCount() {
    constexpr int kArrSize = 10;
    const int kTestArr[kArrSize] = {
        23, -2, 34, -27, -98, 23, 70, -42, 23, -21};
    const int kTarget = 23;

    const int iter_count = CountTargetOccurencesIter(
        kTestArr, kArrSize, kTarget);
    assert(iter_count == 3);

    const int recur_count = CountTargetOccurencesRecur(
        kTestArr, kArrSize, kTarget);
    assert(recur_count == 3);

    // Test the count for empty arrays is 0.
    assert(CountTargetOccurencesIter(nullptr, 0, kTarget) == 0);
    assert(CountTargetOccurencesRecur(nullptr, 0, kTarget) == 0);
}

// Test both iterative and recursive implementations for counting the number
// of values in a list of ints that match the target value.
void TestListCount() {
    const std::forward_list<int> kTestList{
        23, -2, 34, -27, -98, 23, 70, -42, 23, -21};
    const int kTarget = 23;

    const int iter_count = CountTargetOccurencesIter(kTestList, kTarget);
    assert(iter_count == 3);

    const int recur_count = CountTargetOccurencesRecur(kTestList, kTarget);
    assert(recur_count == 3);

    // Test the count for empty lists is 0.
    const std::forward_list<int> kEmptyList;
    assert(CountTargetOccurencesIter(kEmptyList, kTarget) == 0);
    assert(CountTargetOccurencesRecur(kEmptyList, kTarget) == 0);
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

// Count the number of occurences of the target value in list iteratively.
int CountTargetOccurencesIter(const std::forward_list<int> &int_list,
                              int target) {
    int count = 0;

    for (int el : int_list) {
        if (el == target) {
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

int CountTargetOccurencesRecur(const std::forward_list<int> &int_list,
                               int target) {
    return CountTargetOccurencesRecur(
        int_list.begin(), int_list.end(), target);
}

int CountTargetOccurencesRecur(std::forward_list<int>::const_iterator it,
                               std::forward_list<int>::const_iterator end,
                               int target) {
    if (it == end) {
        return 0;
    } else if (*it == target) {
        return 1 + CountTargetOccurencesRecur(++it, end, target);
    } else {
        return CountTargetOccurencesRecur(++it, end, target);
    }
}

