//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// HashMapTree.cpp
// This file includes the implementation of the HashMapTree
// class template
//========================================================
#include <iostream>
#include <vector>
#include "HashMapTree.hpp"

using namespace std;

//==============================================================
// HashMapTree
// Default constructor for the HashMapTree class. Initializes the
// hash table with the default number of slots and a hash function.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::HashMapTree()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTreePair[slots];
};

//==============================================================
// HashMapTree
// Parameterized constructor for the HashMapTree class. Initializes
// the hash table with a given number of slots and a hash function.
// PARAMETERS:
// - m: number of slots for the hash table
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::HashMapTree(size_t m)
{
    size = 0;
    slots = m;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTreePair[slots];
};

//==============================================================
// ~HashMapTree
// Destructor for the HashMapTree class. Frees the memory allocated
// for the hash table.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::~HashMapTree()
{
    delete[] table;
};

//==============================================================
// HashMapTree
// Copy constructor for the HashMapTree class. Creates a new object
// as a copy of an existing HashMapTree.
// PARAMETERS:
// - copy: the HashMapTree to copy from
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::HashMapTree(const HashMapTree &copy)
{
    if (this != &copy)
    {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
}

//==============================================================
// operator=
// Assignment operator for the HashMapTree class. Assigns the values
// of another HashMapTree to this one.
// PARAMETERS:
// - copy: the HashMapTree to assign from
// RETURN VALUE:
// - reference to the current object
//==============================================================
template <class K, class V>
HashMapTree<K, V> &HashMapTree<K, V>::operator=(const HashMapTree<K, V> &copy)
{
    if (this != &copy)
    {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
    return *this;
}

//==============================================================
// insert
// Inserts a key-value pair into the hash map tree. If the key
// already exists, the value is updated.
// PARAMETERS:
// - key: key of the item to insert
// - value: value of the item to insert
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
void HashMapTree<K, V>::insert(const K &key, const V &value)
{

    size_t slot = h(key);
    pair<K, V> temp(key, value);
    RBTreeNode<pair<K, V> > *check_temp = table[slot].search(temp);
    if (check_temp == nullptr)
    {
        table[slot].insert(temp);
        size++;
    }
    else
    {
        table[slot].remove(*check_temp->value());
        table[slot].insert(temp);
    };
}

//==============================================================
// remove
// Removes the key-value pair associated with the provided key
// from the hash map tree.
// PARAMETERS:
// - key: key of the item to remove
// RETURN VALUE:
// - none
// EXCEPTIONS:
// - throws key_exception if the key is not found
//==============================================================
template <class K, class V>
void HashMapTree<K, V>::remove(const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    if (table[slot].search(temp) != nullptr)
    {
        table[slot].remove(temp);
        size--;
    }
    else
    {
        throw key_exception();
    }
};

//==============================================================
// operator[]
// Accesses the value associated with the given key. If the key
// is found, returns the corresponding value. Throws an exception
// if the key is not found.
// PARAMETERS:
// - key: key of the item to access
// RETURN VALUE:
// - reference to the value associated with the key
// EXCEPTIONS:
// - throws key_exception if the key is not found
//==============================================================
template <class K, class V>
V &HashMapTree<K, V>::operator[](const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V> > *item = table[slot].search(temp);

    if (item != nullptr)
    {
        return item->value()->second;
    }

    throw key_exception();
}

//==============================================================
// search
// Searches for the key-value pair associated with the given key
// in the hash map tree and returns a pointer to the pair.
// PARAMETERS:
// - key: key of the item to search for
// RETURN VALUE:
// - pointer to the key-value pair if found, nullptr if not found
//==============================================================
template <class K, class V>
pair<K, V> *HashMapTree<K, V>::search(const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V> > *item = table[slot].search(temp);
    if (item == nullptr)
    {
        return nullptr;
    };

    return item->value();
};

//==============================================================
// search (RBTreePair)
// Searches the Red-Black Tree for a node containing the specified 
// key-value pair and returns a pointer to the node if found.
// PARAMETERS:
// - key: the key-value pair to search for
// RETURN VALUE:
// - pointer to the node containing the key-value pair, or nullptr 
//   if not found
//==============================================================
template <class K, class V>
RBTreeNode<pair<K, V> > *HashMapTree<K, V>::RBTreePair::search(const pair<K, V> &key) const
{
    RBTreeNode<pair<K, V> > *current = this->root;
    while (current != this->NIL)
    {
        if (custom::operator==(key, current->val))
        {
            return current;
        }
        else if (custom::operator<(key, current->val))
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
};

//==============================================================
// insert (RBTreePair)
// Inserts a new key-value pair into the Red-Black Tree and balances
// the tree to maintain its properties.
// PARAMETERS:
// - value: the key-value pair to insert
// RETURN VALUE:
// - pointer to the newly inserted node
//==============================================================
template <class K, class V>
RBTreeNode<pair<K, V> > *HashMapTree<K, V>::RBTreePair::insert(pair<K, V> value)
{
    RBTreeNode<pair<K, V> > *inserted = new RBTreeNode<pair<K, V> >(value);
    RBTreeNode<pair<K, V> > *current = this->root;
    RBTreeNode<pair<K, V> > *parent = this->NIL;

    while (current != this->NIL)
    {
        parent = current;
        if (custom::operator<=(inserted->val, current->val))
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    inserted->parent = parent;
    if (parent == this->NIL)
    {
        this->root = inserted;
    }
    else if (custom::operator<=(inserted->val, parent->val))
    {
        parent->left = inserted;
    }
    else
    {
        parent->right = inserted;
    }
    inserted->left = this->NIL;
    inserted->right = this->NIL;
    inserted->color = RED;
    this->insert_fixup(inserted);
    this->NIL_fixup();
    this->rbt_size++;
    return inserted;
};

//==============================================================
// remove (RBTreePair)
// Removes a key-value pair from the Red-Black Tree and rebalances 
// the tree to maintain its properties.
// PARAMETERS:
// - value: the key-value pair to remove
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
void HashMapTree<K, V>::RBTreePair::remove(pair<K, V> value)
{
    if (this->isEmpty())
    {
        throw empty_tree_exception();
    }

    RBTreeNode<pair<K, V> > *deleted = search(value);
    if (deleted == this->NIL)
    {
        throw value_not_in_tree_exception();
    }

    RBTreeNode<pair<K, V> > *y = deleted;
    RBTreeNode<pair<K, V> > *x;
    Color original_color = y->color;
    if (deleted->left == this->NIL)
    {
        x = deleted->right;
        this->transplant(deleted, deleted->right);
    }
    else if (deleted->right == this->NIL)
    {
        x = deleted->left;
        this->transplant(deleted, deleted->left);
    }
    else
    {
        y = deleted->right->treeMin();
        original_color = y->color;
        x = y->right;
        if (y != deleted->right)
        {
            this->transplant(y, y->right);
            y->right = deleted->right;
            y->right->parent = y;
        }
        else
        {
            x->parent = y;
        };
        this->transplant(deleted, y);
        y->left = deleted->left;
        y->left->parent = y;
        y->color = deleted->color;
    }
    if (original_color == BLACK)
    {
        this->delete_fixup(x);
    }
    delete deleted;
    this->NIL_fixup();
    this->rbt_size--;
};

//==============================================================
// get_slot_distribution 
// Get the sizes of each slots in the tree
// PARAMETERS:
// - None
// RETURN VALUE:
// - vector<int> a vector of slots sizes
//==============================================================
template <class K, class V>
vector<int> HashMapTree<K, V>::get_slot_distribution() const {
    std::vector<int> slot_counts(slots, 0);

    for (long i = 0; i < slots; ++i) {
        if (table[i].size() != 0) {  // Check if the tree is not empty
            slot_counts[i] = table[i].size(); // Use RBTree's size function
        }
    }
    return slot_counts;
}
