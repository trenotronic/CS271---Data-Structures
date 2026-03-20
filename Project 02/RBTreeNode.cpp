//==============================================================
// RBTreeNode.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
//
// Description:
// This implementation file provides the definitions for the functions declared 
// in the RBTreeNode class template. It includes constructors for initializing 
// nodes, including a default constructor, parameterized constructor, and a copy 
// constructor that recursively copies a node and its subtree. Additionally, 
// this file defines a destructor to clean up allocated memory, as well as 
// functions to find the minimum and maximum nodes in a subtree and to perform 
// pre-order, in-order, and post-order traversals for printing the tree's contents.
//==============================================================

#include <iostream>
#include "RBTreeNode.hpp"
#include "customexceptions.hpp"
using namespace std;

//==============================================================
// RBTreeNode
// Default constructor for RBTreeNode. Initializes the node's value to T's default,
// color to BLACK, and pointers to nullptr.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTreeNode<T>::RBTreeNode(void){
    value = T();
    color = BLACK;    // Set default color to BLACK
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

//==============================================================
// RBTreeNode
// Parameterized constructor for RBTreeNode. Initializes the node's value and color
// and pointers to nullptr.
// PARAMETERS:
// - val : const reference to the value of type T to be stored in the node
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTreeNode<T>::RBTreeNode(const T &val){
    value = val;
    color = RED;      // Default new nodes to RED for insertion
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

//==============================================================
// RBTreeNode
// Copy constructor for RBTreeNode. Creates a deep copy of a RBTreeNode and its subtree.
// PARAMETERS:
// - node : const reference to the node of type RBTreeNode<T> to copy
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode<T>& node){
    value = node -> value;
    color = node -> color;
    left = nullptr;
    right = nullptr;
    parent = nullptr;

    if(node.left){
        left = new RBTreeNode<T>(*node.left); 
        left -> parent = this;
    }
    if(node.right){
        right = new RBTreeNode<T>(*node.right); 
        right -> parent = this;
    }
    
}

//==============================================================
// ~RBTreeNode
// Destructor for RBTreeNode. Recursively deletes left and right subtrees.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTreeNode<T>::~RBTreeNode() {
    delete left;
    delete right;
}

//==============================================================
// treeMin
// Finds the minimum value node in the subtree rooted at this node.
// PARAMETERS:
// - None
// RETURN VALUE:
// - Pointer to the node with the smallest value in the subtree
//==============================================================
template <typename T>
RBTreeNode<T>* RBTreeNode<T>::treeMin() {
    RBTreeNode<T>* node = this;
    while (node -> left != nullptr) {
        node = node -> left;
    }
    return node;
}

//==============================================================
// treeMax
// Finds the maximum value node in the subtree rooted at this node.
// PARAMETERS:
// - None
// RETURN VALUE:
// - Pointer to the node with the largest value in the subtree
//==============================================================
template <typename T>
RBTreeNode<T>* RBTreeNode<T>::treeMax() {
    RBTreeNode<T>* node = this;
    while (node -> right != nullptr) {
        node = node -> right;
    }
    return node;
}

//==============================================================
// printPreOrderTraversal
// Prints the values of the nodes in pre-order traversal (Node -> Left -> Right).
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTreeNode<T>::printPreOrderTraversal() const {
    cout << value << " ";
    if(left != nullptr){
        left -> printPreOrderTraversal();
    }
    if(right != nullptr){
        right -> printPreOrderTraversal();
    }
}

//==============================================================
// printInOrderTraversal
// Prints the values of the nodes in in-order traversal (Left -> Node -> Right).
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTreeNode<T>::printInOrderTraversal() const {
    if(left != nullptr){
        left -> printInOrderTraversal();
    }
    cout << value << " ";
    if(right != nullptr){
        right -> printInOrderTraversal();
    }
}

//==============================================================
// printPostOrderTraversal
// Prints the values of the nodes in post-order traversal (Left -> Right -> Node).
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTreeNode<T>::printPostOrderTraversal() const {
    if(left != nullptr){
        left -> printPostOrderTraversal();
    }
    if(right != nullptr){
        right -> printPostOrderTraversal();
    }
    cout << value << " ";
}
