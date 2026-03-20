//==============================================================
// RBTreeNode.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This header file defines the RBTreeNode class template, representing a 
// node in a red-black tree. Each node contains a value, a color (RED or BLACK), 
// and pointers to its left, right, and parent nodes. The class provides constructors, 
// a destructor, and member functions to find the minimum and maximum nodes in 
// the subtree, along with functions for pre-order, in-order, and post-order traversals. 
// The `Color` enum is defined to simplify node color representation.
//==============================================================

#include <iostream>
using namespace std;

#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

// Enum to represent the color of nodes in a red-black tree
enum Color {
    RED,
    BLACK
};

template <typename T>
class RBTreeNode {
public:
    //data
    T value;
    Color color;
    RBTreeNode<T>* left;
    RBTreeNode<T>* right;
    RBTreeNode<T>* parent;

    // Constructors and destructor
    RBTreeNode(void);
    RBTreeNode(const T& val); // Constructor with parameter
    RBTreeNode(const RBTreeNode<T>& other); // Copy constructor
    ~RBTreeNode(void); // Destructor

    //Functions
    RBTreeNode<T>* treeMin(void);
    RBTreeNode<T>* treeMax(void);
    void printPreOrderTraversal(void) const;
    void printInOrderTraversal(void) const;
    void printPostOrderTraversal(void) const;

};

#endif


