#pragma once

#include <vector>
#include <string>

#include "util/StorableUnit.h"

class Match;
class Player;
class Team;
class TeamStats;

/// @brief A class that represents a player's goal in a match
class PlayerGoal : public StorableUnit
{
private:
    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    /// @brief The unique identifier of the player's goal
    std::string playerGoalsID;

    /// @brief The team stats that the goal was scored in (using this to get the match, team, etc.)
    std::string statsID;

    /// @brief The player that scored the goal
    std::string playerID;

    /// @brief The time that the goal was scored in the match (in seconds from the start of the match)
    int time;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

    /// @brief Creates a new player goal object with the given arguments
    static PlayerGoal fromArgs(std::vector<std::string>);

public:
    /// @brief Creates a new player goal object with the given arguments
    /// @param playerGoalsID The unique identifier of the player's goal
    /// @param statsID The team stats identifier that the goal was scored in
    /// @param playerID The player identifier that scored the goal
    /// @param time The time that the goal was scored in the match (in seconds from the start of the match)
    PlayerGoal(std::string playerGoalsID, std::string statsID, std::string playerID, int time);

    /// @brief Creates a new player goal object with the given arguments. Generates a unique identifier
    /// @param statsID The team stats identifier that the goal was scored in
    /// @param playerID The player identifier that scored the goal
    /// @param time The time that the goal was scored in the match (in seconds from the start of the match)
    PlayerGoal(std::string statsID, std::string playerID, int time);
    ~PlayerGoal();

    /// @brief Gets the player goal object with the given ID
    /// @param playerGoalID The ID of the player goal to get
    static PlayerGoal idToPlayerGoal(std::string playerGoalID);

    /// @brief Finds and returns all player goals with the given ID (ID can be any stored ID)
    /// @param ID The ID to search for
    /// @return Returns all player goals with the given ID
    static std::vector<PlayerGoal> getGoalsWithID(std::string ID);

    /// @brief Deletes all player goals with the given ID (ID can be any stored ID)
    /// @param ID The ID to search for
    static void deleteGoalsWithID(std::string ID);

    /// @brief Saves the player goal to the file using the StorableUnit interface
    void save() const;

    /// @brief Deletes the player goal from the file using the StorableUnit interface
    void deleteGoal() const;

    /// @brief Gets the unique identifier of the player's goal
    std::string getID() const;

    /// @brief Gets the team stats that the goal was scored in (using this to get the match, team, etc.)
    TeamStats getStats() const;

    /// @brief Gets the player that scored the goal
    Player getPlayer() const;

    /// @brief Gets the time that the goal was scored in the match (in seconds from the start of the match)
    int getTime() const;

    /// @brief Sets the time that the goal was scored in the match (in seconds from the start of the match)
    void setTime(int time);

    /// @brief Changes the player that scored the goal
    void setPlayer(Player player);
};