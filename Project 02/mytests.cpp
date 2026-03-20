//==============================================================
// mytests.cpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This file contains the test cases for the Binary Search Tree (BST) 
// and for Red Black Tree (RBT).
//==============================================================

#include "BST.cpp"
#include "RBTree.cpp"
#include "customexceptions.hpp"
#include <iostream>
using namespace std;


BSTNode<int>* generateIntNodes();
BST<int> generateIntBST();

RBTreeNode<int>* generateIntRBTNodes();
RBTree<int> generateIntRBT();

void BSTNodesTesting();
void BSTTesting();

void RBTNodesTesting();
void RBTTesting();

// BST Declerations

//BSTNode test functions
bool testBSTNodeTreeMin();
bool testBSTNodeTreeMax();
bool testBSTNodePreOrder();
bool testBSTNodeInOrder();
bool testBSTNodePostOrder();

//BSTNode traversal simulating
void BSTNodePreOrder(BSTNode<int>* node, int arr[4], int& index);
void BSTNodeInOrder(BSTNode<int>* node, int arr[4], int& index);
void BSTNodePostOrder(BSTNode<int>* node, int arr[4], int& index);
void insertHelperBSTNodePreOrder(BSTNode<int>* node, int arr[5], int& index);

//BST test functions
bool testBSTIsEmpty();
bool testBSTSize();
bool testBSTSearch();
bool testBSTTreeMin();
bool testBSTTreeMax();
bool testBSTInsert();
bool testBSTRemove();
bool testBSTTransplant();
bool testBSTPreOrder();
bool testBSTInOrder();
bool testBSTPostOrder();

//RBT Declerations

//RBTNode test functions
bool testRBTNodeTreeMin();
bool testRBTNodeTreeMax();
bool testRBTNodePreOrder();
bool testRBTNodeInOrder();
bool testRBTNodePostOrder();

//RBTNode traversal simulating
void RBTNodePreOrder(RBTreeNode<int>* node, int arr[4], int& index);
void RBTNodeInOrder(RBTreeNode<int>* node, int arr[4], int& index);
void RBTNodePostOrder(RBTreeNode<int>* node, int arr[4], int& index);

//RBT test functions
bool testRBTIsEmpty();
bool testRBTSize();
bool testRBTSearch();
bool testRBTTreeMin();
bool testRBTTreeMax();
bool testRBTInsert();
bool testRBTRemove();
bool testRBTTransplant();
bool testRBTPreOrder();
bool testRBTInOrder();
bool testRBTPostOrder();
bool testRBTRotation(); 

// RBT Prop check
template <typename T>
bool isRedBlackTree(RBTree<T> &tree);

template <typename T>
bool checkRBTProperties(RBTreeNode<T>* node, int blackCount, int &pathBlackCount);

//==============================================================
// main
// Initiate testing by calling testing methods.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - 0
//==============================================================
int main() {
    cout << "\n\nTesting BSTNode Methods:" << endl;
    BSTNodesTesting();
    cout << "\n\nTesting BST Methods:" << endl;
    BSTTesting();
    cout << "\n\nTesting RBTNode Methods:" << endl;
    RBTNodesTesting();
    cout << "\n\nTesting RBT Methods:" << endl;
    RBTTesting();
    return 0;
}

// *******************************************************
// **************BST Testing Functions********************
// *******************************************************

//==============================================================
// generateIntNodes
// Generates integer nodes and links them into a structure of a BST.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - node1: the node acting as root in this tree.
//==============================================================
BSTNode<int>* generateIntNodes(){
    BSTNode<int>* node1 = new BSTNode<int>(5);
    BSTNode<int>* node2 = new BSTNode<int>(2);
    BSTNode<int>* node3 = new BSTNode<int>(10);
    BSTNode<int>* node4 = new BSTNode<int>(8);
    node1 -> left = node2;
    node1 -> right= node3;
    node3 -> left = node4;
    return node1;
}

//==============================================================
// generateIntBST
// Generates BST with 4 nodes and returns it.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - root: BST of 4 nodes.
//==============================================================
BST<int> generateIntBST(){
    BST<int> root = BST<int>(5);
    root.insert(11);
    root.insert(3);
    root.insert(9);
    return root;
}

//==============================================================
// testBSTNodeTreeMin
// Testing treeMin() function and returns boolean result.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - result: either 0 or 1.
//==============================================================
bool testBSTNodeTreeMin(){
    BSTNode<int>* rootNode = generateIntNodes();
    bool result = ((rootNode -> treeMin()) -> value == 2);
    delete rootNode;
    return result;
}

//==============================================================
// testBSTNodeTreeMax
// Testing treeMax() function and returns boolean result.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - result: either 0 or 1.
//==============================================================
bool testBSTNodeTreeMax(){
    BSTNode<int>* rootNode = generateIntNodes();
    bool result = ((rootNode -> treeMax()) -> value == 10);
    delete rootNode;
    return result;
}

//==============================================================
// testBSTNodePreOrder
// Testing pre-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTNodePreOrder(){
    cout << "PreOrder of BSTNode" << endl;
    int arr[4];
    int result[4] = {5, 2, 10, 8};
    BSTNode<int>* rootNode = generateIntNodes();
    rootNode->printPreOrderTraversal();
    int index = 0;
    BSTNodePreOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    delete rootNode;
    return true;
}

//==============================================================
// testBSTNodeInOrder
// Testing in-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTNodeInOrder(){
    cout << "InOrder of BSTNode" << endl;
    int arr[4];
    int result[4] = {2, 5, 8, 10};
    BSTNode<int>* rootNode = generateIntNodes();
    rootNode->printInOrderTraversal();
    int index = 0;
    BSTNodeInOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    delete rootNode;
    cout << endl;
    return true;
}

//==============================================================
// testBSTNodePostOrder
// Testing post-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTNodePostOrder(){
    cout << "PostOrder of BSTNode" << endl;
    int arr[4];
    int result[4] = {2, 8, 10, 5};
    BSTNode<int>* rootNode = generateIntNodes();
    int index = 0;
    rootNode->printPostOrderTraversal();
    BSTNodePostOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    delete rootNode;
    return true;
}

//==============================================================
// BSTNodePreOrder
// Helper function of testBSTNodePreOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void BSTNodePreOrder(BSTNode<int>* node, int arr[4], int& index){
    if(node == nullptr){
        return;
    }
    arr[index++] = node -> value;
    BSTNodePreOrder(node -> left, arr, index);
    BSTNodePreOrder(node -> right, arr, index);
    return;
}

//==============================================================
// BSTNodeInOrder
// Helper function of testBSTNodeInOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void BSTNodeInOrder(BSTNode<int>* node, int arr[4], int& index) {
    if (node == nullptr) {
        return;
    }

    BSTNodeInOrder(node->left, arr, index);
    arr[index++] = node->value;
    BSTNodeInOrder(node->right, arr, index);
}

//==============================================================
// BSTNodePostOrder
// Helper function of testBSTNodePostOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void BSTNodePostOrder(BSTNode<int>* node, int arr[4], int& index){
    if(node == nullptr){
        return;
    }
    BSTNodePostOrder(node -> left, arr, index);
    BSTNodePostOrder(node -> right, arr, index);
    arr[index++] = node -> value;
    return;
}

//==============================================================
// insertHelperBSTNodePreOrd
// Helper function for testBSTInsert(). Different sized tree.
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
void insertHelperBSTNodePreOrder(BSTNode<int>* node, int arr[5], int& index) {
    if(node == nullptr){
        return;
    }
    arr[index++] = node -> value;
    BSTNodePreOrder(node -> left, arr, index);
    BSTNodePreOrder(node -> right, arr, index);
    return;
}


//==============================================================
// testBSTIsEmpty
// Testing isEmpty() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTIsEmpty(){
    BST<int> bst;
    cout <<"\nTesting isEmpty function:" << endl;
    // Initially empty BST
    if (!bst.isEmpty()) {
        return false;
    }
    // Non-empty BST
    bst.insert(1);
    if (bst.isEmpty()) {
        return false;
    }
    return true;
}

//==============================================================
// testBSTSize
// Testing size() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTSize(){
    BST<int> bst = generateIntBST();
    cout << "\nTesting size function" << endl;
    // BST as is from generateIntBST
    if (bst.size() != 4) {
        return false;
    }
    // After inserting new node
    bst.insert(15);
    if (bst.size() != 5) {
        return false;
    }
    // After removing a node
    bst.remove(5);
    if (bst.size() != 4) {
        return false;
    }
        return true;
}

//==============================================================
// testBSTSearch
// Testing search() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTSearch() {
    BST<int> bst = generateIntBST();
    cout << "\nTesting search function:" << endl;
    // Testing known values
    BSTNode<int>* result1 = bst.search(5);
    if (result1 == nullptr || result1->value != 5) {
        return false;
    }
    BSTNode<int>* result2 = bst.search(11);
    if (result2 == nullptr || result2->value != 11) {
        return false;
    }
    BSTNode<int>* result3 = bst.search(3);
    if (result3 == nullptr || result3->value != 3) {
        return false;
    }
    BSTNode<int>* result4 = bst.search(9);
    if (result4 == nullptr || result4->value != 9) {
        return false;
    }
    // Testing a value not in the BST
    BSTNode<int>* result5 = bst.search(20);
    if (result5 != nullptr) {
        return false;
    }
    return true;
}

//==============================================================
// testBSTTreeMin
// Testing treeMin() function by comparing to known minimum.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTTreeMin(){
    cout << "\nTesting BST treeMin function" << endl;
    BST<int> bst = generateIntBST();
    bool result = (bst.treeMin()-> value == 3);
    return result;
}

//==============================================================
// testBSTTreeMax
// Testing treeMax() function by comparing to known maximum.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTTreeMax(){
    cout << "\nTesting BST treeMax function" << endl;
    BST<int> bst = generateIntBST();
    bool result = (bst.treeMax()-> value == 11);
    return result;
}

//==============================================================
// testBSTInsert
// Testing insert() function by comparing to array holding known
// results of pre-order traversal on the BST.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTInsert(){
    cout << "\nTesting insert function" << endl;
    // Array of correct resulting tree pre-order after inserting values.
    int result[5] = {5, 3, 5, 11, 9};

    // Use empty tree and insert nodes to match result[] structure.
    BST<int> bst = BST <int>(5);
    bst.insert(11);
    bst.insert(3);
    bst.insert(9);
    bst.insert(5); // Same value case

    // Testing by comparing pre-order traversal to result[] 
    int arr[5];
    int index = 0;
    insertHelperBSTNodePreOrder(bst.root, arr, index);
    for(int i = 0; i < 5; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testBSTRemove
// Testing remove() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTRemove() {
    BST<int> bst = generateIntBST();
    // Output the initial in-order traversal of the BST
    cout << "\nInitial in-order traversal: ";
    bst.printInOrderTraversal(); // Print initial structure
    cout << endl;

    // Step 1: Removing a node with two children
    cout << "Removing node with two children: 5..." << endl;
    bst.remove(5);
    if (bst.search(5) != nullptr) {
        cout << "Failed to remove node 5." << endl;
        return false;
    }

    cout << "In-order traversal after removing node 5: ";
    bst.printInOrderTraversal(); // Print structure after removal
    cout << endl;

    // Step 2: Removing a leaf node
    cout << "Removing leaf node: 3..." << endl;
    bst.remove(3);
    if (bst.search(3) != nullptr) {
        cout << "Failed to remove node 3." << endl;
        return false;
    }

    cout << "In-order traversal after removing node 3: ";
    bst.printInOrderTraversal(); // Print structure after removal
    cout << endl;

    // Step 3: Removing a node with one child
    cout << "Removing node with one child: 9..." << endl;
    bst.remove(9);
    if (bst.search(9) != nullptr) {
        cout << "Failed to remove node 9." << endl;
        return false;
    }

    cout << "In-order traversal after removing node 9: ";
    bst.printInOrderTraversal(); // Print structure after removal
    cout << endl;
    
    bst.remove(11);
    cout << "After removing 11:" << endl;
    bst.printPreOrderTraversal();

    return true; // If all checks passed
}

//==============================================================
// testBSTTransplant
// Testing transplant() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTTransplant() {
    
    BST<int> bst = generateIntBST();
    
    cout << "\nTree before transplant: ";
    bst.printInOrderTraversal();
    cout << endl;
    
    // Transplanting the node with value 5 with a node with value 11
    BSTNode<int>* nodeToTransplant = bst.search(5);
    BSTNode<int>* newNode = bst.search(11);
    bst.transplant(nodeToTransplant, newNode);
    
    cout << "Tree after transplanting 5 with 11 (in order): ";
    bst.printInOrderTraversal();
    cout << endl;
    
    return true;
    
}

//==============================================================
// testBSTPreOrder
// Testing BST pre-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTPreOrder(){
    cout << "PreOrder of BST" << endl;
    int arr[4];
    int result[4] = {5, 3, 11, 9};
    BST<int> root = generateIntBST();
    root.printPreOrderTraversal();
    int index = 0;
    BSTNodePreOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testBSTInOrder
// Testing BST in-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTInOrder(){
    cout << "InOrder of BST" << endl;
    int arr[4];
    int result[4] = {3, 5, 9, 11};
    BST<int> root = generateIntBST();
    root.printInOrderTraversal();
    int index = 0;
    BSTNodeInOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testBSTPostOrder
// Testing BST post-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testBSTPostOrder(){
    cout << "PostOrder of BST" << endl;
    int arr[4];
    int result[4] = {3, 9, 11, 5};
    BST<int> root = generateIntBST();
    root.printPostOrderTraversal();
    int index = 0;
    BSTNodePostOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

// *******************************************************
// **************RBT Testing Functions********************
// *******************************************************

//==============================================================
// generateIntRBTNodes
// Generates integer nodes and links them into a structure of a RBT.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - node1: the node acting as root in this tree.
//==============================================================
RBTreeNode<int>* generateIntRBTNodes(){
    RBTreeNode<int>* node1 = new RBTreeNode<int>(5);
    RBTreeNode<int>* node2 = new RBTreeNode<int>(2);
    RBTreeNode<int>* node3 = new RBTreeNode<int>(10);
    RBTreeNode<int>* node4 = new RBTreeNode<int>(8);
    node1 -> left = node2;
    node1 -> right= node3;
    node3 -> left = node4;
    return node1;
}

//==============================================================
// generateIntRBT
// Generates RBT with 4 nodes and returns it.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - root: RBT of 4 nodes.
//==============================================================
RBTree<int> generateIntRBT(){
    RBTree<int> root = RBTree<int>(5);
    root.insert(11);
    root.insert(3);
    root.insert(9);
    return root;
}

//==============================================================
// testRBTNodeTreeMin
// Testing treeMin() function and returns boolean result.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - result: either 0 or 1.
//==============================================================
bool testRBTNodeTreeMin(){
    RBTreeNode<int>* rootNode = generateIntRBTNodes();
    bool result = ((rootNode -> treeMin()) -> value == 2);
    delete rootNode;
    return result;
}

//==============================================================
// testRBTNodeTreeMax
// Testing treeMax() function and returns boolean result.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - result: either 0 or 1.
//==============================================================
bool testRBTNodeTreeMax(){
    RBTreeNode<int>* rootNode = generateIntRBTNodes();
    bool result = ((rootNode -> treeMax()) -> value == 10);
    delete rootNode;
    return result;
}

//==============================================================
// RBTNodePreOrder
// Helper function of testRBTNodePreOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void RBTNodePreOrder(RBTreeNode<int>* node, int arr[4], int& index){
    if(node == nullptr){
        return;
    }
    arr[index++] = node -> value;
    RBTNodePreOrder(node -> left, arr, index);
    RBTNodePreOrder(node -> right, arr, index);
    return;
}

//==============================================================
// RBTNodeInOrder
// Helper function of testRBTNodeInOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void RBTNodeInOrder(RBTreeNode<int>* node, int arr[4], int& index){
    if (node == nullptr) {
        return;
    }
    RBTNodeInOrder(node->left, arr, index);
    arr[index++] = node->value;
    RBTNodeInOrder(node->right, arr, index);
}

//==============================================================
// RBTNodePostOrder
// Helper function of testRBTNodePostOrder(). Saves results of 
// traversal to array. 
// PARAMETERS: 
// - node: pointer to root node of tree.
// - arr: array to hold results of traversal.
// - index: array index variable.
// RETURN VALUE: 
// - none
//==============================================================
void RBTNodePostOrder(RBTreeNode<int>* node, int arr[4], int& index){
    if(node == nullptr){
        return;
    }
    RBTNodePostOrder(node -> left, arr, index);
    RBTNodePostOrder(node -> right, arr, index);
    arr[index++] = node -> value;
    return;
}

//==============================================================
// testRBTPreOrder
// Testing RBT pre-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTPreOrder(){
    cout << "PreOrder of RBT" << endl;
    int arr[4];
    int result[4] = {5, 3, 11, 9};
    RBTree<int> root = generateIntRBT();
    root.printPreOrderTraversal();
    int index = 0;
    RBTNodePreOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testRBTNodePreOrder
// Testing pre-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTNodePreOrder(){
    cout << "PreOrder of RBTNode" << endl;
    int arr[4];
    int result[4] = {5, 2, 10, 8};
    RBTreeNode<int>* rootNode = generateIntRBTNodes();
    rootNode->printPreOrderTraversal();
    int index = 0;
    RBTNodePreOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    delete rootNode;
    return true;
}

//==============================================================
// testRBTNodeInOrder
// Testing in-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTNodeInOrder(){
    cout << "InOrder of RBTNode" << endl;
    int arr[4];
    int result[4] = {2, 5, 8, 10};
    RBTreeNode<int>* rootNode = generateIntRBTNodes();
    rootNode->printInOrderTraversal();
    cout << endl;
    int index = 0;
    RBTNodeInOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    delete rootNode;
    return true;
}

//==============================================================
// testRBTNodePostOrder
// Testing post-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTNodePostOrder(){
    cout << "InOrder of RBTNode" << endl;
    int arr[4];
    int result[4] = {2, 8, 10, 5};
    RBTreeNode<int>* rootNode = generateIntRBTNodes();
    rootNode->printPostOrderTraversal();
    int index = 0;
    RBTNodePostOrder(rootNode, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    delete rootNode;
    return true;
}

//==============================================================
// testRBTInOrder
// Testing RBT in-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTInOrder(){
    cout << "InOrder of RBT" << endl;
    int arr[4];
    int result[4] = {3, 5, 9, 11};
    RBTree<int> root = generateIntRBT();
    root.printInOrderTraversal();
    int index = 0;
    RBTNodeInOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testRBTPostOrder
// Testing RBT post-order traversal functions by comparing to array.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTPostOrder(){
    cout << "PostOrder of RBT" << endl;
    int arr[4];
    int result[4] = {3, 9, 11, 5};
    RBTree<int> root = generateIntRBT();
    root.printPostOrderTraversal();
    int index = 0;
    RBTNodePostOrder(root.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testRBTRotation
// Testing the left and right rotation in a RBT
// PARAMETERS:
// - none
// RETURN VALUE:
// - either true or false
//==============================================================
bool testRBTRotation(){
    RBTree<int> rbtree = generateIntRBT();
    cout <<"\nTesting Rotation function:" << endl;
    
    cout << "Initial Tree Structure (Pre-Order): " << endl;
    rbtree.printPreOrderTraversal();

    // Step 1: Perform left rotation on the root
    rbtree.leftRotate(rbtree.root);
    cout << "\nTree after Left Rotation (Pre-Order): " << endl;
    rbtree.printPreOrderTraversal();

    // Step 2: Perform right rotation on the new root
    rbtree.rightRotate(rbtree.root);
    cout << "\nTree after Right Rotation (Pre-Order): " << endl;
    rbtree.printPreOrderTraversal();

    // Check if the tree has returned to its initial structure after rotations
    cout << "\nChecking if tree structure matches initial state..." << endl;

    // Expected structure after rotations: {5, 3, 11, 9}
    if (rbtree.root->value == 5 &&
        rbtree.root->left->value == 3 &&
        rbtree.root->right->value == 11 &&
        rbtree.root->right->left->value == 9) {
        cout << "Rotation test passed. Tree structure matches initial." << endl;
        return true;
    } else {
        cout << "Rotation test failed. Tree structure does not match initial." << endl;
        return false;
    }
}

//==============================================================
// testRBTInsert
// Tests inserting values into an RBT. After every call of the
// insert function, our RBT property test is run on the tree to
// ensure that insert operation does not break RBT rules.
// PARAMETERS:
// - none
// RETURN VALUE:
// - either true or false
//==============================================================
bool testRBTInsert(){
    cout << "\nTesting Insert function" << endl;
    // Array of correct resulting tree pre-order after inserting values.
    int result[4] = {5, 3, 11, 9};

    // Use empty tree and insert nodes to match result[] structure.
    RBTree<int> rbt = RBTree<int>(5);
    if(isRedBlackTree(rbt) == false){ // Testing if insert function breaks any RBT properties.
        return false;
    }
    rbt.insert(11);
    if(isRedBlackTree(rbt) == false){
        return false;
    }
    rbt.insert(3);
    if(isRedBlackTree(rbt) == false){
        return false;
    }
    rbt.insert(9);
    if(isRedBlackTree(rbt) == false){
        return false;
    }
    // Testing tree structure after insert by comparing pre-order traversal to result[] 
    int arr[4];
    int index = 0;
    RBTNodePreOrder(rbt.root, arr, index);
    for(int i = 0; i < 4; i++){
        if(result[i] != arr[i]){
            return false;
        }
    }
    cout << endl;
    return true;
}

//==============================================================
// testRBTRemove
// Tests the 3 different cases when removing a node in a RBT 
// PARAMETERS:
// - none
// RETURN VALUE:
// - either true or false
//==============================================================
bool testRBTRemove() {
   
    RBTree<int> rbtreeNoChildren = generateIntRBT();
    if(isRedBlackTree(rbtreeNoChildren) == false){
        return false;
    }
    cout <<"\nTesting Remove function:" << endl;
    
     // Test 1: Remove a node with no children
    cout << "Tree before removing a leaf node (9):" << endl;
    rbtreeNoChildren.printInOrderTraversal();
    
    rbtreeNoChildren.remove(9);  // Remove leaf node (no children)
    if(isRedBlackTree(rbtreeNoChildren) == false){
        return false;
    }
    cout << "\nTree after removing the leaf node (9):" << endl;
    rbtreeNoChildren.printInOrderTraversal();
    
    if (rbtreeNoChildren.search(9) == nullptr && rbtreeNoChildren.size() == 3) {
        cout << "Remove leaf node test passed!" << endl;
    } else {
        cout << "Remove leaf node test failed." << endl;
        return false;
    }

    // Test 2: Remove a node with one child
    RBTree<int> rbtreeOneChild = generateIntRBT();
    cout << "Tree before removing a node with one child (11):" << endl;
    rbtreeOneChild.printPreOrderTraversal();
    if(isRedBlackTree(rbtreeOneChild) == false){
        return false;
    }
    rbtreeOneChild.remove(11);  // Remove node with one child
    if(isRedBlackTree(rbtreeOneChild) == false){
        return false;
    }
    cout << "\nTree after removing node with one child (11):" << endl;
    rbtreeOneChild.printPreOrderTraversal();
    
    if (rbtreeOneChild.search(11) == nullptr && rbtreeOneChild.search(9) != nullptr) {
        cout << "Remove node with one child test passed!" << endl;
    } else {
        cout << "Remove node with one child test failed." << endl;
        return false;
    }

    // Test 3: Remove a node with two children
    RBTree<int> rbtreeTwoChildren = generateIntRBT();
    cout << "Tree before removing a node with two children (5):" << endl;
    rbtreeTwoChildren.printPreOrderTraversal();
    if(isRedBlackTree(rbtreeTwoChildren) == false){
        return false;
    }
    rbtreeTwoChildren.remove(5);  // Remove node with two children
    if(isRedBlackTree(rbtreeTwoChildren) == false){
        return false;
    }
    cout << "\nTree after removing node with two children (5):" << endl;
    rbtreeTwoChildren.printPreOrderTraversal();
    
    if (rbtreeTwoChildren.search(5) == nullptr && rbtreeTwoChildren.root->value != 5) {
        cout << "Remove node with two children test passed!" << endl;
    } else {
        cout << "Remove node with two children test failed." << endl;
        return false;
    }

    return true;
}

//==============================================================
// testRBTIsEmpty
// Testing isEmpty() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTIsEmpty(){
    RBTree<int> RBT;
    cout <<"\nTesting isEmpty function:" << endl;
    // Initially empty RBT
    if (!RBT.isEmpty()) {
        return false;
    }
    // Non-empty RBT
    RBT.insert(1);
    if (RBT.isEmpty()) {
        return false;
    }
    return true;
}

//==============================================================
// testRBTSize
// Testing size() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTSize(){
    RBTree<int> RBT = generateIntRBT();
    cout << "\nTesting size function" << endl;
    // RBT as is from generateIntRBT
    if (RBT.size() != 4) {
        return false;
    }
    // After inserting new node
    RBT.insert(15);
    if (RBT.size() != 5) {
        return false;
    }
    // After removing a node
    RBT.remove(5);
    if (RBT.size() != 4) {
        return false;
    }
        return true;
}

//==============================================================
// testRBTSearch
// Testing search() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTSearch(){
    RBTree <int> RBT = generateIntRBT();
    cout << "\nTesting search function:" << endl;
    // Testing known values
    RBTreeNode<int>* result1 = RBT.search(5);
    if (result1 == nullptr || result1->value != 5) {
        return false;
    }
    RBTreeNode<int>* result2 = RBT.search(11);
    if (result2 == nullptr || result2->value != 11) {
        return false;
    }
    RBTreeNode<int>* result3 = RBT.search(3);
    if (result3 == nullptr || result3->value != 3) {
        return false;
    }
    RBTreeNode<int>* result4 = RBT.search(9);
    if (result4 == nullptr || result4->value != 9) {
        return false;
    }
    // Testing a value not in the RBT
    RBTreeNode<int>* result5 = RBT.search(20);
    if (result5 != nullptr) {
        return false;
    }
    return true;
}

//==============================================================
// testRBTTreeMin
// Testing treeMin() function by comparing to known minimum.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTTreeMin(){
    cout << "\nTesting RBT treeMin function" << endl;
    RBTree<int> RBT = generateIntRBT();
    bool result = (RBT.treeMin()-> value == 3);
    return result;
}

//==============================================================
// testRBTTreeMax
// Testing treeMax() function by comparing to known maximum.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTTreeMax(){
    cout << "\nTesting BST treeMax function" << endl;
    RBTree<int> RBT = generateIntRBT();
    bool result = (RBT.treeMax()-> value == 11);
    return result;
}

//==============================================================
// testRBTTransplant
// Testing transplant() function.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - either true or false.
//==============================================================
bool testRBTTransplant(){
    RBTree<int> RBT = generateIntRBT();
    
    cout << "\nTree before transplant: ";
    RBT.printInOrderTraversal();
    cout << endl;
    
    // Transplanting the node with value 5 with a node with value 11
    RBTreeNode<int>* nodeToTransplant = RBT.search(5);
    RBTreeNode<int>* newNode = RBT.search(11);
    RBT.transplant(nodeToTransplant, newNode);
    
    cout << "Tree after transplanting 5 with 11 (in order): ";
    RBT.printInOrderTraversal();
    cout << endl;
    
    return true;
}

//==============================================================
// isRedBlackTree
// Checks if the tree maintains Red-Black Tree properties
// RETURN VALUE:
// - true if the tree maintains RBT properties, false otherwise
//==============================================================
template <typename T>
bool isRedBlackTree(RBTree<T> &tree) {
    if(tree.root == nullptr){
        return true; // An empty tree is a valid RBT.
    }

    // Property 2: Check if root is black
    if(tree.root->color != BLACK){
        return false;
    }

    // Helper function to check properties recursively
    int pathBlackCount = -1;
    return checkRBTProperties(tree.root, 0, pathBlackCount);
}

//==============================================================
// checkRBTProperties
// Recursively checks RBT properties on each node
// PARAMETERS:
// - node: pointer to the current node
// - blackCount: current path's black node count
// - pathBlackCount: reference black node count for all paths
// RETURN VALUE:
// - true if the subtree rooted at node maintains RBT properties, false otherwise
//==============================================================
template <typename T>
bool checkRBTProperties(RBTreeNode<T>* node, int blackCount, int &pathBlackCount) {
    if(node == nullptr){
        // Property 5: Ensure all paths have the same black node count
        if(pathBlackCount == -1){ //When it is our first time to reach leaf
            pathBlackCount = blackCount;
        }else if(blackCount != pathBlackCount){
            return false; //If any path at leaf have different black node count, false.
        }
        return true;
    }

    // Property 1 and 4: Check if a node is red, then both of its children must be black
    if(node->color == RED){
        if ((node->left && node->left->color == RED) || (node->right && node->right->color == RED)) {
            return false;
        }
    }else{
        // Increment black node count for black nodes
        blackCount++;
    }

    // Recursively check left and right subtrees
    return (checkRBTProperties(node->left, blackCount, pathBlackCount) && 
    checkRBTProperties(node->right, blackCount, pathBlackCount));
}


//********************************************************
//********************************************************
//*****Various Testing Executed and Result Output*********
//********************************************************
//********************************************************

//==============================================================
// BSTNodesTesting
// Testing functions and respective outputs for BSTNode class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void BSTNodesTesting(){
    //TestResult - a struct containing the count of passed and failed tests.
    struct TestResult {
        int passed;
        int failed;
    };
    
    TestResult BSTNode_result = {0, 0};
    if(testBSTNodePreOrder() == true){
        cout << "PreOrder Traversal to BSTNode test passed" << endl;
        BSTNode_result.passed++;
    }else{
        BSTNode_result.failed++;
    }
    if(testBSTNodeInOrder() == true){
        cout << "InOrder Traversal to BSTNode test passed" << endl;
        BSTNode_result.passed++;
    }else{
        BSTNode_result.failed++;
    }
    if(testBSTNodePostOrder() == true){
        cout << "PostOrder Traversal to BSTNode test passed" << endl;
        BSTNode_result.passed++;
    }else{
        BSTNode_result.failed++;
    }
    if(testBSTNodeTreeMin() == true){
        cout << "TreeMin operation to BSTNode test passed" << endl;
        BSTNode_result.passed++;
    }else{
        BSTNode_result.failed++;
    }
    if(testBSTNodeTreeMax() == true){
        cout << "TreeMax operation to BSTNode test passed" << endl;
        BSTNode_result.passed++;
    }else{
        BSTNode_result.failed++;
    }
    cout << "\n\n";
    cout << "BSTNode Tests Passed: " << BSTNode_result.passed << endl;
    cout << "BSTNode Tests Failed: " << BSTNode_result.failed << endl;
    cout << "\n\n";
}

//==============================================================
// BSTTesting
// Testing functions and respective outputs for BST class. Updates
// and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void BSTTesting(){
    struct TestResult {
        int passed;
        int failed;
    };
    TestResult BST_result = {0, 0};

    if(testBSTSize() == true){
        cout << "Size operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTSearch() == true){
        cout << "Search operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTTreeMin() == true){
        cout << "treeMin operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTTreeMax() == true){
        cout << "treeMax operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTInsert() == true){
        cout << "Insert operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTRemove() == true){
        cout << "Remove operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTTransplant() == true){
        cout << "Transplant operation to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTPreOrder() == true){
        cout << "PreOrder to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTInOrder() == true){
        cout << "InOrder to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }
    if(testBSTPostOrder() == true){
        cout << "PostOrder to BST test passed" << endl;
        BST_result.passed++;
    }else{
        BST_result.failed++;
    }

    cout << "\n\n";
    cout << "BST Tests Passed: " << BST_result.passed << endl;
    cout << "BST Tests Failed: " << BST_result.failed << endl;
    cout << "\n\n";
    
}

//==============================================================
// RBTNodesTesting
// Testing functions and respective outputs for RBTNode class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void RBTNodesTesting(){
    struct TestResult {
        int passed;
        int failed;
    };
    TestResult RBTNode_result = {0, 0};
    if(testRBTNodePreOrder() == true){
        cout << "PreOrder Traversal to RBTNode test passed" << endl;
        RBTNode_result.passed++;
    }else{
        RBTNode_result.failed++;
    }
    if(testRBTNodeInOrder() == true){
        cout << "InOrder Traversal to RBTNode test passed" << endl;
        RBTNode_result.passed++;
    }else{
        RBTNode_result.failed++;
    }
    if(testRBTNodePostOrder() == true){
        cout << "PostOrder Traversal to RBTNode test passed" << endl;
        RBTNode_result.passed++;
    }else{
        RBTNode_result.failed++;
    }
    if(testRBTNodeTreeMin() == true){
        cout << "TreeMin operation to RBTNode test passed" << endl;
        RBTNode_result.passed++;
    }else{
        RBTNode_result.failed++;
    }
    if(testRBTNodeTreeMax() == true){
        cout << "TreeMax operation to RBTNode test passed" << endl;
        RBTNode_result.passed++;
    }else{
        RBTNode_result.failed++;
    }
    cout << "\n\n";
    cout << "RBTNode Tests Passed: " << RBTNode_result.passed << endl;
    cout << "RBTNode Tests Failed: " << RBTNode_result.failed << endl;
    cout << "\n\n";
}

//==============================================================
// RBTTesting
// Testing functions and respective outputs for RBT class. Updates
// and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void RBTTesting(){
    struct TestResult {
        int passed;
        int failed;
    };
    TestResult RBT_result = {0, 0};
    if(testRBTSize() == true){
        cout << "Size operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTSearch() == true){
        cout << "Search operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTTreeMin() == true){
        cout << "treeMin operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTTreeMax() == true){
        cout << "treeMax operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTRotation() == true){
        cout << "Rotation operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTInsert() == true){
        cout << "Insert operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTRemove() == true){
        cout << "Remove operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTTransplant() == true){
        cout << "Transplant operation to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTPreOrder() == true){
        cout << "PreOrder to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTInOrder() == true){
        cout << "InOrder to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }
    if(testRBTPostOrder() == true){
        cout << "PostOrder to RBT test passed" << endl;
        RBT_result.passed++;
    }else{
        RBT_result.failed++;
    }

    cout << "\n\n";
    cout << "RBT Tests Passed: " << RBT_result.passed << endl;
    cout << "RBT Tests Failed: " << RBT_result.failed << endl;
    cout << "\n\n";
}
