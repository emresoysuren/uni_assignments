#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <optional>

#include "util/StorableUnit.h"
#include "StatsInfo.h"

class Utils;
class Team;
class DateConstraint;

/// @brief Enum to represent the position of a player playing in a team
enum PlayingPosition
{
    keeper,
    defender,
    midfielder,
    forward,
};

/// @brief A class to represent a player
class Player : public StorableUnit
{
private:
    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    /// @brief The ID of the player
    std::string playerID;

    /// @brief The name of the player
    std::string name;

    /// @brief The surname of the player
    std::string surname;

    /// @brief The license ID of the player
    std::string licenseID;

    /// @brief The position of the player playing in the team (keeper, defender, midfielder, forward)
    PlayingPosition position;

    /// @brief The salary of the player
    int salary;

    /// @brief The date of birth of the player
    std::tm dateOfBirth;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    /// @brief Creates a new Player object but doesn't save it to the file
    /// (Only used for creating a Player object from the file)
    /// @param playerID ID of the player
    /// @param name Name of the player
    /// @param surname Surame of the player
    /// @param position The position of the player playing in the team
    /// @param salary Salary of the player
    /// @param dateOfBirth Date of birth of the player
    Player(std::string playerID, std::string name, std::string surname, std::string licenseID, PlayingPosition position, int salary, tm dateOfBirth);

    ~Player();

    /// @brief Creates a new Player object and saves it to the file using the StorableUnit interface
    static Player createPlayer(std::string name, std::string surname, std::string licenseID, PlayingPosition position, int salary, tm dateOfBirth);

    /// @brief Deletes the player from the file (also deletes all the related data)
    /// using the StorableUnit interface
    void deletePlayer() const;

    /// @brief Converts a number to a PlayingPosition
    /// @param position Position of the player as a number
    /// @return Returns the PlayingPosition corresponding to the given number
    static PlayingPosition numToPosition(int position);

    /// @brief Converts a PlayingPosition to a string (keeper, defender, midfielder, forward)
    static std::string positionToString(int);

    /// @brief Gets all players stored in the file
    /// @return Returns all the players stored in the file as Player objects in a vector
    static std::vector<Player> getAllPlayers();

    /// @brief Converts a player ID to a player
    /// @param playerID ID of the player
    /// @return Player object with the given ID
    static Player idToPlayer(std::string playerID);

    /// @brief Gets the team that the player plays for
    std::optional<Team> getTeam() const;

    /// @brief Gets the ID of the player
    std::string getID() const;

    /// @brief Gets the name of the player
    std::string getName() const;

    /// @brief Gets the surname of the player
    std::string getSurname() const;

    /// @brief Gets the date of birth of the player
    std::tm getDate() const;

    /// @brief Gets the salary of the player
    int getSalary() const;

    /// @brief Gets the position of the player playing in the team (keeper, defender, midfielder, forward)
    PlayingPosition getPosition() const;

    /// @brief Gets the license ID of the player
    std::string getLicenseID() const;

    /// @brief Gets the stats of the player in the given date constraint
    /// @param constraint The date constraint to get the stats in
    /// @return The stats of the player in the given date constraint (goals, wins, draws, losses)
    StatsInfo getStats(DateConstraint constraint) const;

    /// @brief Sets the date of birth of the player
    void setDate(std::tm date);

    /// @brief Sets the name of the player
    void setName(std::string name);

    /// @brief Sets the surname of the player
    void setSurname(std::string surname);

    /// @brief Sets the salary of the player
    void setSalary(int salary);

    /// @brief Sets the position of the player
    void setPosition(PlayingPosition position);

    /// @brief Sets the license ID of the player
    void setLicenseID(std::string licenseID);
};
