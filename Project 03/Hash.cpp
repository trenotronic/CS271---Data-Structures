//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// Hash.cpp
// This file contains the HashFunction class definitions.  
//========================================================

#include "Hash.hpp"
#include <cstdlib>
#include <functional>

#include <iostream>
using namespace std;

//==============================================================
// Hash
// Default constructor for the Hash class. Initializes the hash 
// parameters `a` and `b` with random values.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Hash<T>::Hash ()
{
    a = rand() % (p - 1) + 1;
    b = rand() % p;
};

//==============================================================
// Hash
// Parameterized constructor for the Hash class. Initializes 
// the hash parameters `a`, `b`, and `m` based on the provided 
// values for slots and prime.
// PARAMETERS:
// - slots: Number of slots in the hash table.
// - prime: A prime number used for the hash function.
// RETURN VALUE:
// - none
//==============================================================
template <typename T>
Hash<T>::Hash (size_t slots, size_t prime)
{
    m = slots;
    p = prime;
    a = rand() % (p - 1) + 1;
    b = rand() % p;
};

//==============================================================
// getHash
// Computes and returns the hash value for the given key using 
// a linear transformation based on a, b, and p, then reduces it 
// modulo m.
// PARAMETERS:
// - key: The key to compute the hash value for.
// RETURN VALUE:
// - size_t: The computed hash value modulo m.
//==============================================================
template <typename T>
size_t Hash<T>::getHash (const T &key)
{
    hash<T> hasher;
    size_t hash;
    if (sizeof(key) <= 8)
        hash = key;
    else
        hash = hasher(key);

    // Add b and reduce modulo p
    hash = (a*hash + b) % p;

    // Final modulo m
    return hash % m;
};

//==============================================================
// operator()
// Overload of the function call operator. Allows objects of the 
// Hash class to be used as hash functions directly.
// PARAMETERS:
// - k: The key to compute the hash value for.
// RETURN VALUE:
// - size_t: The computed hash value for the key.
//==============================================================
template <typename T>
size_t Hash<T>::operator() (const T k)
{
    return getHash(k);
};

