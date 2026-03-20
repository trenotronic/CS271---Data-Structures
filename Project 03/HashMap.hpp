//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// HashMap.hpp
// This header file defines the HashMap class template
//========================================================
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "Hash.hpp"

template <class K, class V>
class HashMap
{
private:
    struct Node
    {
        pair<K, V> item;
        Node *next;
        Node *prev;
    };

    const long DEFAULT_SLOTS = 1024;
    long slots;
    long size;
    Node **table;
    Hash<K> h;

    void copy(const HashMap<K, V> &map);

public:
    HashMap();
    HashMap(long m);
    HashMap(const HashMap<K, V> &map);
    ~HashMap();

    HashMap<K,V> operator= (const HashMap<K, V> &map);
    void insert(const K &key, const V &value);
    void remove(Node *D);
    void del(const K &key);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);
    Node *search_node(const K &key);
    vector<int> count_elements_per_slot() const;

};

#include "HashMap.cpp"

#endif
