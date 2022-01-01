#ifndef GROUP
#define GROUP

#include "AVLTree.h";
#include "HashTable.h";
#include "UnionFind.h";
#include "Player.h"

class Group
{
    int group_id;
    AVLTree<std::shared_ptr<Player>, Player> players;
    AVLTree<std::shared_ptr<Player>, Player> *players_per_score;
    int *level_zero;//histogram of scale for all the player with level 0
    int scale;

public:
    Group(int group_id, int scale)
    {
        this->group_id = group_id;
        this->scale = scale;
        level_zero = new int[scale + 1];
        players_per_score = new AVLTree<std::shared_ptr<Player>, Player>[scale + 1];
        for (int i = 0; i <= scale;i++)
        {
            level_zero[i] = 0;
            players_per_score[i] = AVLTree<std::shared_ptr<Player>, Player>();
        }

        this->players = AVLTree<std::shared_ptr<Player>, Player>();
    }

    ~Group()
    {
        delete[] level_zero;
        delete[] players_per_score;
    }

    void MergeGroups(Group& g1, Group& g2){
        AVLTree<std::shared_ptr<Player>, Player> merge_tree_players = AVLTree<std::shared_ptr<Player>, Player>();
        merge_tree_players.AVLTreeMerge(g1.players, g2.players, merge_tree_players);
        g1.players = merge_tree_players;

        AVLTree<std::shared_ptr<Player>, Player> merge_tree_score;
        for (int i = 0; i <= scale; i++)
        {
            g1.level_zero[i] += g2.level_zero[i];
            merge_tree_score = AVLTree<std::shared_ptr<Player>, Player>();
            merge_tree_players.AVLTreeMerge(g1.players_per_score[i], g2.players_per_score[i], merge_tree_score);
            g1.players_per_score[i] = merge_tree_players;
        }
    }
    
};

#endif