//==============================================================
// BST.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This file contains the implementation of the BST (Binary Search Tree) 
// class template, which supports fundamental operations such as insertion, 
// deletion, searching for specific node values, and traversing the tree 
// (pre-order, in-order, post-order). It also includes functionality for 
// finding the minimum and maximum nodes in the tree, as well as memory 
// management through cloning and transplanting nodes. Custom exceptions 
// are used to handle cases like empty trees and missing values.
//==============================================================

#include "BST.hpp"
#include "customexceptions.hpp"
#include <iostream>
using namespace std;

//==============================================================
// BST
// Default constructor for the BST class.
// Initializes an empty binary search tree with a root of nullptr and 
// sets nodeCount to 0.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BST<T>::BST(){
    root = nullptr;
    nodeCount = 0;
}

//==============================================================
// BST
// Constructor that creates a BST with an initial root node.
// PARAMETERS:
// - val : initial value for the root node
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BST<T>::BST(const T &val){
    root = new BSTNode<T>(val);
    nodeCount = 1;
}

//==============================================================
// BST
// Copy constructor that creates a deep copy of an existing BST.
// PARAMETERS:
// - other : a reference to the BST object to copy
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BST<T>::BST(const BST<T> &other){
    root = nullptr;
    nodeCount = 0;
    if(other.root){
        root = clone(other.root);
        nodeCount = other.nodeCount;
    }
}

//==============================================================
// ~BST
// Destructor for the BST class. Deletes all nodes in the tree.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
BST<T>::~BST(){
    delete(root);
}

//==============================================================
// clone
// Creates a deep copy of a given BST subtree.
// PARAMETERS:
// - node : pointer to the root of the subtree to clone
// RETURN VALUE:
// - A pointer to the root of the cloned subtree
//==============================================================
template <typename T>
BSTNode<T>* BST<T>::clone(BSTNode<T> *node) const {
    if(node == nullptr){
        return nullptr;
    }
    
    BSTNode<T>* newNode = new BSTNode<T>(node -> value);
    
    newNode -> left = clone(node -> left);
    newNode -> right = clone(node -> right);
    
    if(newNode -> left){
        newNode -> left -> parent = newNode;
    }
    
    if(newNode -> right){
        newNode -> right -> parent = newNode;
    }
    
    return newNode;
}

//==============================================================
// transplant
// Replaces one subtree with another subtree in the BST.
// PARAMETERS:
// - oldNode : pointer to the subtree to be replaced
// - newNode : pointer to the subtree to replace oldNode
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void BST<T>::transplant(BSTNode<T>* oldNode, BSTNode<T>* newNode) {
    if (oldNode->parent == nullptr) {
        root = newNode; // If oldNode is root
    } else if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode; // If oldNode is left child
    } else {
        oldNode->parent->right = newNode; // If oldNode is right child
    }
    if (newNode != nullptr) {
        newNode->parent = oldNode->parent; // Set parent of newNode
    }
}

//==============================================================
// isEmpty
// Checks if the BST is empty.
// PARAMETERS:
// - None
// RETURN VALUE:
// - True if the BST is empty; otherwise, false
//==============================================================
template <typename T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

//==============================================================
// size
// Returns the number of nodes in the BST.
// PARAMETERS:
// - None
// RETURN VALUE:
// - The total number of nodes in the BST
//==============================================================
template <typename T>
long BST<T>::size() const {
    return nodeCount; 
}

//==============================================================
// insert
// insert values to BST while maintaining BST properties.
// PARAMETERS: 
// - value : value of type T to be inserted.
// RETURN VALUE: 
// - Pointer to BSTNode that was inserted to BST.
//==============================================================
template <typename T>
BSTNode<T>* BST<T>::insert(T value) {
    BSTNode<T>* z = new BSTNode<T>(value); // New node
    BSTNode<T>* x = root;
    BSTNode<T>* y = nullptr; // Future parent node of z.

    // Descend the tree until leaf node. For like values, go to
    // left child.
    while (x != nullptr){
        y = x;
        if (z->value <= x->value){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y; // update parent node address.

    // Insertion process
    if (y == nullptr){ // empty tree case
        root = z;
    }
    else if (z->value <= y->value){ // leq to parent
        y->left = z;
    }
    else {
        y->right = z; // greater than parent
    }
    
    nodeCount++;
    return z;
}

//==============================================================
// remove
// Removes a node with the specified value from the BST.
// PARAMETERS:
// - value : the value of the node to be removed
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void BST<T>::remove (T value) {
    if (isEmpty()) {
        throw EmptyTreeException();
    }

    BSTNode<T>* nodeToRemove = search(value);
    if (!nodeToRemove) {
        throw ValueNotInTreeException();
    }
    
    // Node has no children ( is a leaf node )
    if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
        if (nodeToRemove == root) {
            delete root; // delete root node if only node
            root = nullptr;
        } else {
            transplant(nodeToRemove, nullptr);
            // Detach nodeToRemove's pointers before deletion to avoid recursive deletion
            nodeToRemove->left = nullptr;
            nodeToRemove->right = nullptr;
            delete nodeToRemove;
            }
        }

    // Node has only one child
    else if (nodeToRemove->left == nullptr) {
        cout << "Node has only a right child: " << nodeToRemove->value << endl;
        transplant(nodeToRemove, nodeToRemove->right);
        nodeToRemove->left = nullptr;
        nodeToRemove->right = nullptr;
        delete nodeToRemove;
    } else if (nodeToRemove->right == nullptr) {
        cout << "Node has only a left child: " << nodeToRemove->value << endl;
        transplant(nodeToRemove, nodeToRemove->left);
        nodeToRemove->left = nullptr;
        nodeToRemove->right = nullptr;
        delete nodeToRemove;
    }
        
    // Node has two children
    else {
        BSTNode<T>* successor = nodeToRemove->right->treeMin();
        cout << "Successor found: " << successor->value << endl;

        // Properly handle the successor node's parent
        if (successor->parent != nodeToRemove) {
            transplant(successor, successor->right); // Move right child up
            successor->right = nodeToRemove->right; // connect right child of nodetoRemove
            if (successor->right != nullptr) {
                successor->right->parent = successor; //update parent
            }
        }
        transplant(nodeToRemove, successor); //replace nodeToRemove with successor
        successor->left = nodeToRemove->left; // Move the left child of nodeToRemove
        if (successor->left != nullptr) {
            successor->left->parent = successor; //update parent of left child
        }
        nodeToRemove->left = nullptr;
        nodeToRemove->right = nullptr;
        delete nodeToRemove;
    }
    
    nodeCount--;
}

//==============================================================
// search
// Searches for a node with a given value in the BST.
// PARAMETERS:
// - value : the value to search for in the BST
// RETURN VALUE:
// - A pointer to the node containing the value, or nullptr if not found
//==============================================================
template <typename T>
BSTNode<T>* BST<T>::search(T value) const {
    BSTNode<T>* current = root;
    while (current != nullptr) {
        if (value == current->value) {
            return current;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr; // Not found
}

//==============================================================
// treeMin
// Finds the node with the minimum value in the BST. Calls BSTNode
// treeMin().
// PARAMETERS:
// - None
// RETURN VALUE:
// - A pointer to the node with the minimum value
//==============================================================
template <typename T>
BSTNode<T>* BST<T>::treeMin() const {
    if (isEmpty()){
        throw EmptyTreeException();
    }
    return root->treeMin();
}

//==============================================================
// treeMax
// Finds the node with the maximum value in the BST. Calls BSTNode
// treeMax().
// PARAMETERS:
// - None
// RETURN VALUE:
// - A pointer to the node with the maximum value
//==============================================================
template <typename T>
BSTNode<T>* BST<T>::treeMax() const {
    if (isEmpty()){
        throw EmptyTreeException();
    }
    return root->treeMax();
}

//==============================================================
// printPreOrderTraversal
// Prints the BST nodes in pre-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void BST<T>::printPreOrderTraversal() const{
    if(root != nullptr){
        root -> printPreOrderTraversal();
        cout << endl;
    }
}

//==============================================================
// printInOrderTraversal
// Prints the BST nodes in in-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void BST<T>::printInOrderTraversal() const{
    if(root != nullptr){
        root -> printInOrderTraversal();
        cout << endl;
    }
}

//==============================================================
// printPostOrderTraversal
// Prints the BST nodes in post-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void BST<T>::printPostOrderTraversal() const{
    if(root != nullptr){
        root -> printPostOrderTraversal();
        cout << endl;
    }
}
