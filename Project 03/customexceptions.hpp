//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// customexceptions.hpp
// This header file defines custom exception classes in
// Hash Classes and Set
//========================================================
#include <iostream>
#include <exception>
using namespace std;

#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

class value_not_in_tree_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Value not in tree exception.";
    }
};

class empty_tree_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Empty tree exception.";
    }
};

class key_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Key exception.";
    }
};

class size_exception : public exception {
public:
    const char* what() const throw() {
        return "Error: Size exception.";
    }
};

#endif
