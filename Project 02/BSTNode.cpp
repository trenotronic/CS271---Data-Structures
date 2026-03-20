//==============================================================
// BSTNode.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This file contains the implementation of the BSTNode class template,
// which represents a node in a binary search tree. The class includes
// constructors for initializing nodes, a destructor for managing memory,
// and member functions for finding the minimum and maximum nodes, as well
// as printing the tree in pre-order, in-order, and post-order traversals.
//==============================================================

#include <iostream>
#include "BSTNode.hpp"
#include "customexceptions.hpp"
using namespace std;

//==============================================================
// BSTNode
// Default constructor for BSTNode. Initializes the node's value to 0 and pointers to nullptr.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BSTNode<T>::BSTNode(void){
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

//==============================================================
// BSTNode
// Parameterized constructor for BSTNode. Initializes the node's value to the given value
// and pointers to nullptr.
// PARAMETERS:
// - val : const reference to the value of type T to be stored in the node
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BSTNode<T>::BSTNode(const T &val){
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

//==============================================================
// BSTNode
// Copy constructor for BSTNode. Creates a deep copy of a BSTNode and its subtree.
// PARAMETERS:
// - node : const reference to the node of type BSTNode<T> to copy
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T>& node){
    value = node -> value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;

    if(node.left){
        left = new BSTNode<T>(*node.left); 
        left -> parent = this;
    }
    if(node.right){
        right = new BSTNode<T>(*node.right); 
        right -> parent = this;
    }
    
}

//==============================================================
// ~BSTNode
// Destructor for BSTNode. Recursively deletes left and right subtrees.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BSTNode<T>::~BSTNode() {
    left = nullptr;
    right = nullptr;
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
BSTNode<T>* BSTNode<T>::treeMin() {
    BSTNode<T>* node = this;
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
BSTNode<T>* BSTNode<T>::treeMax() {
    BSTNode<T>* node = this;
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
void BSTNode<T>::printPreOrderTraversal() const {
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
void BSTNode<T>::printInOrderTraversal() const {
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
void BSTNode<T>::printPostOrderTraversal() const {
    if(left != nullptr){
        left -> printPostOrderTraversal();
    }
    if(right != nullptr){
        right -> printPostOrderTraversal();
    }
    cout << value << " ";
}
