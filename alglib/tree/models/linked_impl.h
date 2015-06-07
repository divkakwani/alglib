/*
 * This file is part of the alglib project.
 *
 * (c) Divyanshu Kakwani <divkakwani@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#include <memory>
#include <vector>

#pragma once

/** 
 * \brief A generic tree data structre
 *
 * A node of a tree is defined as, 
 *      Node = (Key, L, R)
 * where L = left subtree and R = right subtree projecting from the node.
 * A tree is identified by a special node, called the root node. Hence, to represent
 * a tree, we just label one node as the root and then the tree is defined recursively.
 * For efficient implementation, an extra field, parent, is added to each node.
 *
 * This class is a general and highly unconstrained tree. It only maintains the parent-child
 * relationship amongst the nodes; No other property is maintained. This class is thus little 
 * useful for any kind of work when used as is. It, however, serves as a basic building block
 * of other more sophosticated trees. Those tree classes can be built by providing richer 
 * interfaces, functiponality and, if required, by imposing certain additional constraints on the
 * nodes of the tree, the maintenance of which is the responsibility of the class itself.
 *
 * Responsibilty: Manage nodes; provide interfaces to establish and alter parent-child
 * relationships amongst the nodes maintaining consistency; allow inspection of the tree via
 * iterators.
 *
 * Managing Nodes: To create new nodes, one can simply use the new operator. They are initially 
 * created as independent nodes. The owner of the node is the one who created it. Hence, releasing
 * it is the responsibility of the user.
 * If automatic node management is required, the user can create new nodes and while attaching it
 * to a tree, the ownership of the node is passed to its parent. This would ensure that once a node
 * has no parent, it, alongwith the tree rooted at that node, is released recursively.
 *
 * Altering parent-child relationships: The parent-child relationships can be altered simply by
 * updating the nodes' pointers. Since the tree class is unaware of _any_ relationship information,
 * merely updating the nodes' pointers suffices.
 * As for maintaining consistency, it can be proven that by allowing a node to have atmost one
 * parent, the 'tree' object always represents some valid tree.(with the same root?)
 *
 * Tree Inspection: Three modes of inspection - preorder, postorder and inorder tranversals are
 * provided by the corresponding iterators. Any other arbitrary mode of iteration can be achieved
 * by writing your own iterators.
 *
 */

// Forward declaration
template<typename value_t> class Tree;

template<typename value_t>
struct Node {

    typedef value_t value_type;

    // Shared - because a node can be a parent to many nodes.
    std::shared_ptr<Node> parent;
    
    value_type val;

    // Unique - because every subtree has a unique parent
    std::vector<std::unique_ptr<Tree<value_t>>> subtrees;

    /// Construct a node, given the value associated with the node, references to its parent
    /// and subtrees
    Node(const value_type& value) {
        val = value;
        parent = 0;
        // Keep the subtrees list empty
    }

    Tree<value_type>& get_ith_subtree(int i) {}
    void set_ith_subtree(Tree<value_type>& T, int i) {}

    value_type get_val() {}
    void set_val(const value_type& value) {}

    Node<value_type>& get_parent() {}
    void set_parent(Node<value_type>* root_node) {}

};    

template<typename value_t>
struct Tree {
 
 public:
    typedef value_t value_type;

    Node<value_type>& root;

    explicit Tree(const Node<value_type>& root_node) : root(root_node) {}
    
    // Iterators
    class PostIter;
    class PreIter;
    class InIter;

    // Inspection of the tree
    PreIter prebegin() const {}                                                                     
    PreIter preend() const {}                                                                       
    InIter inbegin() const {}                                                                       
    InIter inend() const {}                                                                            
    PostIter postbegin() const {}
    PostIter postend() const {}
};

// Node n(3);
// Tree T(n);
// Tree.root.set_ith_subtree(a tree or a node)


