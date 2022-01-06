#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <memory>
#include "Exceptions.h"

template <class T, class Key>
class AVLTree;

template <class T, class Key>
class Node
{
    Key key;
    T data;
    int value;
    Node<T, Key> *left;
    Node<T, Key> *right;
    Node<T, Key> *parent;
    int height;
    int sub_tree_size;
    int sum_elemets_sub_tree;

    Node(Key &key, const T &data, int value) : key(key), data(data), left(nullptr), right(nullptr), parent(nullptr), height(0), sub_tree_size(1),
                                               value(value), sum_elemets_sub_tree(value){};
    ~Node() = default;
    Node(const Node<T, Key> &other) = default;
    Node &operator=(const Node &other) = default;
    Key getKeyNode()
    {
        return this->key;
    }

    T getDataNode()
    {
        return this->data;
    }

    int static getHeight(Node<T, Key> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        return node->height;
    }

    int static getSubTreeSize(Node<T, Key> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return node->sub_tree_size;
    }

    int static getSumElementsSubTree(Node<T, Key> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return node->sum_elemets_sub_tree;
    }

    int BFcalc(Node<T, Key> *curr)
    {
        if (curr == nullptr)
        {
            throw NullArg();
        }
        return getHeight(curr->left) - getHeight(curr->right);
    }

    void updateNodeStats()
    {
        this->height = std::max(this->getHeight(this->left), this->getHeight(this->right)) + 1;
        this->sub_tree_size = this->getSubTreeSize(this->right) + this->getSubTreeSize(this->left) + 1;
        this->sum_elemets_sub_tree = this->value + this->getSumElementsSubTree(this->right) + this->getSumElementsSubTree(this->left);
    }

    friend AVLTree<T, Key>;
};

template <class T, class Key>
class AVLTree
{
    Node<T, Key> *root;
    int size;

    // O(n)  n - size of the tree
    //  copies all the nodes
    Node<T, Key> *copy_tree(Node<T, Key> *other, Node<T, Key> *parent)
    {
        if (other == nullptr)
        {
            return nullptr;
        }
        Node<T, Key> *new_node = new Node<T, Key>(other->key, other->data, other->value);
        new_node->parent = parent;
        new_node->height = other->height;

        new_node->sub_tree_size = other->sub_tree_size;
        new_node->value = other->value;
        new_node->sum_elemets_sub_tree = other->sum_elemets_sub_tree;
        new_node->left = copy_tree(other->left, new_node);
        new_node->right = copy_tree(other->right, new_node);
        return new_node;
    }

    // O(n) n - size of the tree
    //  deletes all the nodes
    void deleteTree(Node<T, Key> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // O(logn) n - size of the tree
    // return the node
    Node<T, Key> *FindItem(Node<T, Key> *curr, const Key &key)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }
        if (curr->key == key)
        {
            return curr;
        }
        if (curr->key > key)
        {
            return FindItem(curr->left, key);
        }
        return FindItem(curr->right, key);
    }

    Node<T, Key> *getpredecessor(Node<T, Key> *curr)
    {
        Node<T, Key> *temp = curr;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    Node<T, Key> *fixTree(Node<T, Key> *curr)
    {
        int bf = curr->BFcalc(curr);
        if (bf == 2)
        {
            if (curr->BFcalc(curr->left) >= 0)
            {
                LL(curr);
            }
            else
            { // bf = -1
                LR(curr);
            }
            return curr->parent;
        }
        else if (bf == -2)
        {
            if (curr->BFcalc(curr->right) <= 0)
            {
                RR(curr);
            }
            else
            {
                RL(curr);
            }
            return curr->parent;
        }

        // update height
        curr->updateNodeStats();
        return curr;
    }

    void LL(Node<T, Key> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T, Key> *temp = curr->left;
        curr->left = curr->left->right;
        if (curr->left != nullptr)
        {
            curr->left->parent = curr;
        }

        temp->right = curr;
        temp->parent = curr->parent;

        if (curr->parent != nullptr && curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        else if (curr->parent != nullptr && curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }

        if (this->root == curr)
        {
            this->root = temp;
        }
        curr->parent = temp;

        curr->updateNodeStats();
        temp->updateNodeStats();
    }

    void RR(Node<T, Key> *curr)
    {
        if (curr == nullptr)
            return;

        Node<T, Key> *temp = curr->right;
        curr->right = curr->right->left;
        if (curr->right != nullptr)
        {
            curr->right->parent = curr;
        }

        temp->left = curr;
        temp->parent = curr->parent;

        if (curr->parent != nullptr && curr == curr->parent->left)
        {
            curr->parent->left = temp;
        }
        else if (curr->parent != nullptr && curr == curr->parent->right)
        {
            curr->parent->right = temp;
        }

        if (this->root == curr)
        {
            this->root = temp;
        }
        curr->parent = temp;
        curr->updateNodeStats();
        temp->updateNodeStats();
    }

    void RL(Node<T, Key> *curr)
    {
        LL(curr->right);
        RR(curr);
    }

    void LR(Node<T, Key> *curr)
    {
        RR(curr->left);
        LL(curr);
    }

    // O(logn) n - size of the tree
    void AddItemAux(Node<T, Key> *curr, const T &new_data, Key &key, int value)
    {
        Node<T, Key> *new_node = new Node<T, Key>(key, new_data, value);
        if (curr->left == nullptr && curr->right == nullptr) // curr == leaf
        {
            if (curr->key > key)
            {
                curr->left = new_node;
            }
            else
            {
                curr->right = new_node;
            }
            new_node->parent = curr;
        }
        else if (curr->key > key)
        {
            if (curr->left == nullptr)
            {
                curr->left = new_node;
                new_node->parent = curr;
            }
            else
            {
                delete new_node;
                AddItemAux(curr->left, new_data, key, value);
            }
        }
        else
        {
            if (curr->right == nullptr)
            {
                curr->right = new_node;
                new_node->parent = curr;
            }
            else
            {
                delete new_node;
                AddItemAux(curr->right, new_data, key, value);
            }
        }

        fixTree(curr);
    }

    Node<T, Key> *deleteNodeRec(Node<T, Key> *curr, const Key &key)
    {
        if (curr == nullptr)
        {
            return curr;
        }

        // We now locate in recursion the location of the node we want to remove
        if (curr->key > key)
        {
            curr->left = deleteNodeRec(curr->left, key);
        }
        else if (curr->key < key)
        {
            curr->right = deleteNodeRec(curr->right, key);
        }
        else
        {
            if (curr->left == nullptr || curr->right == nullptr) // has on child or none
            {
                Node<T, Key> *child;
                if (curr->left)
                {
                    child = curr->left;
                }
                else
                {
                    child = curr->right;
                }
                if (child == nullptr) // node is leaf
                {
                    child = curr;
                    // disconnect current from his parent
                    Node<T, Key> *parent = curr->parent;
                    if (parent)
                    {
                        if (parent->left == curr)
                        {
                            parent->left = nullptr;
                        }
                        else
                        {
                            parent->right = nullptr;
                        }
                    }
                    curr = nullptr;
                }
                else // node has one child
                {
                    // copy content of child to current node
                    curr->key = child->key;
                    curr->data = child->data;
                    curr->left = nullptr;
                    curr->right = nullptr;
                }
                delete child;
                child = nullptr;
            }
            else // has 2 chidren
            {
                Node<T, Key> *node_replace = getpredecessor(curr->left);
                curr->key = node_replace->key;
                curr->data = node_replace->data;
                curr->left = deleteNodeRec(curr->left, node_replace->key);
            }
        }

        if (curr == nullptr)
            return nullptr;

        // Fixing the Tree
        return fixTree(curr);
    }

    void inOrderToArraysAux(Node<T, Key> *curr, T *arrData, Key *arrKey, int *arrValue, int size, int *index)
    {
        if (curr == nullptr || *index >= size)
        {
            return;
        }
        inOrderToArraysAux(curr->left, arrData, arrKey, arrValue, size, index);
        if (*index < size)
        {
            arrData[*(index)] = curr->data;
            arrKey[*(index)] = curr->key;
            arrValue[*(index)] = curr->value;
            (*index)++;
        }
        inOrderToArraysAux(curr->right, arrData, arrKey, arrValue, size, index);
    }

    static Node<T, Key> *sortedArrayToBST_helper(T *arrData, Key *arrKey, int *arrValue ,int start, int end, int size_limit) // A - array of *Node
    {
        if (start > end)
        {
            return nullptr;
        }
        // Get the middle element and make it root
        int mid = start + (end - start) / 2;
        if (mid == size_limit)
        {
            return nullptr;
        }
        Node<T, Key> *curr = new Node<T, Key>(arrKey[mid], arrData[mid], arrValue[mid]);

        curr->left = sortedArrayToBST_helper(arrData, arrKey, arrValue, start, mid - 1, size_limit);

        curr->right = sortedArrayToBST_helper(arrData, arrKey, arrValue, mid + 1, end, size_limit);
        return curr;
    }

    static void sortedArrayToBST(T *AData, Key *AKey, int *arrValue, int n, AVLTree<T, Key> &new_tree)
    {
        new_tree.root = sortedArrayToBST_helper(AData, AKey, arrValue, 0, n, n);

        // update the merge tree elements heights
        new_tree.updateHeights(new_tree.root);
    }

    void updateHeights(Node<T, Key> *curr)
    {
        if (curr == nullptr){
            return;
        }
        updateHeights(curr->left);
        updateHeights(curr->right);
        curr->height = std::max(curr->getHeight(curr->left), curr->getHeight(curr->right)) + 1;
        curr->sub_tree_size = curr->getSubTreeSize(curr->left) + curr->getSubTreeSize(curr->right) + 1;
        curr->sum_elemets_sub_tree = curr->getSumElementsSubTree(curr->left) + curr->getSumElementsSubTree(curr->right) + curr->value;
        
    }

    template <typename Func>
    void nodeInorder(Node<T, Key> *node, Func f)
    {
        if (node == nullptr)
        {
            return;
        }

        nodeInorder(node->left, f);
        if (node->data != nullptr)
        {
            f(node->data);
        }
        nodeInorder(node->right, f);
    }

    void getRankAux(Node<T, Key> *curr, Key &key, int *rank)
    {
        if (curr == nullptr)
        {
            return;
        }
        if (curr->getKeyNode() == key)
        {
            *rank += curr->getSubTreeSize(curr->left) + 1;
            return;
        }
        if (curr->getKeyNode() > key)
        {
            getRankAux(curr->left, key, rank);
            return;
        }
        *rank += curr->getSubTreeSize(curr->left) + 1;
        getRankAux(curr->right, key, rank);
    }

    void getSumOfBiggestElementsAux(Node<T, Key>* curr, int max, int counter, int* sum){
        if(curr == nullptr){
            return;
        }
        int temp = counter + 1 + curr->getSubTreeSize(curr->right);
        if(temp == max){
            *sum += curr->getSumElementsSubTree(curr->right) + curr->value;
            return;
        }
        if(temp > max){
            getSumOfBiggestElementsAux(curr->right, max, counter, sum);
            return;
        }
        *sum += curr->getSumElementsSubTree(curr->right) + curr->value;
        getSumOfBiggestElementsAux(curr->left, max, temp, sum);
    }

public:
    AVLTree() : root(nullptr), size(0){};

    ~AVLTree()
    {
        deleteTree(root);
    }

    AVLTree(const AVLTree<T, Key> &other) : size(other.size)
    {
        root = copy_tree(other.root, nullptr);
    }

    AVLTree &operator=(const AVLTree &other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->deleteTree(this->root);
        this->root = this->copy_tree(other.root, nullptr);
        this->size = other.size;

        return *this;
    }

    void AddItem(const T &new_data, Key key, int value)
    {
        if (this->root == nullptr)
        {
            this->root = new Node<T, Key>(key, new_data, value);
        }
        else
            AddItemAux(root, new_data, key, value);
        this->size++;
    }

    void removeItem(const Key &key)
    {
        if (this->root->key == key)
        {
            if (this->root->left == nullptr && this->root->right == nullptr)
            {
                delete this->root;
                this->root = nullptr;
                size--;
                return;
            }
        }
        deleteNodeRec(this->root, key);
        size--;
    }

    int getSize()
    {
        return this->size;
    }

    bool isExists(const Key &key)
    {
        if (this->FindItem(this->root, key) == nullptr)
        {
            return false;
        }
        return true;
    }

    Node<T, Key> *getRoot()
    {
        return this->root;
    }

    T getData(Key &key)
    {
        Node<T, Key> *temp = FindItem(this->root, key);
        if (temp == nullptr)
            return nullptr;

        return temp->getDataNode();
    }

    T FindMax()
    {
        Node<T, Key> *temp = this->root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->data;
    }

    static void AVLTreeMerge(AVLTree<T, Key> &tr1, AVLTree<T, Key> &tr2, AVLTree<T, Key> &merge_tree)
    {
        int s1 = tr1.getSize();
        int s2 = tr2.getSize();
        merge_tree.size = s1 + s2;
        T *arrData1 = new T[s1];
        T *arrData2 = new T[s2];
        T *arrDataNew = new T[s1 + s2];
        Key *arrKey1 = new Key[s1];
        Key *arrKey2 = new Key[s2];
        Key *arrKeyNew = new Key[s1 + s2];
        int *arrValue1 = new int[s1];
        int *arrValue2 = new int[s2];
        int *arrValueNew = new int[s2 + s1];
        tr1.inOrderToArrays(arrData1, arrKey1, arrValue1, s1);
        tr2.inOrderToArrays(arrData2, arrKey2, arrValue2, s2);
        int index1 = 0, index2 = 0, index_new = 0;
        while (index_new < s1 + s2)
        { // merge the 2 arrays into 1
            if (index1 == s1)
            {
                arrValueNew[index_new] = arrValue2[index2];
                arrKeyNew[index_new] = arrKey2[index2];
                arrDataNew[index_new++] = arrData2[index2++];
                continue;
            }
            if (index2 == s2)
            {
                arrValueNew[index_new] = arrValue1[index1];
                arrKeyNew[index_new] = arrKey1[index1];
                arrDataNew[index_new++] = arrData1[index1++];
                continue;
            }
            if (arrKey1[index1] > arrKey2[index2])
            {
                arrValueNew[index_new] = arrValue2[index2];
                arrKeyNew[index_new] = arrKey2[index2];
                arrDataNew[index_new++] = arrData2[index2++];
                continue;
            }
            arrValueNew[index_new] = arrValue1[index2];
            arrKeyNew[index_new] = arrKey1[index1];
            arrDataNew[index_new++] = arrData1[index1++];
        }
        AVLTree<T, Key>::sortedArrayToBST(arrDataNew, arrKeyNew, arrValueNew, s1 + s2, merge_tree);
        delete[] arrData1;
        delete[] arrData2;
        delete[] arrDataNew;
        delete[] arrKey1;
        delete[] arrKey2;
        delete[] arrKeyNew;
        delete[] arrValue1;
        delete[] arrValue2;
        delete[] arrValueNew;
    }

    void inOrderToArrays(T *arrData, Key *arrKey, int* arrValue, int size)
    {
        int i = 0;
        inOrderToArraysAux(this->root, arrData, arrKey, arrValue, size, &i);
    }

    template <typename Func>
    void Inorder(Func f)
    {
        try
        {
            nodeInorder(this->root, f);
        }
        catch (std::exception &e)
        {
        }
    }

    int getRank(Key key)
    {
        if (!this->isExists(key))
        {
            return -1;
        }
        
        int rank = 0;
        this->getRankAux(this->root, key, &rank);
        return rank;
    }

    int getSumOfBiggestElements(int num_of_elements)
    {
        if (num_of_elements > this->size)
        {
            return -1;
        }
        
        int sum = 0;
        this->getSumOfBiggestElementsAux(this->root, num_of_elements, 0, &sum);
        return sum;
    }
};

#endif
