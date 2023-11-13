#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <map>

class Utils;
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
    static const std::string FILE_PATH;
    std::string playerID;
    std::string name;
    std::string surname;
    int licenseID;
    PlayingPosition position;
    int salary;
    std::tm dateOfBirth;

    void save() const;

public:
    /// @brief Creates a new Player object
    /// @param playerID ID of the player
    /// @param name Name of the player
    /// @param surname Surame of the player
    /// @param position The position of the player playing in the team
    /// @param salary Salary of the player
    /// @param dateOfBirth Date of birth of the player
    Player(std::string playerID, std::string name, std::string surname, int licenseID, PlayingPosition position, int salary, tm dateOfBirth);

    ~Player();

    static Player createPlayer(std::string name, std::string surname, PlayingPosition position, int salary, tm dateOfBirth);

    static void deletePlayer(std::string playerID);

    /// @brief Converts a number to a PlayingPosition
    /// @param position Position of the player as a number
    /// @return Returns the PlayingPosition corresponding to the given number
    static PlayingPosition numToPosition(int position);

    static std::vector<Player> getAllPlayers();

    static Player fromString(std::string line);

    static Player idToPlayer(std::string playerID);

    std::string getID() const;

    std::string getName() const;

    std::string getSurname() const;
};
