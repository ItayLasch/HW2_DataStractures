#include <stdio.h>
#include <iostream>
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
int main(){
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
    UnionFind<int> uf(15);
    uf.Union(2, 4);
    uf.Union(2, 6);
    uf.Union(3, 5);
    uf.Union(2, 5);
    uf.Union(1, 7);
    uf.Union(7, 10);
    uf.Union(8, 1);
    int x = uf.Find(1);

    return 0;
}


