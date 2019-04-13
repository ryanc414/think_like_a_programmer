/* 6-8. Design your own: Try to discover a linked-list processing problem that is
 * difficult to solve using iteration but can be solved directly using recursion
 *
 * Let's try removing the last element in a forward_list that matches a
 * particular value.
 */

#include <iostream>
#include <forward_list>

enum RemoveLastAction {
    kCheck = 0,
    kRemoveNext = 1,
    kReturn = 2
};

bool RemoveLast(std::forward_list<int> &list, int val);
RemoveLastAction RemoveLastRecur(std::forward_list<int> &list,
                                 std::forward_list<int>::iterator it,
                                 int val);

// Test removing the last 1 from a list of ints.
int main() {
    std::forward_list<int> test_list{1, 2, 5, 1, 2, 2, 4, 1, 2, 1, 1, 9};

    RemoveLast(test_list, 1);

    for (auto val : test_list) {
        std::cout << val << ", ";
    }
    std::cout << std::endl;

    return 0;
}

// Removes the last instance of a value from a list.
bool RemoveLast(std::forward_list<int> &list, int val) {
    switch (RemoveLastRecur(list, list.begin(), val)) {
        case kCheck:
            return false;

        case kRemoveNext:
            list.erase_after(list.before_begin());
            return true;

        case kReturn:
            return true;

        default:
            throw std::runtime_error("Unexpected return");
    }
}

// Recursive step to remove the lat instance of a value from a list.
RemoveLastAction RemoveLastRecur(std::forward_list<int> &list,
                                 std::forward_list<int>::iterator it,
                                 int val) {
    if (it == list.end()) {
        return kCheck;
    }

    auto next_it = it;
    ++next_it;

    switch (RemoveLastRecur(list, next_it, val)) {
        case kCheck:
            if (*it == val) {
                return kRemoveNext;
            } else {
                return kCheck;
            }

        case kRemoveNext:
            list.erase_after(it);
            return kReturn;

        case kReturn:
            return kReturn;

        default:
            throw std::runtime_error("Unexpected return");
    }
}

