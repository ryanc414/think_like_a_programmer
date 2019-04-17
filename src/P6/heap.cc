/*
 * 6-9. Some words in programming have more than one common meaning. In
 * Chapter 4, we learned about the heap, from which we get memory allocated
 * with new. The term heap also describes a binary tree in which each node value
 * is higher than any in the left or right subtree. Write a recursive function to
 * determine whether a binary tree is a heap.
 */

#include <cassert>
#include <iostream>
#include <memory>

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

    // Checks if the tree is a heap.
    bool IsHeap() const;

  private:
    T value_;
    std::unique_ptr<BinaryTree<T>> left_;
    std::unique_ptr<BinaryTree<T>> right_;
};

// Test the BinaryTree heap checking.
int main() {
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

    std::cout << "All heap assertions passed." << std::endl;

    return 0;
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

