//==============================================================
// RBTree.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This file contains the implementation of the RBTree (Red Black Tree) 
// class template, which supports fundamental operations such as insertion, 
// deletion, searching for specific node values, and traversing the tree 
// (pre-order, in-order, post-order). It also includes functionality for 
// finding the minimum and maximum nodes in the tree, as well as memory 
// management through cloning and transplanting nodes. Custom exceptions 
// are used to handle cases like empty trees and missing values. Insertion
// and deletion have helper methods that maintain RBTree properties as the
// tree is operated upon. Left and right rotation methods are implemented
// to be used by helper methods that "fix" RBTree property violations, which 
// are caused inevitably by insertion and deletion of nodes in an RBTree
//==============================================================

#include "RBTree.hpp"
#include "customexceptions.hpp"
#include <iostream>
using namespace std;

//==============================================================
// RBTree
// Default constructor for the RBTree class.
// Initializes an empty binary search tree with a root of nullptr and 
// sets nodeCount to 0.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTree<T>::RBTree(){
    root = nullptr;
    nodeCount = 0;
}

//==============================================================
// RBTree
// Constructor that creates a RBTree with an initial root node.
// PARAMETERS:
// - val : initial value for the root node
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTree<T>::RBTree(const T &val){
    root = new RBTreeNode<T>(val);
    root->color = BLACK;  // Root must be black in a red-black tree
    nodeCount = 1;
}

//==============================================================
// RBTree
// Copy constructor that creates a deep copy of an existing RBTree.
// PARAMETERS:
// - other : a reference to the RBTree object to copy
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTree<T>::RBTree(const RBTree<T> &other){
    root = nullptr;
    nodeCount = 0;
    if(other.root){
        root = clone(other.root);
        nodeCount = other.nodeCount;
    }
}

//==============================================================
// ~RBTree
// Destructor for the RBTree class. Deletes all nodes in the tree.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
RBTree<T>::~RBTree(){
    delete root;
}

//==============================================================
// clone
// Creates a deep copy of a given RBTree subtree.
// PARAMETERS:
// - node : pointer to the root of the subtree to clone
// RETURN VALUE:
// - A pointer to the root of the cloned subtree
//==============================================================
template <typename T>
RBTreeNode<T>* RBTree<T>::clone(RBTreeNode<T> *node) const {
    if(node == nullptr){
        return nullptr;
    }
    
    RBTreeNode<T>* newNode = new RBTreeNode<T>(node -> value);
    newNode->color = node->color; // color
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
// Replaces one subtree with another subtree in the RBTree.
// PARAMETERS:
// - oldNode : pointer to the subtree to be replaced
// - newNode : pointer to the subtree to replace oldNode
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::transplant(RBTreeNode<T>* oldNode, RBTreeNode<T>* newNode) {
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
// Checks if the RBTree is empty.
// PARAMETERS:
// - None
// RETURN VALUE:
// - True if the RBTree is empty; otherwise, false
//==============================================================
template <typename T>
bool RBTree<T>::isEmpty() const {
    return root == nullptr;
}

//==============================================================
// size
// Returns the number of nodes in the RBTree.
// PARAMETERS:
// - None
// RETURN VALUE:
// - The total number of nodes in the RBTree
//==============================================================
template <typename T>
long RBTree<T>::size() const {
    return nodeCount; 
}

//==============================================================
// insertFixup
// Restores the Red-Black Tree properties after insertion.
// PARAMETERS:
// - z : pointer to the newly inserted node.
//==============================================================
template<typename T>
void RBTree<T>::RBInsertFixup(RBTreeNode<T>* z) {
    // Loop until we fix the tree properties or reach the root
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            // z's parent is the left child of its grandparent
            RBTreeNode<T>* y = z->parent->parent->right; // Uncle node

            if (y != nullptr && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK; 
                z->parent->parent->color = RED;
                z = z->parent->parent; 
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is a right child
                    z = z->parent; 
                    leftRotate(z);
                }
                // Case 3: z is a left child
                z->parent->color = BLACK;          
                z->parent->parent->color = RED;   
                rightRotate(z->parent->parent); 
            }
        } else {
            // z's parent is the right child of its grandparent
            RBTreeNode<T>* y = z->parent->parent->left; // Uncle node

            if (y != nullptr && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2: z is a left child
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: z is a right child
                z->parent->color = BLACK; 
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK; // Ensure the root is always black
}
//==============================================================
// insert
// insert values to RBTree while maintaining RBTree properties.
// PARAMETERS: 
// - value : value of type T to be inserted.
// RETURN VALUE: 
// - z     : pointer to RBTreeNode that was inserted to RBTree.
//==============================================================
template <typename T>
RBTreeNode<T>* RBTree<T>::insert(T value) {
    RBTreeNode<T>* z = new RBTreeNode<T>(value); // New node
    RBTreeNode<T>* x = root;
    RBTreeNode<T>* y = nullptr; // Future parent node of z.

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
    // Not strictly necessary, safegaurd.
    z->left = nullptr;
    z->right = nullptr;
    z->color = RED;

    RBInsertFixup(z); // call fixer and maintain RBT properties.
    nodeCount++;
    return z;
}

//==============================================================
// remove
// Removes a node with the specified value from the RBTree.
// PARAMETERS:
// - value : the value of the node to be removed
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::remove(T value) {
    if (isEmpty()) {
        throw EmptyTreeException();
    }
    RBTreeNode<T>* nodeToRemove = search(value);
    if (!nodeToRemove) {
        throw ValueNotInTreeException();
    }

    // Initialize pointers for deletion and balance correction
    RBTreeNode<T>* node = nodeToRemove; // Node to be removed
    RBTreeNode<T>* y = node;            // Node that will be removed or moved
    RBTreeNode<T>* x;                   // Replacement node
    Color originalColor = y->color;     // Store the original color of y

    // Case 1: Node to remove has no left child
    if (node->left == nullptr) {
        x = node->right; // Right child becomes the replacement
        transplant(node, node->right); 
    }
    // Case 2: Node to remove has no right child
    else if (node->right == nullptr) {
        x = node->left; // Left child becomes the replacement
        transplant(node, node->left); 
    }
    // Case 3: Node has two children
    else {
        y = node->right->treeMin();
        originalColor = y->color; // Update original color with successor's color
        x = y->right; // Successor's right child

        // If successor is not a direct child of node
        if (y->parent != node) {
            transplant(y, y->right); // Replace successor with its right child
            y->right = node->right;  // Move node's right child to successor
            y->right->parent = y;
        }

        // Replace node with successor
        transplant(node, y);
        y->left = node->left;       // Attach node's left subtree to successor
        y->left->parent = y;
        y->color = node->color;     // Preserve node's color in successor
    }
    // Detach nodeToRemove's pointers before deletion to avoid recursive deletion
    nodeToRemove->left = nullptr;
    nodeToRemove->right = nullptr;
    delete nodeToRemove;

    nodeCount--;

    // If we removed a black node, we need to fix the tree to keep RBT prop
    if (originalColor == BLACK) {
        fixRemove(x);
    }
}

//==============================================================
// fixRemove
// Helper function to restore red-black properties after removing a node.
// This function handles cases based on the sibling's color and structure.
// PARAMETERS:
// - x : pointer to the replacement node after deletion
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::fixRemove(RBTreeNode<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            RBTreeNode<T>* w = x->parent->right; // Sibling

            if (w->color == RED) {
                // Case 1: Sibling is red
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            // Case 2: Sibling's children are black
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                // Case 3: Sibling's right child is black
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }

                // Case 4: Sibling's right child is red
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else { // Symmetric case, swap left and right
            RBTreeNode<T>* w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if (x) x->color = BLACK; // Ensure root is black
}


//==============================================================
// search
// Searches for a node with a given value in the RBTree.
// PARAMETERS:
// - value : the value to search for in the RBTree
// RETURN VALUE:
// - A pointer to the node containing the value, or nullptr if not found
//==============================================================
template <typename T>
RBTreeNode<T>* RBTree<T>::search(T value) const {
    RBTreeNode<T>* current = root;
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
// Finds the node with the minimum value in the RBTree. Calls RBTreereeNode
// treeMin().
// PARAMETERS:
// - None
// RETURN VALUE:
// - A pointer to the node with the minimum value
//==============================================================
template <typename T>
RBTreeNode<T>* RBTree<T>::treeMin() const {
    if (isEmpty()){
        throw EmptyTreeException();
    }
    return root->treeMin();
}

//==============================================================
// treeMax
// Finds the node with the maximum value in the RBTree. Calls RBTreeNode
// treeMax().
// PARAMETERS:
// - None
// RETURN VALUE:
// - A pointer to the node with the maximum value
//==============================================================
template <typename T>
RBTreeNode<T>* RBTree<T>::treeMax() const {
    if (isEmpty()){
        throw EmptyTreeException();
    }
    return root->treeMax();
}

//==============================================================
// printPreOrderTraversal
// Prints the RBTree nodes in pre-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::printPreOrderTraversal() const{
    if(root != nullptr){
        root -> printPreOrderTraversal();
        cout << endl;
    }
}

//==============================================================
// printInOrderTraversal
// Prints the RBTree nodes in in-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::printInOrderTraversal() const{
    if(root != nullptr){
        root -> printInOrderTraversal();
        cout << endl;
    }
}

//==============================================================
// printPostOrderTraversal
// Prints the RBTree nodes in post-order traversal order.
// PARAMETERS:
// - None
// RETURN VALUE:
// - None
//==============================================================
template <typename T>
void RBTree<T>::printPostOrderTraversal() const{
    if(root != nullptr){
        root -> printPostOrderTraversal();
        cout << endl;
    }
}

//==============================================================
// leftRotate
// Performs a left rotation on the given node x within the RBTree.
// PARAMETERS:
// - x: Pointer to the RBTreeNode<T> to be rotated to the left.
// RETURN VALUE:
// - None
// NOTES:
// - A left rotation involves making the right child of x (y) the new root of the subtree,
//   and making x the left child of y.
// - Throws ValueNotInTreeException if x does not have a right child.
//==============================================================
template <typename T>
void RBTree<T>::leftRotate(RBTreeNode<T>* x) {
    RBTreeNode<T>* y = x->right;
    if (y == nullptr){
        throw ValueNotInTreeException();
    }
    x->right = y->left;

    // if y's left subtree exists.
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    // x is root node case.
    if (x->parent == nullptr) {
        root = y;
    } 
    // x is left child case.
    else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    // x is right child case.
    else {
        x->parent->right = y;
    }

    // x becomes y's left child.
    y->left = x;
    x->parent = y;
}

//==============================================================
// rightRotate
// Performs a right rotation on the given node x within the RBTree.
// PARAMETERS:
// - x: Pointer to the RBTreeNode<T> to be rotated to the right.
// RETURN VALUE:
// - None
// NOTES:
// - A right rotation involves making the left child of x (y) the new root of the subtree,
//   and making x the right child of y.
// - Throws ValueNotInTreeException if x does not have a left child.
//==============================================================
template <typename T>
void RBTree<T>::rightRotate(RBTreeNode<T>* x) {
    RBTreeNode<T>* y = x->left;
    if (y == nullptr){
        throw ValueNotInTreeException();
    }
    x->left = y->right;

    // if y's right subtree exists.
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    // x is root node case.
    if (x->parent == nullptr) {
        root = y;
    } 
    // x is right child case.
    else if (x == x->parent->right) {
        x->parent->right = y;
    } 
    // x is left child case.
    else {
        x->parent->left = y;
    }

    // x becomes y's right child.
    y->right = x;
    x->parent = y;
}
