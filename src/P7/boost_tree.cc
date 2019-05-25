/*
 * 7-8. Design your own: Take a problem you have already solved, and solve it again
 * using a different component. Remember to analyze the results in comparison to
 * your original solution.
 *
 * Let's re-implement our binary search tree class using the Boost Graph
 * Library classes to represent the nodes and vertices.
 */
#include <cassert>
#include <boost/config.hpp>
#include <iostream>
#include <optional>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/property_map/property_map.hpp>


// Implementation of a basic binary search tree using the boost Graph library.
// Allows key-value pairs to be inserted and later retrieved. Does not perform
// any clever balancing for optimization.
//
// Currently hardcodes a mapping of int -> string: TODO add template params to
// generalise.
class BinarySearchTree {
  public:
    BinarySearchTree() = default;
    void InsertValue(int key, std::string value);
    const std::string *RetrieveValue(int key) const;

  private:
    struct VertexProperties {
        int key;
        std::string value;
    };

    enum class ChildType {kLeftChild, kRightChild};

    struct EdgeProperties {
        ChildType child_type;
    };

    typedef boost::adjacency_list<boost::vecS,
                                  boost::listS,
                                  boost::directedS,
                                  VertexProperties,
                                  EdgeProperties> Graph;
    Graph tree_;
    std::optional<Graph::vertex_descriptor> root_;

    void InsertValueRecur_(Graph::vertex_descriptor node,
                           const VertexProperties &vp);
    const std::string *
    RetrieveValueRecur_(Graph::vertex_descriptor node, int key) const;
};

int main() {
    BinarySearchTree test_tree;

    // Check that retrieving a value from an empty tree returns nullptr.
    assert(test_tree.RetrieveValue(123) == nullptr);

    // Insert some values.
    test_tree.InsertValue(482, "Alice");
    test_tree.InsertValue(837, "Bob");
    test_tree.InsertValue(321, "Charlie");
    test_tree.InsertValue(443, "David");
    test_tree.InsertValue(780, "Emily");

    // Check that the values can be retrieved.
    assert(*test_tree.RetrieveValue(482) == "Alice");
    assert(*test_tree.RetrieveValue(837) == "Bob");
    assert(*test_tree.RetrieveValue(321) == "Charlie");
    assert(*test_tree.RetrieveValue(443) == "David");
    assert(*test_tree.RetrieveValue(780) == "Emily");

    // Check that invalid keys return nullptr
    assert(test_tree.RetrieveValue(999) == nullptr);

    std::cout << "All BinarySearchTree assertions passed." << std::endl;

    return 0;
}

// Inserts a new key-value pair into the graph. This will always create a new
// vertex: TODO handle duplicate keys by overwriting old vertice?
void BinarySearchTree::InsertValue(int key, const std::string value) {
    VertexProperties vp{key, value};

    if (!root_) {
        root_ = boost::add_vertex(vp, tree_);
    } else {
        InsertValueRecur_(*root_, vp);
    }
}

// Recursive implementation for inserting a key-value pair into the tree.
// For each node, compare the key to the one we are inserting and decide
// whether to insert it under the left- or right- subtree.
void BinarySearchTree::InsertValueRecur_(Graph::vertex_descriptor node,
                                         const VertexProperties &vp) {
    Graph::out_edge_iterator it;
    Graph::out_edge_iterator end;

    auto edge_type_map = get(&EdgeProperties::child_type, tree_);
    auto vertex_key_map = get(&VertexProperties::key, tree_);

    // Iterate through our child nodes to check if we can delegate the insert
    // under one of them.
    for (boost::tie(it, end) = boost::out_edges(node, tree_);
         it != end;
         ++it) {
        auto child_node = boost::target(*it, tree_);

        switch (edge_type_map[*it]) {
            case ChildType::kLeftChild:
                if (vp.key <= vertex_key_map[node]) {
                    InsertValueRecur_(child_node, vp);
                    return;
                }
                break;

            case ChildType::kRightChild:
                if (vp.key > vertex_key_map[node]) {
                    InsertValueRecur_(child_node, vp);
                    return;
                }
                break;

            default:
                throw std::runtime_error("Unexpected edge type");
        }
    }

    // If we get to here then we need to create a new child node. Do some
    // extra checking to ensure we don't ever create two left- or right-
    // children.
    assert(boost::out_degree(node, tree_) < 2);

    if (vp.key <= vertex_key_map[node]) {
        // Sanity check that we don't already have a left child.
        for (boost::tie(it, end) = boost::out_edges(node, tree_);
             it != end;
             ++it) {
            assert(edge_type_map[*it] != ChildType::kLeftChild);
        }

        // Insert a new child vertex and edge connecting it to our current
        // node.
        auto new_child = boost::add_vertex(vp, tree_);
        EdgeProperties ep{ChildType::kLeftChild};
        boost::add_edge(node, new_child, ep, tree_);
    } else {
        // Sanity check that we don't already have a right child.
        for (boost::tie(it, end) = boost::out_edges(node, tree_);
             it != end;
             ++it) {
            assert(edge_type_map[*it] != ChildType::kRightChild);
        }

        // Insert a new child vertex and edge connecting it to our current
        // node.
        auto new_child = boost::add_vertex(vp, tree_);
        EdgeProperties ep{ChildType::kRightChild};
        boost::add_edge(node, new_child, ep, tree_);
    }
}

// Retreives a value for a given key. If the key does not exist, returns
// nullptr.
const std::string *BinarySearchTree::RetrieveValue(int key) const {
    if (!root_) {
        return nullptr;
    }

    return RetrieveValueRecur_(*root_, key);
}


const std::string *BinarySearchTree::RetrieveValueRecur_(
    Graph::vertex_descriptor node, int key) const {
    Graph::out_edge_iterator it;
    Graph::out_edge_iterator end;

    auto edge_type_map = get(&EdgeProperties::child_type, tree_);
    auto vertex_key_map = get(&VertexProperties::key, tree_);
    auto vertex_value_map = get(&VertexProperties::value, tree_);

    if (key == vertex_key_map[node]) {
        return &vertex_value_map[node];
    }


    // Iterate through our child nodes to check if we can search for the vertex
    // under one of them.
    for (boost::tie(it, end) = boost::out_edges(node, tree_);
         it != end;
         ++it) {
        auto child_node = boost::target(*it, tree_);

        switch (edge_type_map[*it]) {
            case ChildType::kLeftChild:
                if (key <= vertex_key_map[node]) {
                    return RetrieveValueRecur_(child_node, key);
                }
                break;

            case ChildType::kRightChild:
                if (key > vertex_key_map[node]) {
                    return RetrieveValueRecur_(child_node, key);
                }
                break;

            default:
                throw std::runtime_error("Unexpected edge type");
        }
    }

    // If we get to here then the node wa not found.
    return nullptr;
}

