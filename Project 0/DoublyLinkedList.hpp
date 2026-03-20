//=========================================================
// DoublyLinkedList.hh
// Trinity Meckel, Son Nguyen, Thomas
// September 20, 2024
// This is the header file for the DoublyLinkedList class
//=========================================================

#include <iostream>

using namespace std;

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

template <class T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T val;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;
    int size;

public:
    DoublyLinkedList ( void );
    DoublyLinkedList ( const DoublyLinkedList<T> &aList );
    ~DoublyLinkedList ( void );
    void prepend ( const T &item );
    void append ( const T &item );
    void insert ( const T &item, int index );
    void remove ( int index );
    int search ( const T &item ) const;
    T & operator[] ( int index );
    int length ( void ) const;
    bool empty ( void ) const;
    DoublyLinkedList<T> concat ( const DoublyLinkedList<T> &list ) const;
    DoublyLinkedList<T> & operator= ( const DoublyLinkedList<T> &aList );
 
    //====================================================
    // Friend 
    // This function overloads the << operator to print
    // the contents of a DoublyLinkedList object
    // Parameters:
    // os: an ostream object (such as cout) to which the 
    //     list will be printed
    // list: a reference to the DoublyLinkedList object 
    //       that we want to print
    // Return Value:
    // returns the ostream object (os) with the contents of
    // the list printed, where each element is separated by
    // a single space. No trailing space is printed after the
    // last element.
    // //====================================================
    friend ostream & operator<< ( ostream &os, DoublyLinkedList<T> &list ) {
        Node *current = list.head; // start from head of the list
        // go through list and print each item
        while (current != NULL)
        {
            os << current->val; // print the value of the current node

            if (current->next != NULL)
            {
                os << ' '; // print a space if there is another item following
            }

            current = current->next; // move to the new node
        }

        return os;
    }
};


// #include "DoublyLinkedList.cpp"


#endif