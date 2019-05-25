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
// Types for keys and values can be specified via the template parameters.
template <class K, class V> class BinarySearchTree {
  public:
    BinarySearchTree();
    void InsertValue(K key, V value);
    const V *RetrieveValue(K key) const;
    size_t Size() const;

  private:
    // Define the type of our graph. It is a directed graph. Each vertex
    // has a key and value as properties and each edge is either a left- or
    // right- edge from the point of view of its source vertex.
    struct VertexProperties {
        K key;
        V value;
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

    // Store the root vertex for ease of access. This vertex isn't created
    // until the first value is added so we make it an optional type.
    std::optional<typename Graph::vertex_descriptor> root_;

    // Define property map objects - these are required to retrieve the
    // properties of vertices and edges.
    typename boost::property_map<Graph, K VertexProperties::*>::type
    vertex_key_map_;

    typename boost::property_map<Graph, V VertexProperties::*>::type
    vertex_value_map_;

    typename boost::property_map<Graph, ChildType EdgeProperties::*>::type
    edge_type_map_;

    // Recursive implementations for inserting and retrieving values from
    // the tree.
    void InsertValueRecur_(typename Graph::vertex_descriptor node,
                           const VertexProperties &vp);
    const V *
    RetrieveValueRecur_(typename Graph::vertex_descriptor node, K key) const;
};

int main() {
    BinarySearchTree<int, std::string> test_tree;

    // Check that retrieving a value from an empty tree returns nullptr.
    assert(test_tree.RetrieveValue(123) == nullptr);
    assert(test_tree.Size() == 0);

    // Insert some values.
    test_tree.InsertValue(482, "Alice");
    test_tree.InsertValue(837, "Bob");
    test_tree.InsertValue(321, "Charlie");
    test_tree.InsertValue(443, "David");
    test_tree.InsertValue(780, "Emily");
    assert(test_tree.Size() == 5);

    // Check that the values can be retrieved.
    assert(*test_tree.RetrieveValue(482) == "Alice");
    assert(*test_tree.RetrieveValue(837) == "Bob");
    assert(*test_tree.RetrieveValue(321) == "Charlie");
    assert(*test_tree.RetrieveValue(443) == "David");
    assert(*test_tree.RetrieveValue(780) == "Emily");

    // Check that invalid keys return nullptr
    assert(test_tree.RetrieveValue(999) == nullptr);

    // Try to update an existing key's value. The tree size should be
    // unchanged.
    test_tree.InsertValue(321, "Chantelle");
    assert(test_tree.Size() == 5);
    assert(*test_tree.RetrieveValue(321) == "Chantelle");

    std::cout << "All BinarySearchTree assertions passed." << std::endl;

    return 0;
}

// Constructor. Initialise the property getter objects.
template <class K, class V> BinarySearchTree<K, V>::BinarySearchTree() :
        tree_(), root_() {
    edge_type_map_ = boost::get(&EdgeProperties::child_type, tree_);
    vertex_key_map_ = boost::get(&VertexProperties::key, tree_);
    vertex_value_map_ = boost::get(&VertexProperties::value, tree_);
}

// Inserts a new key-value pair into the graph. If the key is already in the
// graph, updates its value intead of creating a duplicate pair.
template <class K, class V> void
BinarySearchTree<K, V>::InsertValue(K key, const V value) {
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
template <class K, class V> void
BinarySearchTree<K, V>::InsertValueRecur_(
        typename Graph::vertex_descriptor node,
        const VertexProperties &vp) {
    typename Graph::out_edge_iterator it;
    typename Graph::out_edge_iterator end;

    if (vp.key == vertex_key_map_[node]) {
        vertex_value_map_[node] = vp.value;
        return;
    }

    // Iterate through our child nodes to check if we can delegate the insert
    // under one of them.
    for (boost::tie(it, end) = boost::out_edges(node, tree_);
         it != end;
         ++it) {
        auto child_node = boost::target(*it, tree_);

        switch (edge_type_map_[*it]) {
            case ChildType::kLeftChild:
                if (vp.key <= vertex_key_map_[node]) {
                    InsertValueRecur_(child_node, vp);
                    return;
                }
                break;

            case ChildType::kRightChild:
                if (vp.key > vertex_key_map_[node]) {
                    InsertValueRecur_(child_node, vp);
                    return;
                }
                break;

            default:
                throw std::runtime_error("Unexpected edge type");
        }
    }

    // If we get to here then we need to create a new child node on our
    // current node.
    assert(boost::out_degree(node, tree_) < 2);

    if (vp.key <= vertex_key_map_[node]) {
        // Insert a new child vertex and edge connecting it to our current
        // node.
        auto new_child = boost::add_vertex(vp, tree_);
        EdgeProperties ep{ChildType::kLeftChild};
        boost::add_edge(node, new_child, ep, tree_);
    } else {
        // Insert a new child vertex and edge connecting it to our current
        // node.
        auto new_child = boost::add_vertex(vp, tree_);
        EdgeProperties ep{ChildType::kRightChild};
        boost::add_edge(node, new_child, ep, tree_);
    }
}

// Retreives a value for a given key. If the key does not exist, returns
// nullptr.
template <class K, class V> const V *
BinarySearchTree<K, V>::RetrieveValue(K key) const {
    if (!root_) {
        return nullptr;
    }

    return RetrieveValueRecur_(*root_, key);
}

// Recursive implementation for retrieving a value from the tree corresponding
// to a given key.
template <class K, class V> const V *
BinarySearchTree<K, V>::RetrieveValueRecur_(
       typename Graph::vertex_descriptor node, K key) const {
    typename Graph::out_edge_iterator it;
    typename Graph::out_edge_iterator end;

    if (key == vertex_key_map_[node]) {
        return &vertex_value_map_[node];
    }


    // Iterate through our child nodes to check if we can search for the vertex
    // under one of them.
    for (boost::tie(it, end) = boost::out_edges(node, tree_);
         it != end;
         ++it) {
        auto child_node = boost::target(*it, tree_);

        switch (edge_type_map_[*it]) {
            case ChildType::kLeftChild:
                if (key <= vertex_key_map_[node]) {
                    return RetrieveValueRecur_(child_node, key);
                }
                break;

            case ChildType::kRightChild:
                if (key > vertex_key_map_[node]) {
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

// Return the number of vertices in the tree.
template <class K, class V> size_t BinarySearchTree<K, V>::Size() const {
    return static_cast<size_t>(boost::num_vertices(tree_));
}

