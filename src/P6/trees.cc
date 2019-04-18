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
 */

#include <cassert>
#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>

void TestHeap();
void TestBinarySearch();

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

    bool IsHeap() const;
    bool IsSearchTree() const;

  private:
    T value_;
    std::unique_ptr<BinaryTree<T>> left_;
    std::unique_ptr<BinaryTree<T>> right_;

    std::tuple<bool, int, int> IsSearchTreeRecur_() const;
};

// Test the BinaryTree.
int main() {
    TestHeap();
    TestBinarySearch();

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
        bool is_bst = right_is_bst && (right_lowest < value_);
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
        left_ = std::make_unique<BinaryTree<T>>(BinaryTree<T>(left_val));
    } else {
        left_->value_ = left_val;
    }
}

template <class T> void BinaryTree<T>::set_right(T right_val) {
    if (right_ == nullptr) {
        right_ = std::make_unique<BinaryTree<T>>(BinaryTree<T>(right_val));
    } else {
        right_->value_ = right_val;
    }
}

