#pragma once

#include <optional>
#include <string>
#include <vector>

#include "util/StorableUnit.h"

#include "Team.h"
class Team;

#include "Player.h"
class Player;

/// @brief A class that represents a team-player relationship and stores it in a file
class TeamPlayer : public StorableUnit
{
private:
    /// @brief The team that the player plays for
    Team team;

    /// @brief The player that plays for the team
    Player player;

    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    /// @brief Creates a new team-player relationship with the given arguments
    /// @param team The team that the player plays for
    /// @param player The player that plays for the team
    TeamPlayer(Team team, Player player);
    ~TeamPlayer();

    /// @brief Saves the team-player relationship to the file using the StorableUnit interface.
    /// Objects are saved in teamID and playerID pairs
    /// (doesn't save if the team-player relationship already exists)
    void save() const;

    /// @brief Gets the players that play for the given team
    /// @param team The team to get the players of
    /// @return The players that play for the given team
    static std::vector<Player> getPlayersOfTeam(Team team);

    /// @brief Gets the team that the given player plays for
    /// @param player The player to get the team of
    /// @return The team that the given player plays for
    static std::optional<Team> getTeamOfPlayer(Player player);

    /// @brief Removes the team-player relationship with the given ID
    static void removeTeamOrPlayerWithID(std::string ID);
};