#include "HashTable.h"
#include "Player.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <memory>
using std::cout;
using std::endl;
using std::make_shared;
using std::vector;
int main()
{
    try
    {

        int rounds = 100;
        srand(time(NULL));
        int num, op = 1, index;
        HashTable<int> ht = HashTable<int>();
        vector<int> v = {};
        for (int i = 0; i < rounds; i++)
        {
            std::cout << "\x1B[2J\x1B[H";
            if (op > 0 || v.size() <= 1) //* INSERT
            {
                num = rand();
                ht.Insert(num,num);
                v.push_back(num);
            }
            // std::cout << "Inserting:  " << num << std::endl;
            else //* DELETE
            {
                int t1 = rand();
                int t2 = v.size();
                index = t1 % t2;
                num = v[index];
                ht.Delete(num);
                v.erase(v.begin() + index);
            }
            std::cout << ht << std::endl;
            op = rand() % 3;
            Sleep(3000);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "FUCK!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << e.what();
    }
    return 0;
}