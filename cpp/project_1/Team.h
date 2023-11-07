#pragma once

#include <string>
using namespace std;

/// @brief Class representing a soccer team
class Team
{
private:
    int teamID;
    string name;
    string adress;
    string phoneNumber;
    unsigned int playerCount;
    string director;

public:
    /// @brief Creates a new Team object
    /// @param teamID ID of the team
    /// @param name Name of the team
    /// @param adress Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param playerCount Total number of players in the team
    /// @param director Current director of the team
    Team(int teamID, string name, string adress, string phoneNumber, unsigned int playerCount, string director)
        : teamID(teamID), name(name), adress(adress), phoneNumber(phoneNumber), playerCount(playerCount), director(director)
    {
    }
    ~Team() {}

    /// @brief Finds a team by its ID
    /// @param teamID ID of the team to find
    /// @return Returns the team with the given ID
    static Team idToTeam(int teamID)
    {
        return Team(teamID, "", "", "", 0, "");
    }
};
