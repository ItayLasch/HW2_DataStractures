#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Exceptions.h"
#include <iostream>

template <class T>
class HashTable;

template <class T>
class NodeList
{
    int key;
    T data;
    NodeList<T> *prev;
    NodeList<T> *next;

    NodeList(int key ,T data) :key(key), data(data), prev(nullptr), next(nullptr){};
    ~NodeList() = default;
    NodeList(const NodeList<T> &other) = default;
    NodeList &operator=(const NodeList<T> &other) = default;
    public:
    NodeList<T>* GetNext()
    {
        return this->next;
    }

    friend std::ostream &operator<<(std::ostream &os, const NodeList<T> &nd)
    {
        os << nd.key;
        return os;
    }

    friend HashTable<T>;
};

template <class T>
class HashTable
{
    int size;
    NodeList<T> **array;
    int numberOfElements;
    const int Init_size = 4;
    
    void Resize()
    {
        if (numberOfElements <= size / 4 || numberOfElements == size)
        {
            NodeList<T> **temp = new NodeList<T> *[size];
            for(int i = 0 ; i < size; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            int smallerSize = size / 2 < Init_size ? Init_size : size / 2;
            int newSize = (numberOfElements == size) ? 2 * size : smallerSize;
            array = new NodeList<T> *[newSize];
            for (int i = 0; i < newSize;i++)
            {
                array[i] = nullptr;
            }
            int oldSize = this->size;
            this->size = newSize;
            for (int i = 0; i < oldSize;i++)
            {
                if (temp[i] != nullptr)
                {
                    NodeList<T> *tempNode = temp[i];
                    while(tempNode != nullptr)
                    {
                        int location = (tempNode->key) % size;
                        NodeList<T> *newNode = new NodeList<T>(tempNode->key, tempNode->data);
                        if (array[location] == nullptr)
                        {
                            array[location] = newNode;
                        }
                        else
                        {
                            newNode->next = array[location];
                            array[location]->prev = newNode;
                            array[location] = newNode;
                        }
                        tempNode = tempNode->next;
                    }
                }
            }

            this->deleteNodes(temp, oldSize);
            delete[] temp;
        }
    }

    void deleteNodes(NodeList<T> ** array,int size)
    {
        NodeList<T> *curr;
        NodeList<T> *temp;
        for (int i = 0; i < size; i++)
        {
            curr = array[i];
            while (curr != nullptr)
            {
                temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

public:
    HashTable()
    {
        this->size = Init_size;
        this->array = new NodeList<T> *[Init_size];
        for (int i = 0; i < size;i++)
        {
            array[i] = nullptr;
        }
        numberOfElements = 0;
    }

    ~HashTable()
    {
        this->deleteNodes(this->array,this->size);
        delete[] array;
    }

    HashTable(const HashTable &other)
    {
        this->size = other.size;
        this->numberOfElements = other.numberOfElements;
        this->array = new NodeList<T> *[size];
        for (int i = 0; i < size; i++)
        {
            this->array[i] = other.array[i];
        }
    }

    HashTable &operator=(const HashTable &other)
    {

        if (this == &other)
        {
            return *this;
        }
        
        this->deleteNodes(this->array,this->size);
        delete[] this->array;
        this->array = new NodeList<T> *[size];
        for (int i = 0; i < size; i++)
        {
            this->array[i] = other.array[i];
        }

        this->size = other.size;
        this->numberOfElements = other.numberOfElements;

        return *this;
    }

    bool Search(int key)
    {
        int location = key % size;
        if(array[location] == nullptr)
        {
            return false;
        }

        NodeList<T> *temp = array[location];
        while(temp != nullptr)
        {
            if(temp->key == key)
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    void Insert(const T newData, int key)
    {
        if(Search(key))
        {
            return;
        }

        int location = key % size;
        NodeList<T>* newNode = new NodeList<T>(key,newData);
        if (array[location] == nullptr)
        {
            array[location] = newNode;
        }
        else
        {
            newNode->next = array[location];
            array[location]->prev = newNode;
            array[location] = newNode;
        }
        this->numberOfElements++;
        this->Resize();
    }

    void Delete(int key)
    {
        if(!Search(key))
        {
            return;
        }

        int location = key % size;
        NodeList<T> *temp = array[location];
        if (array[location]->key == key)
        {
            if(array[location]->next != nullptr)
            {
                array[location]->next->prev = nullptr;
            }
            array[location] = array[location]->next;
        }
        else
        {
            while(temp != nullptr)
            {
                if(temp->key == key)
                {
                    temp->prev->next = temp->next;
                    if(temp->next != nullptr)
                    {
                        temp->next->prev = temp->prev;
                    }
                    break;
                }
                temp = temp->next;
            }
        }

        delete temp;

        this->numberOfElements--;
        this->Resize();
    }

    T& getData(int key)
    {
        int location = key % size;
        if (array[location] == nullptr)
        {
            throw NotExist();
        }

        NodeList<T> *temp = array[location];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                return temp->data;
            }
            temp = temp->next;
        }

        throw NotExist();
    }

    friend std::ostream &operator<<(std::ostream &os, const HashTable<T> &ht)
    {
        for (int i = 0; i < ht.size; i++)
        {
            os << i << ": ";
            NodeList<T> *temp = ht.array[i];
            while (temp != nullptr)
            {
                os << "-> " << *temp;
                temp = temp->GetNext();
            }
            os << std::endl;
        }
        return os;
    }
};

#endif