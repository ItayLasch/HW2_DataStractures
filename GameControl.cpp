#include "GameControl.h"

GameControl::GameControl(int K, int scale)
{
    Players = HashTable<std::shared_ptr<Player>>();

    GroupsParent = UnionFind(K);
    Groups = new Group *[K + 1];
    for (int i = 0; i <= K; i++)
    {
        Groups[i] = new Group(i, scale);
    }

    this->K = K;
    this->scale = scale;
}

GameControl::~GameControl()
{
    for (int i = 0; i <= K; i++)
    {
        delete Groups[i];
    }
    delete[] Groups;
}

GameControl::GameControl(const GameControl &other)
{
    this->Players = other.Players;
    this->GroupsParent = other.GroupsParent;
    this->Groups = new Group *[other.K + 1];
    for (int i = 0; i <= other.K; i++)
    {
        *this->Groups[i] = Group(*other.Groups[i]);
    }
    this->K = K;
    this->scale = scale;
}

GameControl &GameControl::operator=(const GameControl &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->Players = other.Players;
    this->GroupsParent = other.GroupsParent;
    this->Groups = new Group *[other.K + 1];
    for (int i = 0; i <= other.K; i++)
    {
        *this->Groups[i] = Group(*other.Groups[i]);
    }
    this->K = K;
    this->scale = scale;
    return *this;
}

void GameControl::mergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1 <= 0 || GroupID1 > K || GroupID2 <= 0 || GroupID2 > K)
    {
        throw InvalidInput();
    }
    //this->Print();

    int G1 = GroupsParent.Find(GroupID1);
    int G2 = GroupsParent.Find(GroupID2);
    if (G1 == G2)
    {
        return;
    }
    int Bigger = GroupsParent.Union(G1, G2);
    if (Bigger == G1)
    {
        Group::MergeGroups(*Groups[G1], *Groups[G2]);
        return;
    }
    else if (Bigger == G2)
    {
        Group::MergeGroups(*Groups[G2], *Groups[G1]);
        return;
    }

    throw FAIL();
}

void GameControl::addPlayer(int playerID, int GroupID, int score)
{

    if (GroupID <= 0 || GroupID > K || score <= 0 || score > scale)
    {
        throw InvalidInput();
    }

    if (Players.Search(playerID))
    {
        throw AlreadyExist();
    }

    int ParentGroup = GroupsParent.Find(GroupID);
    std::shared_ptr<Player> player_p(new Player(playerID, score, ParentGroup));
    this->Players.Insert(player_p, playerID);
    this->Groups[ParentGroup]->AddPlayer(player_p);
    this->Groups[0]->AddPlayer(player_p);
}

void GameControl::removePlayer(int PlayerID)
{
    if (!Players.Search(PlayerID))
    {
        throw NotExist();
    }

    std::shared_ptr<Player> p = Players.getData(PlayerID);
    int group_id = GroupsParent.Find(p->getGroupId());
    Groups[group_id]->RemovePlayer(*p);
    Groups[0]->RemovePlayer(*p);
    Players.Delete(p->getPlayerId());
}

void GameControl::increasePlayerIDLevel(int PlayerID, int levelIncrease)
{
    if (!Players.Search(PlayerID))
    {
        throw NotExist();
    }
    std::shared_ptr<Player> player_p = Players.getData(PlayerID);
    int group_id = player_p->getGroupId();
    if (player_p->getLevel() == 0)
    {
        Groups[0]->RemoveFromZeroLevel(player_p->getScore());
        Groups[group_id]->RemoveFromZeroLevel(player_p->getScore());
    }
    else
    {
        Groups[0]->RemovePlayer(*player_p.get());
        Groups[group_id]->RemovePlayer(*player_p.get());
    }
    player_p->addToLevel(levelIncrease);
    Groups[0]->AddPlayer(player_p);
    Groups[group_id]->AddPlayer(player_p);
}

void GameControl::changePlayerIDScore(int PlayerID, int NewScore)
{
    if (NewScore <= 0 || NewScore > scale)
    {
        throw InvalidInput();
    }
    if (!Players.Search(PlayerID))
    {
        throw NotExist();
    }

    std::shared_ptr<Player> player_p = Players.getData(PlayerID);
    Groups[player_p->getGroupId()]->changePlayerScore(player_p, NewScore);
    Groups[0]->changePlayerScore(player_p, NewScore);
}

void GameControl::getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double *players)
{
    if (GroupID < 0 || GroupID > K)
    {
        throw InvalidInput();
    }
    Group *group = Groups[GroupsParent.Find(GroupID)];
    int lowerLevelNew = lowerLevel >= 0 ? lowerLevel : 0;
    std::shared_ptr<Player> pLower(new Player(std::numeric_limits<int>::min(), score, group->getGroupID(), lowerLevelNew));
    std::shared_ptr<Player> pHigher(new Player(std::numeric_limits<int>::max(), score, group->getGroupID(), higherLevel));
    Groups[GroupID]->AddPlayer(pLower);
    Groups[GroupID]->AddPlayer(pHigher);

    double lowRank = Groups[GroupID]->getPlayersTree().getRank(*pLower);
    double highRank = Groups[GroupID]->getPlayersTree().getRank(*pHigher);
    double lowRankInScore = Groups[GroupID]->getPlayersTreeByScore(score).getRank(*pLower);
    double highRankInScore = Groups[GroupID]->getPlayersTreeByScore(score).getRank(*pHigher);

    double total_betweenLevels = 0, total_betweenLevelsInScore = 0;
    if (lowerLevel <= 0)
    {
        total_betweenLevels = highRank - lowRank - 1 + Groups[GroupID]->getTotalSumInLevelZero();
        total_betweenLevelsInScore = highRankInScore - lowRankInScore - 1 + Groups[GroupID]->getPlayerInLevelZero()[score];
    }
    else
    {
        total_betweenLevels = highRank - lowRank - 1;
        total_betweenLevelsInScore = highRankInScore - lowRankInScore - 1;
    }
    if (total_betweenLevels == 0 || total_betweenLevelsInScore == 0)
    {
        throw NotExist();
    }

    *players = (total_betweenLevelsInScore / total_betweenLevels) * 100;
    Groups[GroupID]->RemovePlayer(*pLower);
    Groups[GroupID]->RemovePlayer(*pHigher);
    pLower.reset();
    pLower = nullptr;
    pHigher.reset();
    pHigher = nullptr;
}

void GameControl::averageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel)
{
    if (GroupID <= 0 || GroupID > K)
    {
        throw InvalidInput();
    }
    Group *group = Groups[GroupsParent.Find(GroupID)];
    int player_in_level_0 = group->getTotalSumInLevelZero();
    int tree_size = group->getPlayersTree().getSize();
    if (tree_size + player_in_level_0 < m)
    {
        throw OutOfBounds();
    }
    int m_new = m > tree_size ? tree_size : m;
    double sum = group->getPlayersTree().getSumOfBiggestElements(m_new);
    *avgLevel = sum / m;
}

void GameControl::Quit(GameControl *GC)
{
    delete GC;
}

void GameControl::Print()
{
    for (int i = 0; i <= K; i++)
    {
        Groups[i]->Print();
    }
}
