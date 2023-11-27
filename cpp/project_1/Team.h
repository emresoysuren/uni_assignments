#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

#include "util/StorableUnit.h"

class Match;
class Player;

/// @brief A struct that represents a date constraint.
struct DateConstraint
{
    /// @brief The date from which the constraint starts
    std::optional<std::tm> from = std::nullopt;

    /// @brief The date to which the constraint ends
    std::optional<std::tm> to = std::nullopt;

    /// @brief Checks if the given date is in the constraint. If the from or to values are ommited, they will be ignored.
    /// @param date The date to check
    /// @return Whether the date is in the constraint or not
    bool isDateInConstraint(std::tm date) const
    {
        if (from.has_value())
        {
            if (date.tm_year < from.value().tm_year || (date.tm_year == from.value().tm_year && (date.tm_mon < from.value().tm_mon || (date.tm_mon == from.value().tm_mon && date.tm_mday < from.value().tm_mday))))
            {
                return false;
            }
        }

        if (to.has_value())
        {
            if (date.tm_year > to.value().tm_year || (date.tm_year == to.value().tm_year && (date.tm_mon > to.value().tm_mon || (date.tm_mon == to.value().tm_mon && date.tm_mday > to.value().tm_mday))))
            {
                return false;
            }
        }

        return true;
    }
};

/// @brief Class representing a soccer team
class Team : public StorableUnit
{
private:
    /// @brief The path to the file where the data is stored
    static const std::string FILE_PATH;

    /// @brief The ID of the team
    std::string teamID;

    /// @brief The name of the team
    std::string name;

    /// @brief The address of the team
    std::string address;

    /// @brief The phone number of the team
    std::string phoneNumber;

    /// @brief The director of the team
    std::string director;

    // Inherited via StorableUnit (see StorableUnit.h)
    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    /// @brief Creates a new Team object (Without saving it to the file. Only use this to create a team object from the file.)
    /// @param teamID ID of the team
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    Team(std::string teamID, std::string name, std::string address, std::string phoneNumber, std::string director);
    ~Team();

    /// @brief Finds a team by its ID
    /// @param teamID ID of the team to find
    /// @return Returns the team with the given ID or throws an error if it doesn't exist
    static Team idToTeam(std::string teamID);

    /// @brief Deletes the team from the file using the StorableUnit interface
    void deleteTeam() const;

    /// @brief Returns all the teams stored in the file
    static std::vector<Team> getAllTeams();

    /// @brief Creates a new team with a new ID and saves it to the file using the StorableUnit interface
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    static Team createTeam(std::string name, std::string address, std::string phoneNumber, std::string director);

    /// @brief Adds a player to the team using the TeamPlayer class
    void addPlayer(Player) const;

    /// @brief Gets all the players of the team
    std::vector<Player> getPlayers() const;

    // Getter and setters

    /// @brief Gets the name of the team
    std::string getName() const;

    /// @brief Gets the ID of the team
    std::string getID() const;

    /// @brief Gets the address of the team
    std::string getAddr() const;

    /// @brief Gets the phone number of the team
    std::string getPhone() const;

    /// @brief Gets the director of the team
    std::string getDirector() const;

    /// @brief Gets the total goals of the team
    /// @param constraint The date constraint to apply
    /// @return The total goals of the team
    int getTotalGoals(DateConstraint constraint) const;

    /// @brief Gets the total wins of the team
    /// @param constraint The date constraint to apply
    /// @return The total wins of the team
    int getTotalWins(DateConstraint constraint) const;

    /// @brief Gets the total losses of the team
    /// @param constraint The date constraint to apply
    /// @return The total losses of the team
    int getTotalLosses(DateConstraint constraint) const;

    /// @brief Sets the name of the team
    /// @param newValue The new name of the team
    void setName(std::string newValue);

    /// @brief Sets the address of the team
    /// @param newValue The new address of the team
    void setAddr(std::string newValue);

    /// @brief Sets the phone number of the team
    /// @param newValue The new phone number of the team
    void setPhone(std::string newValue);

    /// @brief Sets the director of the team
    /// @param newValue The new director of the team
    void setDirector(std::string newValue);
};
