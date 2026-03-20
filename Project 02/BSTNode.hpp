//==============================================================
// BSTNode.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This header file defines the BSTNode class template, which represents a 
// node in a binary search tree. The class includes public data members 
// for the node's value and pointers to its left and right children and 
// parent nodes. Additionally, the file provides declarations for constructors, 
// a destructor, and member functions to find the minimum and maximum nodes 
// in the subtree, as well as functions for pre-order, in-order, and post-order 
// traversals.
//==============================================================

#include <iostream>
using namespace std;

#ifndef BSTNODE_HPP
#define BSTNODE_HPP

template <typename T>
class BSTNode {
public:
    //data
    T value;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode<T>* parent;

    // Constructors and destructor
    BSTNode(void);
    BSTNode(const T& val); // Constructor with parameter
    BSTNode(const BSTNode<T>& other); // Copy constructor
    ~BSTNode(void); // Destructor

    //Functions
    BSTNode<T>* treeMin(void);
    BSTNode<T>* treeMax(void);
    void printPreOrderTraversal(void) const;
    void printInOrderTraversal(void) const;
    void printPostOrderTraversal(void) const;

};

#endif


