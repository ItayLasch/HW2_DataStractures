#include "library2.h"
#include "GameControl.h"

void *Init(int k, int scale)
{
    if(k <= 0 || scale < 0 || scale > 200)
    {
        return NULL;
    }

    GameControl *DS;
    try
    {
        DS = new GameControl(k, scale);
    }
    catch(...)
    {
        cout << "DS = NULL" << std::endl;
        return NULL;
    }
    
    
    return (void *)DS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }

    try
    {
        ((GameControl *)DS)->mergeGroups(GroupID1, GroupID2);
    }
    catch(InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS == NULL || PlayerID <= 0)
    {
        return INVALID_INPUT;
    }
    
    try{
        ((GameControl*)DS)->addPlayer(PlayerID, GroupID, score);
    }
    catch(InvalidInput &e){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(AlreadyExist &e)
    {
        return FAILURE;
    }
    catch(...)
    {
        return FAILURE;
    }
    
    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS == NULL || PlayerID <= 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((GameControl *)DS)->removePlayer(PlayerID);
    }
    catch(...)
    {
        return FAILURE;
    }

    return SUCCESS;
}


StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS == NULL || PlayerID <= 0 || LevelIncrease <= 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((GameControl*)DS)->increasePlayerIDLevel(PlayerID, LevelIncrease);
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(NotExist &e){
        return FAILURE;
    }
    
    return SUCCESS;
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS == NULL || PlayerID <= 0)
    {
        return INVALID_INPUT;
    }

    try{
        ((GameControl *)DS)->changePlayerIDScore(PlayerID, NewScore);
    }
    catch(InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(NotExist &e)
    {
        return FAILURE;
    }
    catch(...){
        return FAILURE;
    }
    

    return SUCCESS;
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel, double *players)
{
    if(DS == NULL || players == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((GameControl *)DS)->getPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(InvalidInput & e){
        return INVALID_INPUT;
    }
    catch(NotExist& e){
        std::cout << "player not exist" << std::endl;
        return FAILURE;
    }
    catch(...){
        return FAILURE;
    }
    return SUCCESS;
}


StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double *level)
{
    if(DS == NULL || level == NULL || m <= 0 )
    {
        return INVALID_INPUT;
    }

    try
    {
        ((GameControl *)DS)->averageHighestPlayerLevelByGroup(GroupID, m, level);
    }
    catch(InvalidInput& e)
    {
        return INVALID_INPUT;
    }
    catch(std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch(OutOfBounds& e)
    {
        return FAILURE;
    }

    return SUCCESS;
}



void Quit(void **DS)
{
    if (DS == NULL)
    {
        return;
    }

    ((GameControl *)*DS)->Quit((GameControl *)*DS);
    *DS = NULL;
}