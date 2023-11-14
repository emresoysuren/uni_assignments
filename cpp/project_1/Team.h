#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Match;
class Player;

/// @brief Class representing a soccer team
class Team
{
private:
    static const std::string FILE_PATH;
    static const std::string TEAM_PLAYER_FILE_PATH;
    std::string teamID;
    std::string name;
    std::string address;
    std::string phoneNumber;
    std::string director;

    /// @brief Converts a string to a Team object
    /// @param line String to convert
    /// @return Returns the converted Team object
    static Team fromString(std::string line);

    void save() const;
    void resave() const;

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

    static void deleteTeam(std::string teamID);

    static std::vector<Team> getAllTeams();

    /// @brief Creates a new team with a new ID
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    static Team createTeam(std::string name, std::string address, std::string phoneNumber, std::string director);

    void addPlayer(std::string playerID) const;

    std::vector<Player> getPlayers() const;

    static void removeTeamOrPlayerWithID(std::string ID);

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
