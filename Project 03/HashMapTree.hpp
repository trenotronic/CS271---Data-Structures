//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// HashMapTree.hpp
// This header file defines the HashMapTree class template
//========================================================
#include <iostream>

using namespace std;

#ifndef HASHMAPTREE_HPP
#define HASHMAPTREE_HPP

#include <utility>
#include "RBTree.hpp"
#include "Hash.hpp"
#include "customexceptions.hpp"

namespace custom
{
    template <class K, class V>
    bool operator==(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first == p2.first;
    }
    template <class K, class V>
    bool operator!=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first != p2.first;
    }
    template <class K, class V>
    bool operator<(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first < p2.first;
    }
    template <class K, class V>
    bool operator>(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first > p2.first;
    }
    template <class K, class V>
    bool operator<=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first <= p2.first;
    }
    template <class K, class V>
    bool operator>=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first >= p2.first;
    }
};

template <class K, class V>
class HashMapTree
{
private:
    const size_t DEFAULT_SLOTS = 10000019;
    const size_t DEFAULT_PRIME = 1000003;
    long slots;
    long size;
    Hash<K> h;

    class RBTreePair : public RBTree<pair<K, V> >
    {
    public:
        RBTreeNode<pair<K, V> > *search(const pair<K, V> &key) const;
        RBTreeNode<pair<K, V> > *insert(pair<K, V> value);
        void remove(pair<K, V> value);
    };

    RBTreePair *table;

public:
    HashMapTree();
    HashMapTree(size_t m);
    HashMapTree(const HashMapTree &copy);
    ~HashMapTree();
    HashMapTree<K, V> &operator=(const HashMapTree<K, V> &copy);

    void insert(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);
    std::vector<int> get_slot_distribution() const;

};

#include "HashMapTree.cpp"

#endif
