#ifndef HASH_TABLE_H
#define HASH_TABLE_H

template <class T>
class HashTable;

template <class T>
class NodeList
{
    int key;
    T data;
    NodeList *prev;
    NodeList *next;

    NodeList(int key ,T data) :key(key), data(data), prev(nullptr), next(nullptr){};
    ~NodeList() = default;
    NodeList(const NodeList<T> &other) = default;
    NodeList &operator=(const NodeList<T> &other) = default;

    friend HashTable<T>;
};

template <class T>
class HashTable
{
    int size;
    NodeList<T> **array;
    int numberOfElements;

    void Resize()
    {
        if (numberOfElements == size / 4 || numberOfElements == size)
        {
            delete[] this->array;
            int newSize = (numberOfElements == size) ? 2 * size : size / 4;
            NodeList<T> **newArray = new NodeList<T> *[newSize];
            this->size = newSize;
        }
    }

    void deleteNodes()
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
    HashTable(int size)
    {
        this->size = size;
        this->array = new NodeList<T> *[size];
        numberOfElements = 0;
    }

    ~HashTable() /////////////////////////
    {
        this->deleteNodes();
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

    HashTable &operator=(HashTable &other)
    {

        if (this == &other)
        {
            return *this;
        }

        this->size = other.size;
        this->numberOfElements = other.numberOfElements;
        this->deleteNodes();
        delete[] this->array;
        this->array = new NodeList<T> *[size];
        for (int i = 0; i < size; i++)
        {
            this->array[i] = other.array[i];
        }

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
        }

        return false;
    }

    void Insert(const T &newData, int key)
    {
        if(Search(key))
        {
            return;
        }

        int location = key % size;
        NodeList<T> newNode = new NodeList<T>(key,newData);
        if (array[location] == nullptr)
        {
            array[location] = newNode;
            return;
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

        if(array[location]->key == key)
        {
            if(array[location]->next != nullptr)
            {
                array[location]->next->prev = nullptr;
            }
            array[locatin] = array[location]->next;
        }

        this->numberOfElements--;
        this->Resize();
    }
};

#endif