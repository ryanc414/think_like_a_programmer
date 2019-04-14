/* 6-8. Design your own: Try to discover a linked-list processing problem that is
 * difficult to solve using iteration but can be solved directly using recursion
 *
 * Let's try to reverse a forward_list in-place.
 */

#include <cassert>
#include <forward_list>

void ReverseList(std::forward_list<int> &list);
void ReverseListRecur(std::forward_list<int> &list,
                      std::forward_list<int>::const_iterator it);


// Test the ReverseList function.
int main() {
    // First test reversing a list of 9 elements.
    std::forward_list<int> test_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::forward_list<int> expected_list{9, 8, 7, 6, 5, 4, 3, 2, 1};

    ReverseList(test_list);

    // Check that the test list elements are now reversed by comparing with
    // the expected list.
    assert(test_list == expected_list);

    // Test that an empty list is handled correctly - no change should be
    // made.
    std::forward_list<int> empty_list;
    ReverseList(empty_list);
    assert(empty_list.empty());

    // Test that a list containing a single element is unchanged.
    std::forward_list<int> singleton{42};
    ReverseList(singleton);
    assert(singleton.front() == 42);

    return 0;
}

// Reverses a forward_list in-place.
void ReverseList(std::forward_list<int> &list) {
    if (!list.empty()) {
        ReverseListRecur(list, list.begin());
    }
}

// Recursive step to reverse a forward_list in-place.
void ReverseListRecur(std::forward_list<int> &list,
                      std::forward_list<int>::const_iterator it) {
    if (it != list.begin()) {
        list.push_front(*it);
    }

    auto next_it = it;
    ++next_it;

    if (next_it != list.end()) {
        ReverseListRecur(list, next_it);
        list.erase_after(it);
    }
}

