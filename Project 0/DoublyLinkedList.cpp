//====================================================
// DoublyLinkedList.cpp
// Trinity Meckel, Son Nguyen, Thomas
// September 20, 2024
// This is the implementation file for the DoublyLinkedList class
//====================================================


#include<iostream>
#include "DoublyLinkedList.hpp"

using namespace std;

//====================================================
// default constructor
// initializes an empty doubly linked list
// Parameters:
// none
// Return Value:
// None. Initializes head & tail to NULL, length to 0
//====================================================
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(void) 
{
    head = NULL;
    tail = NULL;
    size = 0;
}


//====================================================
// copy constructor
// create a deep copy of a DoublyLinkedList instance
// Parameters:
// aList: an instance of DoublyLinkedList class
// Return Value:
// None. Initializes head & tail to NULL, length to 0
//====================================================
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &aList) {
	head = NULL;
    tail = NULL;
    size = 0;

    //prepend value of each node of the reference list aList to tis doubly linked list
    Node *node = aList.head;
    while (node != NULL) {
        append(node->val);
        node = node->next;
    }
}


//=====================================================
// destructor
// removes an instance of the DoublyLinkedList class
// Parameters:
// None
// Return Value:
// None. the instance no longer exists
//=====================================================
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(void)
{
{
    Node *ptr = head;
    while (ptr != NULL) {
        Node *next = ptr->next; // Store the next node before deletion
        delete ptr;
        ptr = next;
    }
    head = tail = NULL;
    size = 0;
}
}


//====================================================
// Prepend
// This function adds a new element to the front of the 
// list
// Parameters:
// item: the element to be added to the front of the list
// Return Value:
// None. Element is inserted to become new head of list.
// If list is empty, both head and tail are updated to
// point to the new node. 
//====================================================
template <class T>
void DoublyLinkedList<T>::prepend(const T &item)
{
    // create new node
    Node *newNode = new Node;
    newNode->val = item;
    newNode->prev = NULL; // new node will be head, so no previous node
    newNode->next = head; // new node next is current head

    // check if the list is empty
    if ( head == NULL )
    {
        tail = newNode; // if list is empty, both tail & head should point to new node
    }
    else
    {
        head->prev = newNode; // update prev head to new node
    }

    head = newNode; // new node becomes head of list
    size++; 
}


//====================================================
// Append
// This function adds a new element to the end of the list
// Parameters:
// item: the element to be added 
// Return Value:
// None. Element is inserted to become new tail of list.
// If list is empty, both head and tail are updated to
// point to the new node. 
//====================================================
template<class T>
void DoublyLinkedList<T>::append ( const T &item ) {
    // create a new Node
    Node *newNode = new Node;
    newNode->next = NULL;
    newNode->prev = tail;
    newNode->val = item;

    // if the list is empty, head will be pointing to the new Node
    if (size == 0) {
        head = newNode;
    } 
    // if the list isnt empty, the last Node in the list will be poiting to the new Node
    else {
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}


//================================================================
// insert
// This function inserts a new element into the list at
// a specified index
// Parameters:
// item: the element being added to the list
// index: the index at which a new element is being added
// Return Value:
// None. This function only serves to insert a new item into the list
//================================================================
template <class T>
void DoublyLinkedList<T>::insert(const T &item, int index)
{
    //Throw an out_of_range error if the index does not exist within the list
    if (index < 0 || index > size)
        throw out_of_range("That is outside of the list range.");
    
    if (index == 0)
        this->prepend(item); //if index is 0 put the item at the start of list
    else if (index == size)
        this->append(item); // if index is length of the list append item at the end

    else
    {
        //create a new node to be placed where an element is being inserted
        Node *ptr = new Node;
        //store the new item as the value in the newly placed node
        ptr->val = item;
        //traverse to the node just before the insertion point
        Node *qtr = head;
        for (int i = 0; i < index - 1; i++) 
            qtr = qtr->next;
        //insert the new node between qtr and the next node
        ptr->next = qtr->next;
        ptr->prev = qtr;
        qtr->next->prev = ptr;
        qtr->next = ptr;
        // Adjust the size of the list
        size++;
    }
}


//====================================================
// Remove
// This function removes an item at a specfic position
// indicated by the index
// Parameters:
// index: the position of the element to remove 
// Return Value:
// None. Element at the specfic index is removed.
// If index is out of range, the functions throws
// and out_of_range exception
//====================================================
template <class T> 
void DoublyLinkedList<T>::remove(int index)
{
    // check if the index is out of range
    if (index < 0 || index >= size)
    {
        throw out_of_range( "Index is out of range");
    }

    // special Case: removing the head
    if (index == 0)
    {
        Node *nodeToRemove = head;
        head = head->next;

        if (head != NULL)
        {
            head->prev = NULL;
        }
        else
        {
            tail = NULL; // list is now empty
        }

        delete nodeToRemove;
    }

    // special case: removing the tail
    else if (index == size - 1)
    {    
        Node *nodeToRemove = tail;
        tail = tail->prev;

        if (tail != NULL)
        {
            tail->next = NULL;
        }
        else
        {
            head = NULL; // list is now empty
        }
    }

    // removing from the middle
    else
    {
        Node *current = head;
        for (int i = 0 ; i < index ; i++)
        {
            current = current->next;
        }

        current->prev->next = current->next;
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }

        delete current;
    }

    --size; // decrement from the length of list
}


//====================================================
// search
// This function looks for an item in the list and return
// its index in the list
// Parameters:
// item: the item to be searched for
// Return Value:
// index: the position of that item in the list
//====================================================
template <class T>
int DoublyLinkedList<T>::search ( const T &item ) const {
    Node *current = head;
    for (int i = 0; i < size; i++) {
        if (current->val == item) {
            return i;
        }
        current = current->next;
    }
    return -1;
}


//====================================================
// accessing operator []
// overloads the accessing operator. Allows the
// accessing of indices in the doubly linked list to
// access stored values.
// Parameters:
// index: the index being accessed to retrieve a stored value
// Return Value:
// ptr->val: the value being stored at the index being accessed
//====================================================
template <class T>
T & DoublyLinkedList<T>::operator[] (int index)
{
    //Throw an out_of_range error if the index does not exist within the list
    if (index < 0 || index > size - 1)
        throw out_of_range("That is outside of the list range.");
    Node *ptr = head;
    for (int i = 0; i < index; i++) //loop to iterate through the list
        ptr = ptr->next;
    return ptr->val;
}


//====================================================
// Length
// This function returns the number of elements in the list
// Parameters:
// none
// Return Value:
// returns an integer that reperesents the current
// number of elements in the list
//====================================================
template <class T>
int DoublyLinkedList<T>::length(void) const
{
    return size;
}


//====================================================
// empty
// This function returns true if the list is empty, false otherwise
// Parameters:
// none
// Return Value:
// returns true if the list is empty, false otherwise
//====================================================
template <class T>
bool DoublyLinkedList<T>::empty ( void ) const {
    return size == 0;
}


//=======================================================
// concat
// This function concatenates two doubly linked lists and
// produces a new list with the values stored within the others
// Parameters:
// list: one of the two lists being concatenated, specifically
// the one being placed second after the first list
// const: a constant calling object of the DoublyLinkedList class
// its elements are placed first within the new list
// Return Value:
// newList: A new list comprised of the combined elements from list
// and the calling object.
//=======================================================
template <class T>
DoublyLinkedList<T> DoublyLinkedList<T>::concat(const DoublyLinkedList<T> &list) const
{
    DoublyLinkedList<T> newList;
    //Append the elements of the calling object into newList
    Node *ptr = head;
    while(ptr != NULL) //loop to iterate through the nodes of the calling object
    {
        newList.append(ptr->val);
        ptr = ptr->next;
    }
    //Append the elements of list into newList
    Node *qtr = list.head;
    while(qtr != NULL) //loop to iterate through the nodes in list
    {
        newList.append(qtr->val);
        qtr = qtr->next;
    }
    return newList;
}


//=======================================================
// Assignment operator =
// This function assigns one DoublyLinkedList object to another
// by clearing all nodes in the current list and performing
// a deep copy of the nodes from the given list.
// Parameters:
// alist: the list being copied and assigned to the current object
// Return Value:
// *this: returns the current object after assignment, with all
// elements from the given list copied into it. 
//=======================================================
template <typename T>
DoublyLinkedList<T> & DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &aList) {
    // Check if the object is assigned to itself
    if (this == &aList) {
        return *this;
    }

    // clear all nodes
    this->~DoublyLinkedList();

    // Initialize a deep copy of the given list
    Node* current = aList.head;
    while (current != nullptr) {
        this->append(current->val);
        current = current->next;
    }
    return *this;
}