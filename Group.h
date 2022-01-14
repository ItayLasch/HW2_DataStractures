#ifndef GROUP_H
#define GROUP_H

#include "AVLTree.h"
#include "Player.h"

class Group
{
    int group_id;
    AVLTree<std::shared_ptr<Player>, Player> playersTree;
    AVLTree<std::shared_ptr<Player>, Player> *players_per_score;
    int *players_in_level_0; // ht for all the player with level 0
    int scale;

public:
    Group(int group_id = 0, int scale = 200)
    {
        this->group_id = group_id;
        this->scale = scale;
        players_in_level_0 = new int[scale + 1];
        players_per_score = new AVLTree<std::shared_ptr<Player>, Player>[scale + 1];
        for (int i = 0; i <= scale; i++)
        {
            players_in_level_0[i] = 0;
            players_per_score[i] = AVLTree<std::shared_ptr<Player>, Player>();
        }
    }

    ~Group()
    {
        delete[] players_in_level_0;
        delete[] players_per_score;
    }

    Group(const Group &other) // O(n)
    {
        this->group_id = other.group_id;
        this->scale = other.scale;
        players_in_level_0 = new int[scale + 1];
        players_per_score = new AVLTree<std::shared_ptr<Player>, Player>[scale + 1];
        for (int i = 0; i <= scale; i++)
        {
            players_in_level_0[i] = other.players_in_level_0[i];
            players_per_score[i] = other.players_per_score[i];
        }

        this->playersTree = other.playersTree;
    }

    Group &operator=(const Group &other)
    {
        if (this == &other)
        {
            return *this;
        }

        if (players_in_level_0 != nullptr)
        {
            delete[] players_in_level_0;
        }
        if (players_per_score != nullptr)
        {
            delete[] players_per_score;
        }

        this->group_id = other.group_id;
        this->scale = other.scale;
        players_in_level_0 = new int[scale + 1];
        players_per_score = new AVLTree<std::shared_ptr<Player>, Player>[scale + 1];
        for (int i = 0; i <= scale; i++)
        {

            players_in_level_0[i] = other.players_in_level_0[i];
            players_per_score[i] = other.players_per_score[i];
        }

        this->playersTree = other.playersTree;
        return *this;
    }

    static void MergeGroups(Group &g1, Group &g2)
    {
        AVLTree<std::shared_ptr<Player>, Player> merge_tree_players = AVLTree<std::shared_ptr<Player>, Player>();
        merge_tree_players.AVLTreeMerge(g1.playersTree, g2.playersTree, merge_tree_players);
        g1.playersTree = merge_tree_players;
        g2.playersTree = AVLTree<std::shared_ptr<Player>, Player>();

        AVLTree<std::shared_ptr<Player>, Player> merge_tree_score;
        for (int i = 0; i <= g1.scale; i++)
        {
            g1.players_in_level_0[i] += g2.players_in_level_0[i];
            g2.players_in_level_0[i] = 0;
            merge_tree_score = AVLTree<std::shared_ptr<Player>, Player>();
            merge_tree_players.AVLTreeMerge(g1.players_per_score[i], g2.players_per_score[i], merge_tree_score);
            g1.players_per_score[i] = merge_tree_score;
            g2.players_per_score[i] = AVLTree<std::shared_ptr<Player>, Player>();
        }

        g1.playersTree.Inorder([&](std::shared_ptr<Player> p)
                               { p->setGroup(g1.group_id); });

    }

    void AddPlayer(std::shared_ptr<Player> &newPlayer)
    {
        if (newPlayer->getLevel() == 0)
        {
            players_in_level_0[newPlayer->getScore()]++;
        }
        else
        {
            Player player_key = Player(*newPlayer);
            playersTree.AddItem(newPlayer, player_key, player_key.getLevel());
            players_per_score[newPlayer->getScore()].AddItem(newPlayer, player_key, player_key.getLevel());
        }
    }

    void RemovePlayer(Player &player_key)
    {
        if (player_key.getLevel() == 0)
        {
            this->players_in_level_0[player_key.getScore()]--;
            return;
        }

        this->playersTree.removeItem(player_key);
        this->players_per_score[player_key.getScore()].removeItem(player_key);
    }


    double getTotalSumInLevelZero()
    {
        double sum = 0;
        for (int i = 0; i <= this->scale; i++)
        {
            sum += players_in_level_0[i];
        }

        return sum;
    }

    int getGroupID()
    {
        return this->group_id;
    }

    int *getPlayerInLevelZero()
    {
        return this->players_in_level_0;
    }

    AVLTree<std::shared_ptr<Player>, Player> &getPlayersTreeByScore(int score)
    {
        return this->players_per_score[score];
    }

    AVLTree<std::shared_ptr<Player>, Player> &getPlayersTree()
    {
        return this->playersTree;
    }
};

#endif