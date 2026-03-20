//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// RBTree.hpp
// This is the header file with definitions of functions for the RBTreeNode class
//=========================================================
#include <iostream>
using namespace std;

#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

enum Color
{
    RED,
    BLACK
};

template <class T>
class RBTree;

template <class T>
class RBTreeNode
{
public:
    T val;
    RBTreeNode *parent;
    RBTreeNode *left;
    RBTreeNode *right;
    Color color;

public:
    RBTreeNode();
    RBTreeNode(T value);
    RBTreeNode(const RBTreeNode<T> &node);
    ~RBTreeNode();

    RBTreeNode<T> &operator=(const RBTreeNode<T> &node);
    RBTreeNode<T> *treeMin();
    RBTreeNode<T> *treeMax();
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;
    T *value();

    friend class RBTree<T>;
};

#include "RBTreeNode.cpp"

#endif
