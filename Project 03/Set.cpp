//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// Set.cpp
// This file contains the implementations of the Set class
//==============================================================

#include "Set.hpp"
#include "HashMap.hpp"
#include "Hash.hpp"

//==============================================================
// Set
// Default constructor for the Set class. Initializes an empty 
// set with no elements.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Set<T>::Set()
{
}

//==============================================================
// Set
// Parameterized constructor for the Set class. Initializes the 
// set with a specific table size for the underlying hash table.
// PARAMETERS:
// - table_size: number of slots for the hash table
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Set<T>::Set(size_t table_size)
{
    table(table_size);
}

//==============================================================
// Set
// Copy constructor for the Set class. Creates a new Set object 
// by copying the contents of an existing Set object.
// PARAMETERS:
// - s: the Set object to copy
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Set<T>::Set(const Set<T> &s)
{
    table = s.table;
}

//==============================================================
// operator=
// Assignment operator for the Set class. Copies the elements 
// of another Set object into this one.
// PARAMETERS:
// - set: the Set object to assign from
// RETURN VALUE:
// - reference to the current object
//==============================================================
template <typename T>
Set<T> Set<T>::operator=(const Set<T> &set)
{
    table = set.table;
    return *this;
}

//==============================================================
// ~Set
// Destructor for the Set class. Handles the cleanup of any 
// resources associated with the set.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Set<T>::~Set()
{
}

//==============================================================
// insert
// Inserts a value into the set if it is not already present.
// PARAMETERS:
// - value: the value to insert into the set
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
void Set<T>::insert(const T &value)
{
    if (!search(value))
    {
        table.insert(value, value);
    }
}

//==============================================================
// remove
// Removes a value from the set if it exists.
// PARAMETERS:
// - value: the value to remove from the set
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
void Set<T>::remove(const T &value)
{
    table.del(value);
}

//==============================================================
// search
// Checks if a value is present in the set.
// PARAMETERS:
// - value: the value to search for in the set
// RETURN VALUE:
// - true if the value exists in the set, false otherwise
//==============================================================
template <typename T>
bool Set<T>::search(const T &value)
{
    return (table.search(value) != nullptr);
}


