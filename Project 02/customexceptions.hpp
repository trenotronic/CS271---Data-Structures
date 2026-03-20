//==============================================================
// customexceptions.hpp
// Authors: Jin Seok Youn, Namu Lee Kim, Tren Meckel
// Date: 11/07/2024
// 
// Description:
// This header file defines custom exception classes for use with 
// the Binary Search Tree (BST) and Red Black Tree implementation.
//==============================================================

#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include <exception>

class EmptyTreeException : public exception {
public:
    const char* what() const throw() { return "Empty tree exception"; }
};

class ValueNotInTreeException : public exception {
public:
    const char* what() const throw() { return "Value not in tree exception"; }
};

#endif
