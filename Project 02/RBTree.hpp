//==============================================================
// RBTree.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This header file defines the RBT class template, which manages a 
// collection of RBTreeNode elements organized according to red black 
// tree properties. The class provides a public interface for typical
// red black tree operations, including insertion, deletion, and 
// searching for nodes by value. In order to maintain the properties
// of red black trees, insert and remove have helper functions that 
// "fix" wrong properties that are inevitably created during such operations.
// It also includes methods for tree traversal (pre-order, in-order, 
// and post-order), finding the minimum and maximum nodes, and managing 
// tree memory through cloning and transplanting nodes. In addition,
// rotation methods are implemented to aid the "fix" of insertion and deletion
// operations.
//==============================================================

#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "RBTreeNode.cpp"
#include <iostream>
using namespace std;

template <typename T>
class RBTree {
public:
    RBTreeNode<T>* root;
    long nodeCount;

    RBTree(); // Default constructor
    RBTree(const T &val); //constructor
    RBTree(const RBTree<T>& other); // Copy constructor
    ~RBTree(); // Destructor

    RBTreeNode<T>* clone(RBTreeNode<T>* node) const;
    void transplant(RBTreeNode<T>* oldNode, RBTreeNode<T>* newNode);
    bool isEmpty() const;
    long size() const;
    void RBInsertFixup(RBTreeNode<T>* z); // Helper for insert
    RBTreeNode<T>* insert(T value);
    void fixRemove(RBTreeNode<T>* node); // helper for remove
    void remove(T value);
    RBTreeNode<T>* search(T value) const;
    RBTreeNode<T>* treeMin() const;
    RBTreeNode<T>* treeMax() const;
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;

    // Rotation methods
    void leftRotate(RBTreeNode<T>* x);  
    void rightRotate(RBTreeNode<T>* x); 
};

#endif
