#include <stdio.h>
#include <iostream>
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
using namespace std;
int main()
{
    /*AVLTree<int, int> t1 = AVLTree<int, int>();
    t1.AddItem(1 ,1, 1);
    t1.AddItem(5,5,5);
    t1.AddItem(8,8,8);
    t1.AddItem(10 ,10, 10);
    t1.AddItem(3,3,3);
    t1.AddItem(18,18,18);
    t1.AddItem(2,2,2);
    int rank  = t1.getSumOfBiggestElements(5);
    */
    try{
        UnionFind uf(11);
        uf.Union(6, 4);
        uf.Union(0, 3);
        uf.Union(2, 4);

        uf.Union(7, 0);
        uf.Union(7, 11);
        uf.Union(8, 6);
        uf.Union(2, 11);
        uf.Find(3);
        uf.Print();

    }
    catch(...)
    {
        cout << "error";
    }
    
    return 0;
}
