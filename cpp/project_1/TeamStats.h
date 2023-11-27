#pragma once

#include <string>
#include <vector>

#include "util/StorableUnit.h"

#include "PlayerGoal.h"
class PlayerGoal;

#include "Match.h"
class Match;

#include "Team.h"
class Team;

class Player;

/// @brief A class that represents a team's information in a match
class TeamStats : public StorableUnit
{
private:
    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    /// @brief The unique identifier of the team's stats
    std::string statsID;

    /// @brief The match in which the team played
    Match match;

    /// @brief The team that played the match
    Team team;

    /// @brief The goals scored by the team with the player that scored them and the time
    std::vector<PlayerGoal> goals;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

    /// @brief Creates a new team stats object with the given arguments
    static TeamStats fromArgs(std::vector<std::string>);

public:
    /// @brief Creates a new team stats object with the given arguments
    /// @param statsID The unique identifier of the team's stats
    /// @param match The match in which the team played
    /// @param team The team that played the match
    /// @param goals The goals scored by the team with the player that scored them and the time
    TeamStats(std::string statsID, Match match, Team team, std::vector<PlayerGoal> goals);

    /// @brief Creates a new team stats object with the given arguments
    /// @param match The match in which the team played
    /// @param team The team that played the match
    TeamStats(Match match, Team team);

    /// @brief Saves the team stats to the file using the StorableUnit interface
    void save() const;

    /// @brief Deletes the team stats from the file using the StorableUnit interface
    /// and does other related operations
    void deleteStats() const;

    /// @brief Returns a vector of all the team stats objects that have the given match
    /// @param match The match to search for
    /// @return A vector of all the team stats objects that have the given match
    static std::vector<TeamStats> getTeamStatsWithMatch(Match match);

    /// @brief Returns a vector of all the match objects that have the given team
    /// @param team The team to search for
    /// @return A vector of all the match objects that have the given team
    static std::vector<Match> getMatchesWithTeam(Team team);

    /// @brief Removes all the match objects that have the given team
    /// @param teamID The team's unique identifier
    static void removeTeamMatchesWithTeamID(std::string teamID);

    /// @brief Returns the team stats object with the given unique identifier
    /// @param statsID The team stats' unique identifier
    static TeamStats idToTeamStats(std::string statsID);

    /// @brief Returns the team stats object with the given unique identifier
    std::string getID() const;

    /// @brief Returns the team that played the match
    Team getTeam() const;

    /// @brief Returns the match in which the team played
    Match getMatch() const;

    /// @brief Returns the player goal objects of the team in the match
    std::vector<PlayerGoal> getGoals() const;

    /// @brief Adds a goal to the team in the match
    /// @param player The player that scored the goal
    /// @param time The time in which the goal was scored (in seconds from the start of the match)
    void addGoal(Player player, int time) const;

    /// @brief Removes a goal from the team in the match
    void removeGoal(std::string playerGoalID) const;

    /// @brief Changes the team that played the match.
    /// This function also deletes all the player goals of the current team stats
    /// @param team The new team that played the match
    void changeTeam(Team team);
};