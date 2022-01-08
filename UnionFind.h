#ifndef UNION_FIND
#define UNION_FIND

#include <iostream>
#include "Exceptions.h"
using namespace std;

class UnionFind
{
    int* parents_arr;
    int* size_arr;
    int num_of_elements;

    int WhosYourDaddy(int p){
        int temp = p, count = 0;
        while(temp != this->parents_arr[temp] && count < 2*this->num_of_elements){
            temp = this->parents_arr[temp];
            count++;
        }
        if(count == 2*this->num_of_elements){
            throw InfiniteLoop();
        }
        return temp;
    }
    public:
    UnionFind (int k = 100){
        num_of_elements = k + 1;
        parents_arr = new int[num_of_elements];
        size_arr = new int[num_of_elements];
        for (int i = 0; i < num_of_elements; i++)
        {
            parents_arr[i] = i;
            size_arr[i] = 1;
        }
    }

    UnionFind(const UnionFind& other){
        this->num_of_elements = other.num_of_elements;
        parents_arr = new int[num_of_elements];
        size_arr = new int[num_of_elements];
        for (int i = 0; i < this->num_of_elements; i++)
        {
            this->parents_arr[i] = other.parents_arr[i];
            this->size_arr[i] = other.size_arr[i];
        }
    }

    ~UnionFind(){
        delete [] this->parents_arr;
        delete [] this->size_arr;
    }

    UnionFind& operator=(const UnionFind& other){
        if(this == &other){
            return *this;
        }
        
        delete [] this->parents_arr;
        delete [] this->size_arr;
        this->num_of_elements = other.num_of_elements;
        this->parents_arr = new int[num_of_elements];
        this->size_arr = new int[num_of_elements];
        for (int i = 0; i < this->num_of_elements; i++)
        {
            this->parents_arr[i] = other.parents_arr[i];
            this->size_arr[i] = other.size_arr[i];
        }
        return *this;
    }

    int union_groups(int p, int q)
    {
        if((p < 1 || p > this->num_of_elements) || (q < 1 || q > this->num_of_elements)){
            throw OutOfBounds();
        }
        int p_parent = WhosYourDaddy(p);
        int q_parent = WhosYourDaddy(q);
        if(p_parent == q_parent){//already on the same group
            return q_parent;
        }
        if(this->size_arr[p_parent] >= this->size_arr[q_parent]){
            this->parents_arr[q_parent] = p_parent;
            this->size_arr[p_parent] += this->size_arr[q_parent];
            this->size_arr[q_parent] = 0;
            return p_parent;
        }
        else{
            this->parents_arr[p_parent] = q_parent;
            this->size_arr[q_parent] += this->size_arr[p_parent];
            this->size_arr[p_parent] = 0;
            return q_parent;
        }
    }

    int find(int p){
        if(p < 1 || p > this->num_of_elements){
            throw OutOfBounds();
        }
        int temp = p, count = 0;
        while(temp != this->parents_arr[temp] && count < 2*this->num_of_elements){
            temp = this->parents_arr[temp];
            count++;
        }
        if(count == 2*this->num_of_elements){
            throw InfiniteLoop();
        }
        int p_parent;
        for(int i = 0; i < count; i++){
            p_parent = this->parents_arr[p];
            this->parents_arr[p] = temp;
            p = p_parent;
        }
        return this->parents_arr[temp];

        
    }
    void Print(){
        cout << "       ";
        for (int i = 0; i < this->num_of_elements; i++)
        {
            cout << i << "  ";
        }
        cout << endl << "size:  ";
        for (int i = 0; i < this->num_of_elements; i++)
        {
            cout << this->size_arr[i] << "  ";
        }
        cout << endl << "parent:";
        for (int i = 0; i < this->num_of_elements; i++)
        {
            cout << this->parents_arr[i] << "  ";
        }
        
    }
};

#endif