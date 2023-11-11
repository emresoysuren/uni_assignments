#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <map>
using namespace std;

#include "Team.h"

class Team;

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
    static const string FILE_PATH;
    string playerID;
    string name;
    string surname;
    int licenseID;
    PlayingPosition position;
    int salary;
    tm dateOfBirth;

    static void savePlayer(Player player);

public:
    /// @brief Creates a new Player object
    /// @param playerID ID of the player
    /// @param name Name of the player
    /// @param surname Surame of the player
    /// @param position The position of the player playing in the team
    /// @param salary Salary of the player
    /// @param dateOfBirth Date of birth of the player
    Player(string playerID, string name, string surname, int licenseID, PlayingPosition position, int salary, tm dateOfBirth);

    ~Player();

    static Player createPlayer(string name, string surname, PlayingPosition position, int salary, tm dateOfBirth);

    static void deletePlayer(string playerID);

    /// @brief Converts a number to a PlayingPosition
    /// @param position Position of the player as a number
    /// @return Returns the PlayingPosition corresponding to the given number
    static PlayingPosition numToPosition(int position);

    static vector<Player> getAllPlayers();

    static Player fromString(string line);

    static Player idToPlayer(string playerID);

    string getID();

    string getName();

    string getSurname();
};
