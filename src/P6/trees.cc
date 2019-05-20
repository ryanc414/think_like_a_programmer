/*
 * 6-9. Some words in programming have more than one common meaning. In
 * Chapter 4, we learned about the heap, from which we get memory allocated
 * with new. The term heap also describes a binary tree in which each node value
 * is higher than any in the left or right subtree. Write a recursive function to
 * determine whether a binary tree is a heap.
 *
 * 6-10. A binary search tree is a binary tree in which each node value is greater than
 * any value in that node's left subtree but less than any value in the node's
 * right subtree. Write a recursive function to determine whether a binary tree
 * is a binary search tree
 *
 * 6-11. Write a recursive function that is passed a binary search tree's root pointer and
 * a new value to be inserted and that creates a new node with the new value,
 * placing it in the correct location to maintain the binary search tree structure.
 * Hint: Consider making the root pointer parameter a reference parameter.
 *
 * 6-12. Design your own: Consider basic statistical questions you can ask of a set of
 * numerical values, such as average, median, mode, and so forth. Attempt to
 * write recursive functions to compute those statistics for a binary tree of integers.
 * Some are easier to write than others. Why?
 *
 * 7-4. For the problem in 7-3, implement a solution by implementing an abstract
 * data type that allows an arbitrary number of items to be stored and individual
 * records to be retrieved based on a key value. A generic term for a structure
 * that can efficiently store and retrieve items based on a key value is a symbol
 * table, and common implementations of the symbol table idea are hash tables
 * and binary search trees.
 */

#include <cassert>
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <tuple>

#include "student.hh"

void TestHeap();
void TestBinarySearch();
void TestInsert();
void TestStats();
void TestStudentsBST();

// Each node in a binary tree points to up to two child nodes.
template <class T> class BinaryTreeNode {
  public:
    // Constructor.
    explicit BinaryTreeNode(T value) :
        value_(value), left_(nullptr), right_(nullptr) {};

    // Attribute getters and setters.
    BinaryTreeNode<T> *left() const;
    void set_left(T left_val);
    BinaryTreeNode<T> *right() const;
    void set_right(T right_val);
    T value() const;
    void set_value(T new_value);

    // Equality operator.
    bool operator==(const BinaryTreeNode &other);

  private:
    T value_;
    std::unique_ptr<BinaryTreeNode<T>> left_;
    std::unique_ptr<BinaryTreeNode<T>> right_;
};

// A binary tree has a root node which links to other nodes in the tree.
template <class T> class BinaryTree {
  public:
    // Constructor.
    explicit BinaryTree(T value) : root_(value) {};

    // Retrieve the tree root.
    BinaryTreeNode<T> &root();

    // Methods for checking the type of tree.
    bool IsHeap() const;
    bool IsSearchTree() const;

    // Overloaded operators.
    bool operator==(const BinaryTree &other);

  protected:
    BinaryTreeNode<T> root_;

  private:
    bool IsHeapRecur_(const BinaryTreeNode<T> &node) const;
    std::tuple<bool, int, int>
    IsSearchTreeRecur_(const BinaryTreeNode<T> &node) const;
};

// A Binary search tree is a binary tree where every node's value is greater
// than any value in the left subtree and less than any value in the right
// subtree.
template <class T> class BinarySearchTree : public BinaryTree<T> {
  public:
    // Constructor.
    explicit BinarySearchTree(T value) : BinaryTree<T>(value) {};

    // Calculate the modal value.
    T Mode() const;

    // Modifiers.
    void InsertValue(T new_value);

  private:
    void InsertValueRecur_(T new_value, BinaryTreeNode<T> &node);
    std::tuple<T, int> ModeRecur_(const BinaryTreeNode<T> &node) const;

};

// For binary search trees of ints, add two extra methods for calculating the
// mean and median values.
class IntBinarySearchTree : public BinarySearchTree<int> {
  public:
    // Constructor.
    explicit IntBinarySearchTree(int value) : BinarySearchTree<int>(value) {};

    // Calculate statistical values.
    double Mean() const;
    double Median() const;

  private:
    std::tuple<int, int>
    SumAndCount_(const BinaryTreeNode<int> &node) const;
    int ValueAtIndex_(int index) const;
    std::tuple<int, std::optional<int>>
    ValueAtIndexRecur_(const BinaryTreeNode<int> &node, int index) const;
};

// Searchable BST of student records.
class StudentsBST : public BinarySearchTree<StudentRecord> {
  public:
    explicit StudentsBST(const StudentRecord &first_student) :
        BinarySearchTree<StudentRecord>(first_student) {};
    const StudentRecord *Search(int student_id) const;

  private:
    const StudentRecord *
    SearchRecur_(const BinaryTreeNode<StudentRecord> &node,
                 int student_id) const;
};

// Test the above binary tree classes.
int main() {
    TestHeap();
    TestBinarySearch();
    TestInsert();
    TestStats();
    TestStudentsBST();

    std::cout << "All BinaryTree assertions passed." << std::endl;

    return 0;
}

// Test the BinaryTree heap checking.
void TestHeap() {
    BinaryTree<int> test_tree(528);

    // Check that a tree containing a single node is considered to be a heap.
    assert(test_tree.IsHeap());

    // Add a left and right value and assert the tree is still a heap.
    BinaryTreeNode<int> &root = test_tree.root();
    root.set_left(400);
    root.set_right(302);
    assert(test_tree.IsHeap());

    // Add more nodes under left and right and assert the tree is still a heap.
    root.left()->set_left(350);
    root.left()->set_right(392);
    root.right()->set_left(200);
    root.right()->set_right(226);
    assert(test_tree.IsHeap());

    // Add another node which invalidates the heap.
    root.left()->left()->set_left(999);
    assert(!test_tree.IsHeap());
}

// Test the BinaryTree search tree checking.
void TestBinarySearch() {
    BinaryTree<int> test_tree(554);

    // Check that a tree containing a single node is considered to be a valid
    // binary search tree.
    assert(test_tree.IsSearchTree());

    // Add a left and right value and assert the tree is still a valid BST.
    BinaryTreeNode<int> &root = test_tree.root();
    root.set_left(308);
    root.set_right(772);
    assert(test_tree.IsSearchTree());

    // Add more nodes under left and right and assert the tree is still a valid
    // BST.
    root.left()->set_left(128);
    root.left()->set_right(443);
    root.right()->set_left(643);
    root.right()->set_right(875);
    assert(test_tree.IsSearchTree());

    // Add another node to invalidate the search tree.
    root.left()->left()->set_left(999);
    assert(!test_tree.IsSearchTree());
}

// Test inserting values into a binary search tree.
void TestInsert() {
    BinarySearchTree<int> test_tree(482);

    // Insert some values.
    test_tree.InsertValue(837);
    test_tree.InsertValue(321);
    test_tree.InsertValue(443);
    test_tree.InsertValue(780);

    // Build the expected tree explicitly.
    BinaryTree<int> expected_tree(482);
    BinaryTreeNode<int> &root = expected_tree.root();

    root.set_right(837);
    root.set_left(321);
    root.left()->set_right(443);
    root.right()->set_left(780);
    assert(expected_tree.IsSearchTree());

    // Compare the test tree built from inserting values to the expected one.
    assert(test_tree == expected_tree);
}

// Test calculating statistical data for a binary search tree of ints.
void TestStats() {
    IntBinarySearchTree test_tree(532);

    test_tree.InsertValue(213);
    test_tree.InsertValue(334);
    test_tree.InsertValue(920);
    test_tree.InsertValue(732);
    test_tree.InsertValue(334);
    test_tree.InsertValue(565);

    const double kExpectedMean = static_cast<double>(
        532 + 213 + 334 + 920 + 732 + 334 + 565) / 7.0;
    const int kExpectedMedian = 532;
    const int kExpectedMode = 334;

    assert(test_tree.Mean() == kExpectedMean);
    assert(test_tree.Median() == kExpectedMedian);
    assert(test_tree.Mode() == kExpectedMode);
}

// Test the StudentsBST object.
void TestStudentsBST() {
    // Build a BST containing 10 students.
    StudentsBST students(StudentRecord(43, 66, "Alice"));

    students.InsertValue(StudentRecord(23, 73, "Bob"));
    students.InsertValue(StudentRecord(33, 83, "Carlie"));
    students.InsertValue(StudentRecord(41, 92, "David"));
    students.InsertValue(StudentRecord(72, 88, "Emily"));
    students.InsertValue(StudentRecord(54, 62, "Frank"));
    students.InsertValue(StudentRecord(66, 79, "Gregory"));
    students.InsertValue(StudentRecord(21, 62, "Henrietta"));
    students.InsertValue(StudentRecord(16, 52, "Isaac"));
    students.InsertValue(StudentRecord(57, 80, "Jessica"));

    // Search for the student with ID 41.
    const StudentRecord *found_student = students.Search(41);
    assert(found_student != nullptr);
    assert(found_student->number == 41);
    assert(found_student->grade == 92);
    assert(found_student->name == "David");

    // Try searching for a student with a non-existent ID - nullptr should
    // be returned.
    assert(students.Search(50) == nullptr);

    std::cout << "All student BST assertions passed." << std::endl;
}

// Get methods for left and right child nodes. The raw pointers are returned.
template <class T> BinaryTreeNode<T> *BinaryTreeNode<T>::left() const {
    return left_.get();
}

template <class T> BinaryTreeNode<T> *BinaryTreeNode<T>::right() const {
    return right_.get();
}

// Set methods for left and right sub-trees.
template <class T> void BinaryTreeNode<T>::set_left(T left_val) {
    if (left_ == nullptr) {
        left_ = std::make_unique<BinaryTreeNode<T>>(left_val);
    } else {
        left_->value_ = left_val;
    }
}

template <class T> void BinaryTreeNode<T>::set_right(T right_val) {
    if (right_ == nullptr) {
        right_ = std::make_unique<BinaryTreeNode<T>>(right_val);
    } else {
        right_->value_ = right_val;
    }
}

// Get and set methods for the node value.
template <class T> T BinaryTreeNode<T>::value() const {
    return value_;
}

template <class T> void BinaryTreeNode<T>::set_value(T new_value) {
    value_ = new_value;
}

// Check that two nodes are equal: they have the same value and their left and
// right child nodes are equal.
template <class T> bool
BinaryTreeNode<T>::operator==(const BinaryTreeNode &other) {
    if ((left_ != nullptr) && (right_ != nullptr)) {
        if ((other.left_ == nullptr) || (other.right_ == nullptr)) {
            return false;
        } else {
            return (value_ == other.value_) &&
                   (*left_ == *other.left_) &&
                   (*right_ == *other.right_);
        }
    } else if (left_ != nullptr) {
        if ((other.left_ == nullptr) || (other.right_ != nullptr)) {
            return false;
        } else {
            return (value_ == other.value_) && (*left_ == *other.left_);
        }
    } else if (right_ != nullptr) {
        if ((other.left_ != nullptr) || (other.right_ == nullptr)) {
            return false;
        } else {
            return (value_ == other.value_) && (*right_ == *other.right_);
        }
    } else {
        if ((other.left_ != nullptr) || (other.right_ != nullptr)) {
            return false;
        } else {
            return value_ == other.value_;
        }
    }
}

// Retrieves the root node of the binary tree.
template <class T> BinaryTreeNode<T> &BinaryTree<T>::root() {
    return root_;
}

// Checks if a binary tree is a heap. A heap is a tree in which every parent
// node has a greater value than its children.
template <class T> bool BinaryTree<T>::IsHeap() const {
    return IsHeapRecur_(root_);
}

// Recursive implementation for checking if a tree is a heap. A tree is a heap
// if its root node is greater than the values of each of its left and right
// children and if the sub-trees of its children are also heaps.
template <class T> bool
BinaryTree<T>::IsHeapRecur_(const BinaryTreeNode<T> &node) const {
    if ((node.left() != nullptr) && (node.right() != nullptr)) {
        return (node.value() > node.left()->value()) &&
               IsHeapRecur_(*node.left()) &&
               (node.value() > node.right()->value()) &&
               IsHeapRecur_(*node.right());
    } else if (node.left() != nullptr) {
        return (node.value() > node.left()->value()) &&
               (IsHeapRecur_(*node.right()));
    } else if (node.right() != nullptr) {
        return (node.value() > node.right()->value()) &&
               (IsHeapRecur_(*node.left()));
    } else {
        return true;
    }
}

template <class T> bool BinaryTree<T>::IsSearchTree() const {
    return std::get<0>(IsSearchTreeRecur_(root_));
}

// Recursively check if a tree is valid BST and return the lowest and highest
// values in the tree.
template <class T> std::tuple<bool, int, int>
BinaryTree<T>::IsSearchTreeRecur_(const BinaryTreeNode<T> &node) const {
    bool left_is_bst;
    int left_lowest;
    int left_highest;
    bool right_is_bst;
    int right_lowest;
    int right_highest;

    if ((node.left() != nullptr) && (node.right() != nullptr)) {
        std::tie(left_is_bst, left_lowest, left_highest) =
            IsSearchTreeRecur_(*node.left());
        std::tie(right_is_bst, right_lowest, right_highest) =
            IsSearchTreeRecur_(*node.right());

        bool is_bst = (left_is_bst && (left_highest < node.value())) &&
                      (right_is_bst && (right_lowest > node.value()));
        int lowest = std::min({left_lowest, right_lowest, node.value()});
        int highest = std::max({left_highest, right_highest, node.value()});
        return std::make_tuple(is_bst, lowest, highest);
    } else if (node.left() != nullptr) {
        std::tie(left_is_bst, left_lowest, left_highest) =
            IsSearchTreeRecur_(*node.left());
        bool is_bst = left_is_bst && left_highest < node.value();
        int lowest = std::min(left_lowest, node.value());
        int highest = std::max(left_highest, node.value());
        return std::make_tuple(is_bst, lowest, highest);
    } else if (node.right() != nullptr) {
        std::tie(right_is_bst, right_lowest, right_highest) =
            IsSearchTreeRecur_(*node.right());
        bool is_bst = right_is_bst && (right_lowest > node.value());
        int lowest = std::min(right_lowest, node.value());
        int highest = std::max(right_highest, node.value());
        return std::make_tuple(is_bst, lowest, highest);
    } else {
        return std::make_tuple(true, node.value(), node.value());
    }
}

// Check if two binary trees are equal by recursively comparing from the root
// node.
template <class T> bool BinaryTree<T>::operator==(const BinaryTree<T> &other) {
    return root_ == other.root_;
}

// Insert a value into the correct position in this binary search tree.
template <class T> void BinarySearchTree<T>::InsertValue(T new_value) {
    InsertValueRecur_(new_value, this->root_);
}

template <class T> void BinarySearchTree<T>::InsertValueRecur_(
        T new_value, BinaryTreeNode<T> &node) {
    if (new_value > node.value()) {
        if (node.right() == nullptr) {
            node.set_right(new_value);
        } else {
            InsertValueRecur_(new_value, *node.right());
        }
    } else {
        if (node.left() == nullptr) {
            node.set_left(new_value);
        } else {
            InsertValueRecur_(new_value, *node.left());
        }
    }
}

// Calculate the mode of values in a binary search tree.
template <class T> T BinarySearchTree<T>::Mode() const {
    return std::get<0>(ModeRecur_(this->root_));
}

// Recursive method to calculate the modal value and the number of times it
// appears in a binary search tree under a given node.
template <class T> std::tuple<T, int>
BinarySearchTree<T>::ModeRecur_(const BinaryTreeNode<T> &node) const {
    T left_mode;
    int left_modal_count;
    T right_mode;
    int right_modal_count;

    if ((node.left() != nullptr) && (node.right() != nullptr)) {
        std::tie(left_mode, left_modal_count) = ModeRecur_(*node.left());
        std::tie(right_mode, right_modal_count) = ModeRecur_(*node.right());

        if (left_mode == node.value()) {
            ++left_modal_count;
        } else if (right_mode == node.value()) {
            ++right_modal_count;
        }

        if (left_modal_count > right_modal_count) {
            return std::make_tuple(left_mode, left_modal_count);
        } else if (right_modal_count > left_modal_count) {
            return std::make_tuple(right_mode, right_modal_count);
        } else {
            return std::make_tuple(0, 0);
        }
    } else if (node.left() != nullptr) {
        std::tie(left_mode, left_modal_count) = ModeRecur_(*node.left());

        if (left_mode == node.value()) {
            ++left_modal_count;
        }

        return std::make_tuple(left_mode, left_modal_count);
    } else if (node.right() != nullptr) {
        std::tie(right_mode, right_modal_count) = ModeRecur_(*node.right());

        if (right_mode == node.value()) {
            ++right_modal_count;
        }

        return std::make_tuple(right_mode, right_modal_count);
    } else {
        return std::make_tuple(node.value(), 1);
    }
}

// Calculate the mean of all values in a binary tree.
double IntBinarySearchTree::Mean() const {
    int sum;
    int num_values;

    std::tie(sum, num_values) = SumAndCount_(this->root_);

    return static_cast<double>(sum) / static_cast<double>(num_values);
}

// Recursively calculate the sum and count of values under each node in the
// tree, so that the mean can be calculated.
std::tuple<int, int>
IntBinarySearchTree::SumAndCount_(const BinaryTreeNode<int> &node) const {
    int left_sum;
    int left_count;
    int right_sum;
    int right_count;

    if ((node.left() != nullptr) && (node.right() != nullptr)) {
        std::tie(left_sum, left_count) = SumAndCount_(*node.left());
        std::tie(right_sum, right_count) = SumAndCount_(*node.right());
        return std::make_tuple(left_sum + right_sum + node.value(),
                               left_count + right_count + 1);
    } else if (node.left() != nullptr) {
        std::tie(left_sum, left_count) = SumAndCount_(*node.left());
        return std::make_tuple(left_sum + node.value(), left_count + 1);
    } else if (node.right() != nullptr) {
        std::tie(right_sum, right_count) = SumAndCount_(*node.right());
        return std::make_tuple(right_sum + node.value(), right_count + 1);
    } else {
        return std::make_tuple(node.value(), 1);
    }
}

// Calculate the median value in a binary search tree of ints.
double IntBinarySearchTree::Median() const {
    int count = std::get<1>(SumAndCount_(this->root_));
    if (count % 2 == 0) {
        return static_cast<double>(ValueAtIndex_((count / 2) - 1)) /
               static_cast<double>(ValueAtIndex_(count / 2));
    } else {
        return static_cast<double>(ValueAtIndex_(count / 2));
    }
}

// Get a value at a specified index in the ordering of values in a BST.
int
IntBinarySearchTree::ValueAtIndex_(int index) const {
    std::optional<int> found_value = std::get<1>(ValueAtIndexRecur_(
        this->root_, index));
    if (found_value) {
        return *found_value;
    } else {
        throw std::out_of_range("No value was found.");
    }
}

// Recursively traverse a binary search tree to find a value at a given index
// in the ordering under this node. A tuple containing the number of nodes
// searched and an optional found value is returned. If fewer nodes were found
// than required to reach the index then the optional will be returned empty.
std::tuple<int, std::optional<int>>
IntBinarySearchTree::ValueAtIndexRecur_(const BinaryTreeNode<int> &node,
                                        int index) const {
    int left_search_count = 0;
    int right_search_count = 0;
    std::optional<int> found_value;

    if (index < 0) {
        throw std::out_of_range("Index cannot be negative.");
    }

    if (node.left() != nullptr) {
        std::tie(left_search_count, found_value) = ValueAtIndexRecur_(
            *node.left(), index);
        if (found_value) {
            return std::make_tuple(left_search_count, found_value);
        }
    }

    if (left_search_count == index) {
        return std::make_tuple(left_search_count + 1, node.value());
    }

    if (node.right() != nullptr) {
        std::tie(right_search_count, found_value) = ValueAtIndexRecur_(
            *node.right(), index - left_search_count - 1);
        return std::make_tuple(left_search_count + 1 + right_search_count,
                               found_value);
    }

    return std::make_tuple(left_search_count + 1, std::nullopt);
}

// Compare student records by their ID number for ordering.
bool StudentRecord::operator<(const StudentRecord &other) const {
    return number < other.number;
}

bool StudentRecord::operator>(const StudentRecord &other) const {
    return number > other.number;
}

// Search for a student in the BST by its ID.
const StudentRecord *StudentsBST::Search(int student_id) const {
    return SearchRecur_(this->root_, student_id);
}

// Recursively search for a student with a given ID.
const StudentRecord *
StudentsBST::SearchRecur_(const BinaryTreeNode<StudentRecord> &node,
                          int student_id) const {
    const StudentRecord &student = node.value();

    if (student.number == student_id) {
        return &student;
    } else if ((student_id < student.number) && (node.left() != nullptr)) {
        return SearchRecur_(*node.left(), student_id);
    } else if ((student_id > student.number) && (node.right() != nullptr)) {
        return SearchRecur_(*node.right(), student_id);
    } else {
        return nullptr;
    }
}

