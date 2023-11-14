#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "util/StorableUnit.h"

class Match;
class Player;

/// @brief Class representing a soccer team
class Team : public StorableUnit
{
private:
    static const std::string FILE_PATH;
    std::string teamID;
    std::string name;
    std::string address;
    std::string phoneNumber;
    std::string director;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    /// @brief Creates a new Team object
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

    void deleteTeam() const;

    static std::vector<Team> getAllTeams();

    /// @brief Creates a new team with a new ID
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    static Team createTeam(std::string name, std::string address, std::string phoneNumber, std::string director);

    void addPlayer(Player) const;

    std::vector<Player> getPlayers() const;

    // Getter and setters

    std::string getName() const;

    std::string getID() const;

    std::string getAddr() const;

    std::string getPhone() const;

    std::string getDirector() const;

    void setName(std::string);

    void setAddr(std::string);

    void setPhone(std::string);

    void setDirector(std::string);
};
