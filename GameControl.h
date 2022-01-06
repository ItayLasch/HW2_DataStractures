#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H
#include "AVLTree.h"
#include "Exceptions.h"
#include "HashTable.h"
#include "UnionFind.h"
#include "Group.h"

#include <limits>
#include <cstddef>

class GameControl
{
    HashTable<std::shared_ptr<Player>> Players;
    UnionFind GroupsParent;
    Group **Groups;
    int K;
    int scale;

public:
    GameControl(int K,int scale);

    ~GameControl();

    GameControl(const GameControl &other);

    GameControl& operator=(const GameControl& other);
    
    void mergeGroups(int GroupID1,int GroupID2);

    void addPlayer(int playerID, int GroupID, int score);

    void removePlayer(int PlayerID);

    void increasePlayerIDLevel(int PlayerID, int levelIncrease);

    void changePlayerIDScore(int PlayerID, int NewScore);

    int getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double *players);

    void averageHighestPlayerLevelByGroup(int GroupID, int m, double* avgLevel);

    void Quit(GameControl* GC);

};


#endif