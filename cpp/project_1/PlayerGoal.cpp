#include "PlayerGoal.h"
#include "Match.h"
#include "Player.h"
#include "Team.h"
#include "TeamStats.h"

const std::string PlayerGoal::FILE_PATH = "player_goals.data";

std::vector<std::string> PlayerGoal::getArgs() const
{
    return {playerGoalsID, statsID, playerID, std::to_string(time)};
}

std::string PlayerGoal::getPath() const
{
    return FILE_PATH;
}

PlayerGoal::PlayerGoal(std::string playerGoalsID, std::string statsID, std::string playerID, int time)
    : playerGoalsID(playerGoalsID), statsID(statsID), playerID(playerID), time(time) {}

PlayerGoal::PlayerGoal(std::string statsID, std::string playerID, int time)
    : playerGoalsID(generateUniquePrimaryKey(FILE_PATH)), statsID(statsID), playerID(playerID), time(time) {}

PlayerGoal::~PlayerGoal() {}

void PlayerGoal::save() const
{
    StorableUnit::save();
}

PlayerGoal PlayerGoal::idToPlayerGoal(std::string playerGoalID)
{
    return fromArgs(getStored(FILE_PATH, playerGoalID));
}

PlayerGoal PlayerGoal::fromArgs(std::vector<std::string> args)
{
    return PlayerGoal(args[0], args[1], args[2], std::stoi(args[3]));
}

void PlayerGoal::deleteGoal() const
{
    deleteStored();
}

std::vector<PlayerGoal> PlayerGoal::getGoalsWithID(std::string ID)
{
    std::vector<PlayerGoal> result;

    for (std::vector<std::string> args : StorableUnit::findKeysContains(FILE_PATH, ID))
    {
        result.push_back(fromArgs(args));
    }

    return result;
}

void PlayerGoal::deleteGoalsWithID(std::string ID)
{
    deleteOnAnyMatch(FILE_PATH, ID);
}

std::string PlayerGoal::getID() const
{
    return playerGoalsID;
}

TeamStats PlayerGoal::getStats() const
{
    return TeamStats::idToTeamStats(statsID);
}

Player PlayerGoal::getPlayer() const
{
    return Player::idToPlayer(playerID);
}

int PlayerGoal::getTime() const
{
    return time;
}

void PlayerGoal::setTime(int time)
{
    this->time = time;
    resave();
}

void PlayerGoal::setPlayer(Player player)
{
    playerID = player.getID();
    resave();
}