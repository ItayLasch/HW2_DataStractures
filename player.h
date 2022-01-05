#ifndef PLAYER
#define PLAYER

class Player
{
    int player_id;
    int level;
    int score;
    int group_id;

    public:

    Player(int player_id = 0, int score = 0, int group_id = 0, int level = 0): player_id(player_id), score(score), group_id(group_id), level(level){};
    Player(const Player &other) = default;
    ~Player() = default;

    int getPlayerId()
    {
        return player_id;
    }
    int getLevel()
    {
        return level;
    }
    int getScore()
    {
        return score;
    }
    int getGroupId(){
        return group_id;
    }
    void setLevel(int new_level){
        this->level = new_level;
    }
    void addToLevel(int add){
        this->level += add;
    }
    void setScore(int new_score){
        this->score = new_score;
    }
    void setGroup(int new_group_id){
        this->group_id = new_group_id;
    }

    friend bool operator==(const Player &p1, const Player &p2)
    {
        return (p1.player_id == p2.player_id && p1.level == p2.level);
    }

    friend bool operator<(const Player &p1, const Player &p2)
    {
        int res = p1.level - p2.level;
        if (res < 0 || (res == 0 && p1.player_id < p2.player_id))
        {
            return true;
        }
        return false;
    }

    friend bool operator>(const Player &p1, const Player &p2)
    {
        if (p1 < p2 || p1 == p2)
        {
            return false;
        }
        return true;
    }

};

#endif