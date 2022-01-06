#ifndef UNION_FIND
#define UNION_FIND

template <class T>
class UnionFind
{

    T elements_arr[];
    int parents_arr[];
    int size_arr[];
    int num_of_elemets[];

    public:
    UnionFind (int k){
        num_of_elemets = k + 1;
        parents_arr = new int[k];
        size_arr = new int[k];
        elements_arr = new T[k];
        for (int i = 0; i < k; i++)
        {
            parents_arr[i] = i;
            size_arr[i] = 1;
            elements_arr[i] = new T();
        }
        
    }

    UnionFind(const UnionFind& other){
        this->num_of_elemets = other->num_of_elements;
        parents_arr = new int[num_of_elemets];
        size_arr = new int[num_of_elemets];
        elements_arr = new T[num_of_elemets];
        for (int i = 0; i < k; i++)
        {
            this->parents_arr[i] = other->parents_arr[i];
            this->size_arr[i] = other->size_arr[i];
            this->elements_arr[i] = other->elements_arr[i];
        }
    }

    ~UnionFind(){
        delete [] this->parents_arr;
        delete [] this->size_arr;
        delete [] this->elements_arr;
    }

    UnionFind operator=(const UnionFind& other){
        if(&this == other){
            return *this;
        }
        delete [] this->parents_arr;
        delete [] this->size_arr;
        delete [] this->elements_arr;
        this->num_of_elemets = other->num_of_elements;
        this->parents_arr = new int[num_of_elemets];
        this->size_arr = new int[num_of_elemets];
        this->elements_arr = new T[num_of_elemets];
        for (int i = 0; i < k; i++)
        {
            this->parents_arr[i] = other->parents_arr[i];
            this->size_arr[i] = other->size_arr[i];
            this->elements_arr[i] = other->elements_arr[i];
        }
        return *this;
    }
    
    void Union(int p, int q){
        if((p < 1 || p > this->num_of_elements) && (q < 1 || q > this->num_of_elements)){
            throw OutOfBounds();
        }
        if(this->size_arr[p] >= this->size_arr[q]){
            this->parents_arr[q] = this->parents_arr[p];
        }
        else{
            this->parents_arr[p] = this->parents_arr[q];
        }
    }

    T& Find(int p){
        if(p < 1 || p > this->num_of_elements){
            throw OutOfBounds();
        }
        int temp = p, count = 0;
        while(temp != this->parents_arr[temp] && count < 2*this->num_of_elements){
            temp = this->parents_arr[temp];
            count++;
        }
        if(count == 2*this->num_of_elements){
            throw InfinitLoop();
        }
        int p_parent;
        for(int i = 0; i < count; i++){
            p_parent = this->parents_arr[p];
            this->parents_arr[p] = temp;
            p = p_parent;
        }
        return this->elements_arr[temp];
    }
}



#endif