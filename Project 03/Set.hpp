//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// Set.hpp
// This header file defines the Set class template 
//==============================================================
#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "HashMap.hpp"

using namespace std;

template <typename T>
class Set {
private:
    HashMap<T, T> table;

public:
    Set();
    Set(size_t table_size);
    Set(const Set<T> &s);
    ~Set();
    Set<T> operator=(const Set<T> &tree);

    void insert(const T &value);
    void remove(const T &value);
    bool search(const T &value);
};

#include "Set.cpp"

#endif 


