#pragma once

#include <vector>
#include <string>

#include "util/StorableUnit.h"

class Match;
class Player;
class Team;
class TeamStats;

class PlayerGoal : public StorableUnit
{
private:
    static const std::string FILE_PATH;
    std::string playerGoalsID;
    std::string statsID;
    std::string playerID;
    int time;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

    static PlayerGoal fromArgs(std::vector<std::string>);

public:
    PlayerGoal(std::string playerGoalsID, std::string stats, std::string playerID, int time);
    PlayerGoal(std::string, std::string, int time);
    ~PlayerGoal();

    static PlayerGoal idToPlayerGoal(std::string playerGoalID);
    static std::vector<PlayerGoal> getGoalsWithStatsID(std::string statsID);
    static void deleteGoalsWithID(std::string ID);

    void save() const;
    void deleteGoal() const;

    std::string getID() const;
    TeamStats getStats() const;
    Player getPlayer() const;
    int getTime() const;

    void setTime(int time);
    void setPlayer(Player player);
};