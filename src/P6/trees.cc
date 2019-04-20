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
 */

#include <cassert>
#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>

void TestHeap();
void TestBinarySearch();
void TestInsert();
void TestStats();

// Each node in a binary tree points to up to two child nodes.
template <class T> class BinaryTree {
  public:
    // Constructor.
    explicit BinaryTree(T value) :
        value_(value), left_(nullptr), right_(nullptr) {};

    // Attribute getters and setters.
    BinaryTree<T> *left() const;
    void set_left(T left_val);
    BinaryTree<T> *right() const;
    void set_right(T right_val);
    T value() const;
    void set_value(T new_value);

    // Methods for checking the type of tree.
    bool IsHeap() const;
    bool IsSearchTree() const;

    // Overloaded operators.
    bool operator==(const BinaryTree &other);

  private:
    T value_;
    std::unique_ptr<BinaryTree<T>> left_;
    std::unique_ptr<BinaryTree<T>> right_;
    std::tuple<bool, int, int> IsSearchTreeRecur_() const;
};

// A Binary search tree is a binary tree where every node's value is greater
// than any value in the left subtree and less than any value in the right
// subtree.
template <class T> class BinarySearchTree {
  public:
    // Constructor.
    BinarySearchTree(T value) : tree_root_(value) {};

    // Calculate the modal value.
    T Mode() const;

    // Modifiers.
    void InsertValue(T new_value);

    // Overloaded operators.
    bool operator==(const BinaryTree<T> &other);

  private:
    BinaryTree<T> tree_root_;
    void InsertValueRecur_(T new_value, BinaryTree<T> &node);
    std::tuple<T, int> ModeRecur_(const BinaryTree<T> &node) const;
};

// For binary search trees of ints, add two extra methods for calculating the
// mean and median values.
class IntBinarySearchTree : public BinarySearchTree<int> {
  public:
    // Inherit constructor from parent class.
    using BinarySearchTree<int>::BinarySearchTree;

    // Calculate statistical values.
    double Mean() const;
    int Median() const;
};

// Test the BinaryTree.
int main() {
    TestHeap();
    TestBinarySearch();
    TestInsert();

    std::cout << "All BinaryTree assertions passed." << std::endl;

    return 0;
}

// Test the BinaryTree heap checking.
void TestHeap() {
    BinaryTree<int> test_tree(528);

    // Check that a tree containing a single node is considered to be a heap.
    assert(test_tree.IsHeap());

    // Add a left and right value and assert the tree is still a heap.
    test_tree.set_left(400);
    test_tree.set_right(302);
    assert(test_tree.IsHeap());

    // Add more nodes under left and right and assert the tree is still a heap.
    test_tree.left()->set_left(350);
    test_tree.left()->set_right(392);
    test_tree.right()->set_left(200);
    test_tree.right()->set_right(226);
    assert(test_tree.IsHeap());

    // Add another node which invalidates the heap.
    test_tree.left()->left()->set_left(999);
    assert(!test_tree.IsHeap());
}

// Test the BinaryTree search tree checking.
void TestBinarySearch() {
    BinaryTree<int> test_tree(554);

    // Check that a tree containing a single node is considered to be a valid
    // binary search tree.
    assert(test_tree.IsSearchTree());

    // Add a left and right value and assert the tree is still a valid BST.
    test_tree.set_left(308);
    test_tree.set_right(772);
    assert(test_tree.IsSearchTree());

    // Add more nodes under left and right and assert the tree is still a valid
    // BST.
    test_tree.left()->set_left(128);
    test_tree.left()->set_right(443);
    test_tree.right()->set_left(643);
    test_tree.right()->set_right(875);
    assert(test_tree.IsSearchTree());

    // Add another node to invalidate the search tree.
    test_tree.left()->left()->set_left(999);
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
    expected_tree.set_right(837);
    expected_tree.set_left(321);
    expected_tree.left()->set_right(443);
    expected_tree.right()->set_left(780);
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

// Checks if a binary tree is a heap. A heap is a tree in which every parent
// node has a greater value than its children.
template <class T> bool BinaryTree<T>::IsHeap() const {
    if ((left_ != nullptr) && (right_ != nullptr)) {
        return (value_ > left_->value_) && (left_->IsHeap()) &&
               (value_ > right_->value_) && (right_->IsHeap());
    } else if (left_ != nullptr) {
        return (value_ > left_->value_) && (left_->IsHeap());
    } else if (right_ != nullptr) {
        return (value_ > right_->value_) && (right_->IsHeap());
    } else {
        return true;
    }
}

template <class T> bool BinaryTree<T>::IsSearchTree() const {
    return std::get<0>(IsSearchTreeRecur_());
}

// Recursively check if a tree is valid BST and return the lowest and highest
// values in the tree.
template <class T> std::tuple<bool, int, int>
BinaryTree<T>::IsSearchTreeRecur_() const {
    bool left_is_bst;
    int left_lowest;
    int left_highest;
    bool right_is_bst;
    int right_lowest;
    int right_highest;

    if ((left_ != nullptr) && (right_ != nullptr)) {
        std::tie(left_is_bst, left_lowest, left_highest) =
            left_->IsSearchTreeRecur_();
        std::tie(right_is_bst, right_lowest, right_highest) =
            right_->IsSearchTreeRecur_();

        bool is_bst = (left_is_bst && (left_highest < value_)) &&
                      (right_is_bst && (right_lowest > value_));
        int lowest = std::min({left_lowest, right_lowest, value_});
        int highest = std::max({left_highest, right_highest, value_});
        return std::make_tuple(is_bst, lowest, highest);
    } else if (left_ != nullptr) {
        std::tie(left_is_bst, left_lowest, left_highest) =
            left_->IsSearchTreeRecur_();
        bool is_bst = left_is_bst && left_highest < value_;
        int lowest = std::min(left_lowest, value_);
        int highest = std::max(left_highest, value_);
        return std::make_tuple(is_bst, lowest, highest);
    } else if (right_ != nullptr) {
        std::tie(right_is_bst, right_lowest, right_highest) =
            right_->IsSearchTreeRecur_();
        bool is_bst = right_is_bst && (right_lowest > value_);
        int lowest = std::min(right_lowest, value_);
        int highest = std::max(right_highest, value_);
        return std::make_tuple(is_bst, lowest, highest);
    } else {
        return std::make_tuple(true, value_, value_);
    }
}

// Get methods for left and right sub-trees. The raw pointers are returned.
template <class T> BinaryTree<T> *BinaryTree<T>::left() const {
    return left_.get();
}

template <class T> BinaryTree<T> *BinaryTree<T>::right() const {
    return right_.get();
}

// Set methods for left and right sub-trees.
template <class T> void BinaryTree<T>::set_left(T left_val) {
    if (left_ == nullptr) {
        left_ = std::make_unique<BinaryTree<T>>(left_val);
    } else {
        left_->value_ = left_val;
    }
}

template <class T> void BinaryTree<T>::set_right(T right_val) {
    if (right_ == nullptr) {
        right_ = std::make_unique<BinaryTree<T>>(right_val);
    } else {
        right_->value_ = right_val;
    }
}

// Get and set methods for the node value.
template <class T> T BinaryTree<T>::value() const {
    return value_;
}

template <class T> void BinaryTree<T>::set_value(T new_value) {
    value_ = new_value;
}

// Check that two trees are equal: they contain the same values in the
// same positions.
template <class T> bool BinaryTree<T>::operator==(const BinaryTree &other) {
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

// Insert a value into the correct position in this binary search tree.
template <class T> void BinarySearchTree<T>::InsertValue(T new_value) {
    InsertValueRecur_(new_value, tree_root_);
}

template <class T> void BinarySearchTree<T>::InsertValueRecur_(
        T new_value, BinaryTree<T> &node) {
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

template <class T> bool
BinarySearchTree<T>::operator==(const BinaryTree<T> &other) {
    return tree_root_ == other;
}

// Calculate the mode of values in a binary search tree.
template <class T> T BinarySearchTree<T>::Mode() const {
    return std::get<0>(ModeRecur_(tree_root_));
}

// Recursive method to calculate the modal value and the number of times it
// appears in a binary search tree under a given node.
template <class T> std::tuple<T, int>
BinarySearchTree<T>::ModeRecur_(const BinaryTree<T> &node) const {
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

