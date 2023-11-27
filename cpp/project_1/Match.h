#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <array>

#include "util/StorableUnit.h"

class Team;
class TeamStats;

/// @brief A class to represent a match between two teams
class Match : public StorableUnit
{
private:
    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    /// @brief The ID of the match
    std::string matchID;

    /// @brief The date of the match
    std::tm date;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    /// @brief Creates a new match with the given arguments but does not store it in the file
    /// (only used for creating a match object from the file)
    /// @param matchID The ID of the match
    /// @param date The playing date of the match
    Match(std::string matchID, std::tm date);

    /// @brief Creates a new match object without storing it in the file but generates a unique ID for it
    /// @param date The playing date of the match
    Match(std::tm date);
    ~Match();

    /// @brief Creates a new match and stores it in the file using StorableUnit interface
    /// @param teams The teams that played in the match
    void create(std::vector<Team>);

    /// @brief Returns the teams (2) that played in the match as a vector of TeamStats objects
    std::vector<TeamStats> getStats() const;

    /// @brief Returns the team that won the match
    /// @return The team that won the match as a TeamStats object
    TeamStats getWinner() const;

    /// @brief Returns the team that lost the match
    /// @return The team that lost the match as a TeamStats object
    TeamStats getLoser() const;

    /// @brief Returns the ID of the match
    std::string getID() const;

    /// @brief Returns the date of the match
    std::tm getDate() const;

    /// @brief Sets a new date for the match
    void setDate(std::tm);

    /// @brief Deletes the match from the file using StorableUnit interface
    void deleteMatch() const;

    /// @brief Converts a match ID to a match object
    /// @param matchID The ID of the match to convert
    /// @return Match object with the given ID
    static Match idToMatch(std::string);

    /// @brief Get all matches stored in the file as a vector of Match objects
    static std::vector<Match> getAllMatches();

    /// @brief Returns whether the match is a draw
    bool isDraw() const;

    /// @brief Overload of the < operator to compare matches by thier ID to use in sets
    bool operator<(const Match &other) const;
};