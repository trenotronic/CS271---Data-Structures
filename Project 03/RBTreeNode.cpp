//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// RBTreeNode.cpp
// This file contains the implementations of the red-black tree node functions
//========================================================
#include <iostream>
#include "RBTreeNode.hpp"


/**
 * @brief Construct a new RBTreeNode<T>::RBTreeNode object
 * 
 * @tparam T: templated RBTreeNode data class
 */
template <class T>
RBTreeNode<T>::RBTreeNode()
{
    val = T();
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = BLACK;
}

/**
 * @brief Construct a new RBTreeNode<T>::RBTreeNode object
 * 
 * @tparam T: templated RBTreeNode data class
 * @param value: value of the node
 */
template <class T>
RBTreeNode<T>::RBTreeNode(T value)
{
    val = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

/**
 * @brief Construct a new RBTreeNode<T>::RBTreeNode object
 * 
 * @tparam T: templated RBTreeNode data class
 * @param node: value of the node 
 */
template <class T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode<T> &node)
{
    val = node.val;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = node.color;
}

/**
 * @brief Destroy the RBTreeNode<T>::RBTreeNode object
 * 
 * @tparam T: templated RBTreeNode data class
 */
template <class T>
RBTreeNode<T>::~RBTreeNode(void){};

/**
 * @brief Assignment operator overload
 * 
 * @tparam T: templated RBTreeNode data class
 * @param node: node to be copied
 * @return RBTreeNode<T>&: the node copied from the parameter
 */
template <class T>
RBTreeNode<T> &RBTreeNode<T>::operator=(const RBTreeNode<T> &node)
{
    if (this == &node)
    {
        return *this;
    }
    val = node.val;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = node.color;
    return *this;
};

/**
 * @brief Find the tree minimum in the subtree rooted at *this
 * 
 * @tparam T: templated RBTreeNode data class
 * @return RBTreeNode<T>*: pointer to the node with minimum value
 */
template <class T>
RBTreeNode<T> *RBTreeNode<T>::treeMin()
{
    if (left->left == nullptr)
    {
        return this;
    }
    else
    {
        return left->treeMin();
    };
};

/**
 * @brief Find the tree maximum in the subtree rooted at *this
 * 
 * @tparam T: templated RBTreeNode data class
 * @return RBTreeNode<T>*: pointer to the node with maximum value
 */
template <class T>
RBTreeNode<T> *RBTreeNode<T>::treeMax()
{
    if (right->right == nullptr)
    {
        return this;
    }
    else
    {
        return right->treeMax();
    };
};

/**
 * @brief Print the subtree rooted at *this in Pre Order Traversal
 * 
 * @tparam T: templated RBTreeNode data class
 */
template <class T>
void RBTreeNode<T>::printPreOrderTraversal() const
{
    cout << val << " ";

    if (left->left != nullptr)
    {
        left->printPreOrderTraversal();
    };

    if (right->right != nullptr)
    {
        right->printPreOrderTraversal();
    };
};

/**
 * @brief Print the subtree rooted at *this in In Order Traversal
 * 
 * @tparam T: templated RBTreeNode data class
 */
template <class T>
void RBTreeNode<T>::printInOrderTraversal() const
{
    if (left->left != nullptr)
    {
        left->printInOrderTraversal();
    };

    cout << val << " ";

    if (right->right != nullptr)
    {
        right->printInOrderTraversal();
    };
};

/**
 * @brief Print the subtree rooted at *this in Post Order Traversal
 * 
 * @tparam T: templated RBTreeNode data class
 */
template <class T>
void RBTreeNode<T>::printPostOrderTraversal() const
{
    if (left->left != nullptr)
    {
        left->printPostOrderTraversal();
    };

    if (right->right != nullptr)
    {
        right->printPostOrderTraversal();
    };

    cout << val << " ";
};

/**
 * @brief Get the value of the node
 * 
 * @tparam T: templated RBTreeNode data class
 * @return T: value of the node
 */
template <class T>
T *RBTreeNode<T>::value() 
{
    return &val;
};
