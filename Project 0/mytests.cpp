//====================================================
// mytests.cpp
// Trinity Meckel, Son Nguyen, Thomas
// September 20, 2024
// This is the test file for DoublyLinkedList class
//====================================================

#include<iostream>
#include "DoublyLinkedList.cpp"
#include<cassert>

using namespace std;

//====================================================
// Test Default Constructor
// Purpose: Test if the default constructor initializes an empty list.
// It demonstrates that the list is properly initialized with a size of 0
// and that the `empty()` function returns true when the list is created.
//====================================================
void testDefaultConstructor() {
    DoublyLinkedList<int> list;
    assert(list.length() == 0); //list should be empty
    assert(list.empty()); //empty() should return true
    cout << "testDefaultConstructor passed!" << endl;
}


//====================================================
// Test Copy Constructor
// Purpose: Test to see if the copy constructor makes a deep copy of the list.
// It demonstrates that the copied list has the same values as the original,
// and modifications to the original list do not affect the copied list.
//====================================================
void testCopyConstructor() {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    //make a deep copy of the list
    DoublyLinkedList<int> copiedList(list);

    //check that the copied list has the same values
    assert(copiedList.length() == 5);
    assert(copiedList[0] == 1);
    assert(copiedList[1] == 2);
    assert(copiedList[2] == 3);

    //modify the original list and ensure the copy remains unchanged
    list.append(4);
    assert(copiedList.length() == 5); //copied list should remain unchanged

    cout << "testCopyConstructor passed!" << endl;
}


//====================================================
// Test Prepend Function
// Purpose: Test the prepend method to ensure it adds elements to the beginning of the list.
// It demonstrates that elements are correctly inserted at the head and the list updates accordingly.
//====================================================
void testPrepend() 
{
    //initialize a instance of doubly linked list class
    DoublyLinkedList<int> list;
    list.prepend(1);
    list.prepend(2);
    list.prepend(3);

    //the list should now be: 3 2 1
    assert(list.length() == 3);
    assert(list[0] == 3); 
    assert(list[1] == 2);
    assert(list[2] == 1);
    cout << "testPrepend passed!" << endl;
}


//====================================================
// Test Append Function
// Purpose: Test the append method to ensure it adds elements to the end of the list.
// It demonstrates that elements are correctly inserted at the tail and the list updates accordingly.
//====================================================
void testAppend() {
    //initialize a instance of doubly linked list class
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    //the list should now be: 1 2 3
    assert(list.length() == 3);
    assert(list[0] == 1);
    assert(list[1] == 2);
    assert(list[2] == 3);
    cout << "testAppend passed!" << endl;
}


//====================================================
// Test Insert Function
// Purpose: Test the insert method to ensure elements are inserted at the correct index.
// It demonstrates that the element is correctly inserted at any position in the list.
//====================================================
void testInsert()
{   
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    cout << "List before inserts: " << list << endl;
    list.insert(5, 0); //insert 5 at index 0
    list.insert(100, 2); //insert 4 at index 2
    list.insert(8, list.length()); //insert 8 at the end

    cout << "List after inserting: " << list << endl;

    //the list should now be: 5 1 4 2 3 8
    assert(list.length() == 6);
    assert(list[0] == 5);
    assert(list[1] == 1);
    assert(list[2] == 100);
    assert(list[3] == 2);
    assert(list[4] == 3); //check index 4
    assert(list[5] == 8); //check last index

    cout << "testInsert passed!" << endl;

}


//====================================================
// Test Remove Function
// Purpose: Test the remove method to ensure elements are removed from the correct index.
// It demonstrates that the correct element is removed and the list structure remains intact.
//====================================================
void testRemove() 
{
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    try 
    {
        //remove element at index 1 (which is '2')
        list.remove(1);
        assert(list.length() == 2); //check if the length is updated
        assert(list[0] == 1); //verify first element is still '1'
        assert(list[1] == 3); //verify second element is now '3'

        //remove the head
        list.remove(0);
        assert(list.length() == 1); // Length should be 1 after removal
        assert(list[0] == 3); //the remaining element should be '3'

        //remove the tail
        list.remove(list.length() - 1);
        assert(list.length() == 0); //list should be empty now

        //try out-of-range removal and catch exception
        list.remove(5);
    }
    catch (const out_of_range& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << "testRemove passed!" << endl;
}


//====================================================
// Test Search Function
// Purpose: Test the search method to ensure it finds the correct index of an element.
// It demonstrates that the search function returns the correct index if the element exists,
// and returns -1 if the element does not exist in the list.
//====================================================
void testSearch() {
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    //search for the value 200
    assert(list.search(2) == 1);

    //search for the value 500
    assert(list.search(500) == -1);

    cout << "testSearch passed!" << endl;
}


//====================================================
// Test Operator[] Function
// Purpose: Test the [] operator to ensure elements can be accessed by index.
// It demonstrates that the correct element is returned when using the [] operator.
//====================================================
void testAccess()
{
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    //access elements using the operator[]
    assert(list[0] == 1);
    assert(list[1] == 2);
    assert(list[2] == 3);

    cout << "testAccess passed!" << endl;
}


//====================================================
// Test Length Function
// Purpose: Test the length method to ensure it returns the correct number of elements in the list.
// It demonstrates that the size of the list is accurately tracked.
//====================================================
void testLength() {
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    //the list should have 3 elements
    assert(list.length() == 3);

    cout << "testLength passed!" << endl;
}


//====================================================
// Test Empty Function
// Purpose: Test the empty method to ensure it correctly identifies whether the list is empty.
// It demonstrates that the list reports being empty when it has no elements, and not empty when it contains elements.
//====================================================
void testEmpty() {

    DoublyLinkedList<int> list;

    //initially, the list should be empty
    assert(list.empty());

    //add an element to the list
    list.append(1);

    //now the list should not be empty
    assert(!list.empty());

    cout << "testEmpty passed!" << endl;
}


//====================================================
// Test Concat Function
// Purpose: Test the concat method to ensure two lists are concatenated correctly.
// It demonstrates that the elements from two lists are correctly combined in sequence.
//====================================================
void testConcat()
{
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    //create new lists
    DoublyLinkedList<int> list2, list3;

    //populate list2
    list2.append(40);
    list2.append(50);
    list2.append(60);

    //concatenate list and list2
    list3 = list.concat(list2);

    //check that the concatenation produced the correct results
    assert(list3.length() == list.length() + list2.length()); 

    //check individual elements of list3
    for (int i = 0; i < list.length(); i++) {
        assert(list3[i] == list[i]); //the first part of list3 should match list
    }
    for (int i = 0; i < list2.length(); i++) {
        assert(list3[list.length() + i] == list2[i]); //the second part of list3 should match list2
    }
    cout << "testConcat passed!" << endl;
}


//====================================================
// Test Operator << Function
// Purpose: Test the output of each list
// It demonstrates that the output will be the elements in the list with the same order
//====================================================
void testPrintList() 
{
    //initialize a doubly linked list
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    cout << "List after removal: " << list << endl;
}


//====================================================
// Test Assignment Operator = 
// Purpose: Test the assignment operator to ensure one list is the deep copu of another correctly.
// It demonstrates that the destination list receives a deep copy of the elements from the source list.
//====================================================
void testAssignmentOperator() {

    //initialize a doubly linked list
    DoublyLinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    DoublyLinkedList<int> list2;
    list2.append(3);
    list2.append(4);

    //assign list2 to list1
    list1 = list2;

    //now list1 should be the same as list2: 3 4
    assert(list1.length() == 2);
    assert(list1[0] == 3);
    assert(list1[1] == 4);

    cout << "testAssignmentOperator passed!" << endl;
}

int main() 
{
    testDefaultConstructor();
    testCopyConstructor();
    testPrepend();
    testAppend();
    testInsert();
    testRemove();
    testSearch();
    testAccess();
    testLength();
    testEmpty();
    testConcat();
    testPrintList();
    testAssignmentOperator();

    return 0;  
}
