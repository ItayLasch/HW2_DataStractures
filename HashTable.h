#ifndef HASH_TABLE_H
#define HASH_TABLE_H

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
            NodeList<T> **temp = new NodeList<T> *[size];
            for(int i = 0 ; i < size; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            int newSize = (numberOfElements == size) ? 2 * size : size / 2;
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
                    int location = (temp[i]->key) % size;
                    NodeList<T> *newNode = new NodeList<T>(temp[i]->key, temp[i]->data);
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
    HashTable(int size = 100)
    {
        this->size = size;
        this->array = new NodeList<T> *[size];
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

    HashTable &operator=(HashTable &other)
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

    void Insert(const T &newData, int key)
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
};

#endif