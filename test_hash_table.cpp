#include "HashTable.h"

int main()
{
    HashTable<int> ht = HashTable<int>();
    ht.Insert(1,1);
    ht.Insert(2,2);
    ht.Insert(6, 6);
    ht.Delete(2);
    return 0;
}

