#pragma once

#include <string>
#include <ctime>
#include <map>
using namespace std;

#include "Team.h"

/// @brief Enum to represent the position of a player playing in a team
enum PlayingPosition
{
    keeper,
    defender,
    midfielder,
    forward,
};

/// @brief A class to represent a player
class Player
{
private:
    string playerID;
    string name;
    string surname;
    Team team;
    int licenseID;
    PlayingPosition position;
    int salary;
    tm dateOfBirth;

    /// @brief Converts a number to a PlayingPosition
    /// @param position Position of the player as a number
    /// @return Returns the PlayingPosition corresponding to the given number
    static PlayingPosition numToPosition(int position)
    {
        static map<int, PlayingPosition> positions = {
            {PlayingPosition::keeper, PlayingPosition::keeper},
            {PlayingPosition::defender, PlayingPosition::defender},
            {PlayingPosition::midfielder, PlayingPosition::midfielder},
            {PlayingPosition::forward, PlayingPosition::forward},
        };

        return positions[position];
    }

public:
    /// @brief Creates a new Player object
    /// @param playerID ID of the player
    /// @param name Name of the player
    /// @param surname Surame of the player
    /// @param teamID The id of the team the player is in
    /// @param licenseID License ID of the player
    /// @param position The position of the player playing as a number
    /// @param salary Salary of the player
    /// @param dateOfBirth Date of birth of the player
    Player(string playerID, string name, string surname, int teamID, int licenseID, int position, int salary, tm dateOfBirth)
        : playerID(playerID), name(name), surname(surname), team(Team::idToTeam(teamID)), licenseID(licenseID), position(numToPosition(position)), salary(salary), dateOfBirth(dateOfBirth)
    {
    }
    ~Player() {}
};
