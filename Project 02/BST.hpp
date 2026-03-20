//==============================================================
// BST.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This header file defines the BST class template, which manages a 
// collection of BSTNode elements organized according to binary search 
// tree properties. The class provides a public interface for typical
// binary search tree operations, including insertion, deletion, and 
// searching for nodes by value. It also includes methods for tree 
// traversal (pre-order, in-order, and post-order), finding the minimum 
// and maximum nodes, and managing tree memory through cloning and 
// transplanting nodes.
//==============================================================

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.cpp"
#include <iostream>
using namespace std;

template <typename T>
class BST {
public:
    BSTNode<T>* root;
    long nodeCount;

    BST(); // Default constructor
    BST(const T &val); //constructor
    BST(const BST<T>& other); // Copy constructor
    ~BST(); // Destructor

    BSTNode<T>* clone(BSTNode<T>* node) const;
    void transplant(BSTNode<T>* oldNode, BSTNode<T>* newNode);
    bool isEmpty() const;
    long size() const;
    BSTNode<T>* insert(T value);
    void remove(T value);
    BSTNode<T>* search(T value) const;
    BSTNode<T>* treeMin() const;
    BSTNode<T>* treeMax() const;
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;
};

#endif
