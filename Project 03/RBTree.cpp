//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// RBTree.cpp
// This file contains the implementations of the red-black tree functions
//========================================================
#include "RBTree.hpp"


/**
 * @brief Construct a new RBTree<T>::RBTree object
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
RBTree<T>::RBTree(void)
{
    root = NIL;
    rbt_size = 0;
};

/**
 * @brief Construct a new RBTree<T>::RBTree object
 *
 * @tparam T: templated RBTree data class
 * @param tree: the tree to be copied.
 */
template <class T>
RBTree<T>::RBTree(const RBTree<T> &tree)
{
    root = copy(tree.root, tree);
    rbt_size = tree.rbt_size;
};

/**
 * @brief Destroy the RBTree<T>::RBTree object
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
RBTree<T>::~RBTree(void)
{
    deallocate(root);
    delete NIL;
};

/**
 * @brief Assignment operator overload
 *
 * @tparam T: templated RBTree data class
 * @param tree: the tree to be copied
 * @return RBTree<T>&: the tree copied from the parameter
 */
template <class T>
RBTree<T> &RBTree<T>::operator=(const RBTree<T> &tree)
{
    if (this == &tree)
    {
        return *this;
    }
    deallocate(root);
    root = copy(tree.root, tree);
    rbt_size = tree.rbt_size;
    return *this;
};

/**
 * @brief Checks if the RBTree<T> is empty
 *
 * @tparam T: templated RBTree data class
 * @return true: the tree is empty
 * @return false: the tree is not empty
 */
template <class T>
bool RBTree<T>::isEmpty() const
{
    return rbt_size == 0;
}

/**
 * @brief Count the number of nodes in the RBTree
 *
 * @tparam T: templated RBTree data class
 * @return long: the number of nodes in the RBTree
 */
template <class T>
long RBTree<T>::size() const
{
    return rbt_size;
}

/**
 * @brief Search for the node with value in the RBTree
 *
 * @tparam T: templated RBTree data class
 * @param value: the value of the node to search for
 * @return RBTreeNode<T>*: pointer to the node with value if successful search, NIL otherwise
 */
template <class T>
RBTreeNode<T> *RBTree<T>::search(const T &value)
{
    RBTreeNode<T> *current = root;
    while (current != NIL)
    {
        if (value == current->val)
        {
            return current;
        }
        else if (value < current->val)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

/**
 * @brief Find the minimum value of the RBTree
 *
 * @tparam T: templated RBTree data class
 * @return RBTreeNode<T>*: pointer to the node with the minimum value
 */
template <class T>
RBTreeNode<T> *RBTree<T>::treeMin() const
{
    if (isEmpty())
    {
        throw empty_tree_exception();
    }
    else
    {
        return root->treeMin();
    }
}

/**
 * @brief Find the maximum value of the RBTree
 *
 * @tparam T: templated RBTree data class
 * @return RBTreeNode<T>*: pointer to the node with the maximum value
 */
template <class T>
RBTreeNode<T> *RBTree<T>::treeMax() const
{
    if (isEmpty())
    {
        throw empty_tree_exception();
    }
    else
    {
        return root->treeMax();
    }
}

/**
 * @brief Print the RBTree in Pre Order Traversal
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
void RBTree<T>::printPreOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printPreOrderTraversal();
    }
}

/**
 * @brief Print the RBTree in In Order Traversal
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
void RBTree<T>::printInOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printInOrderTraversal();
    }
}

/**
 * @brief Print the RBTree in Post Order Traversal
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
void RBTree<T>::printPostOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printPostOrderTraversal();
    }
}

/**
 * @brief Insert the value into the RBTree
 *
 * @tparam T: templated RBTree data class
 * @param value: value to be inserted
 * @return RBTreeNode<T>*: pointer to the inserted node
 */
template <class T>
RBTreeNode<T> *RBTree<T>::insert(T value)
{
    RBTreeNode<T> *inserted = new RBTreeNode<T>(value);
    RBTreeNode<T> *current = root;
    RBTreeNode<T> *parent = NIL;

    while (current != NIL)
    {
        parent = current;
        if (inserted->val <= current->val)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    inserted->parent = parent;
    if (parent == NIL)
    { 
        root = inserted;
    }
    else if (inserted->val <= parent->val)
    {
        parent->left = inserted;
    }
    else
    {
        parent->right = inserted;
    }
    inserted->left = NIL;
    inserted->right = NIL;
    inserted->color = RED;
    insert_fixup(inserted);
    NIL_fixup();
    rbt_size++;
    return inserted;
}

/**
 * @brief Fixup after insertion
 *
 * @tparam T: templated RBTree data class
 * @param z: node to be fixed
 */
template <class T>
void RBTree<T>::insert_fixup(RBTreeNode<T> *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBTreeNode<T> *uncle = z->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }
        else
        {
            RBTreeNode<T> *uncle = z->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

/**
 * @brief Remove the value from the RBTree
 *
 * @tparam T: templated RBTree data class
 * @param value: value to be deleted
 */
template <class T>
void RBTree<T>::remove(T value)
{
    if (isEmpty())
    {
        throw empty_tree_exception();
    }

    RBTreeNode<T> *deleted = search(value);
    if (deleted == NIL)
    {
        throw value_not_in_tree_exception();
    }

    RBTreeNode<T> *y = deleted;
    RBTreeNode<T> *x;
    Color original_color = y->color;
    if (deleted->left == NIL)
    {
        x = deleted->right;
        transplant(deleted, deleted->right);
    }
    else if (deleted->right == NIL)
    {
        x = deleted->left;
        transplant(deleted, deleted->left);
    }
    else
    {
        y = deleted->right->treeMin();
        original_color = y->color;
        x = y->right;
        if (y != deleted->right)
        {
            transplant(y, y->right);
            y->right = deleted->right;
            y->right->parent = y;
        }
        else
        {
            x->parent = y;
        };
        transplant(deleted, y);
        y->left = deleted->left;
        y->left->parent = y;
        y->color = deleted->color;
    }
    if (original_color == BLACK)
    {
        delete_fixup(x);
    }
    delete deleted;
    NIL_fixup();
    rbt_size--;
}

/**
 * @brief Fixup after deletion
 *
 * @tparam T: templated RBTree data class
 * @param x: node to be fixed
 */
template <class T>
void RBTree<T>::delete_fixup(RBTreeNode<T> *x)
{
    RBTreeNode<T> *w;
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            };
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                };
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root;
            };
        }
        else
        {
            w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            };
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                };
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = root;
            };
        };
    }
    x->color = BLACK;
};

/**
 * @brief Left-rotate the tree at node
 *
 * @tparam T: templated RBTree data class
 * @param node: node to be rotated
 */
template <class T>
void RBTree<T>::left_rotate(RBTreeNode<T> *node)
{
    RBTreeNode<T> *y = node->right;
    node->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = node;
    };
    y->parent = node->parent;
    if (node->parent == NIL)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
};

/**
 * @brief Right-rotate the tree at node
 *
 * @tparam T: templated RBTree data class
 * @param node: node to be rotated.
 */
template <class T>
void RBTree<T>::right_rotate(RBTreeNode<T> *node)
{
    RBTreeNode<T> *y = node->left;
    node->left = y->right;
    if (y->right != NIL)
    {
        y->right->parent = node;
    };
    y->parent = node->parent;
    if (node->parent == NIL)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    y->right = node;
    node->parent = y;
};

/**
 * @brief Transplate the newNode to the oldNode position
 *
 * @tparam T: templated RBTree data class
 * @param oldNode: node to be transplated
 * @param newNode; node to be deleted
 */
template <class T>
void RBTree<T>::transplant(RBTreeNode<T> *oldNode, RBTreeNode<T> *newNode)
{
    if (oldNode->parent == NIL)
    {
        root = newNode;
    }
    else if (oldNode == oldNode->parent->left)
    {
        oldNode->parent->left = newNode;
    }
    else
    {
        oldNode->parent->right = newNode;
    };
    newNode->parent = oldNode->parent;
};

/**
 * @brief Deallocate the entire RBTree
 *
 * @tparam T: templated RBTree data class
 * @param node: root of the subtree to be deleted.
 */
template <class T>
void RBTree<T>::deallocate(RBTreeNode<T> *node)
{
    if (node == NIL)
    {
        return;
    };
    if (node->left != NIL)
    {
        deallocate(node->left);
    };
    if (node->right != NIL)
    {
        deallocate(node->right);
    };
    delete node;
};

/**
 * @brief Deep copy the parameter tree
 *
 * @tparam T: templated RBTree data class
 * @param node: node to be copied
 * @param tree: tree to be copied
 * @return RBTreeNode<T>*: the tree copied from the parameter
 */
template <class T>
RBTreeNode<T> *RBTree<T>::copy(const RBTreeNode<T> *node, const RBTree<T> &tree)
{
    RBTreeNode<T> *z = new RBTreeNode<T>(node->val);
    z->color = node->color;

    if (node->right != tree.NIL)
    {
        z->right = copy(node->right, tree);
        z->right->parent = z;
    }
    else
    {
        z->right = NIL;
    };
    if (node->left != tree.NIL)
    {
        z->left = copy(node->left, tree);
        z->left->parent = z;
    }
    else
    {
        z->left = NIL;
    };
    return z;
};

/**
 * @brief Fix up the NIL node
 *
 * @tparam T: templated RBTree data class
 */
template <class T>
void RBTree<T>::NIL_fixup()
{
    NIL->left = nullptr;
    NIL->right = nullptr;
    NIL->parent = nullptr;
    NIL->color = BLACK;
};

/**
 * @brief Check if the tree is balanced
 *
 * @tparam T: templated RBTree data class
 * @return true: the tree is balanced
 * @return false: the tree is not balanced
 */
template <class T>
bool RBTree<T>::is_balanced() const
{
    if (root == nullptr)
        return true;

    if (root->color != BLACK)
    {
        std::cerr << "Root is not black." << std::endl;
        return false;
    }

    int blackHeight = -1;
    return is_balanced_helper(root, 0, blackHeight);
}

/**
 * @brief Helper function for is_balanced()
 *
 * @tparam T: templated RBTree data class
 * @param node: current node to check
 * @param currentBlackHeight: current black height
 * @param expectedBlackHeight: expected black height
 * @return true: the subtree rooted at node is balanced
 * @return false: the subtree rooted at node is balanced
 */
template <class T>
bool RBTree<T>::is_balanced_helper(RBTreeNode<T> *node, int currentBlackHeight, int &expectedBlackHeight) const
{
    if (node == nullptr)
    {
        if (expectedBlackHeight == -1)
        {
            expectedBlackHeight = currentBlackHeight;
        }
        return currentBlackHeight == expectedBlackHeight;
    }

    if (node->color == RED)
    {
        if ((node->left && node->left->color == RED) || (node->right && node->right->color == RED))
        {
            std::cerr << "Consecutive red nodes found at node with data " << node->val << std::endl;
            return false;
        }
    }

    if (node->color == BLACK)
        currentBlackHeight++;

    return is_balanced_helper(node->left, currentBlackHeight, expectedBlackHeight) &&
           is_balanced_helper(node->right, currentBlackHeight, expectedBlackHeight);
}
