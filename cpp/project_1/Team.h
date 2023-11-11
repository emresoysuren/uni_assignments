#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "Player.h"

class Player;

/// @brief Class representing a soccer team
class Team
{
private:
    static const string FILE_PATH;
    static const string TEAM_PLAYER_FILE_PATH;
    string teamID;
    string name;
    string address;
    string phoneNumber;
    string director;

    /// @brief Converts a string to a Team object
    /// @param line String to convert
    /// @return Returns the converted Team object
    static Team fromString(string line);

    static void saveTeam(Team team);

public:
    /// @brief Creates a new Team object
    /// @param teamID ID of the team
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    Team(string teamID, string name, string address, string phoneNumber, string director);
    ~Team();

    /// @brief Finds a team by its ID
    /// @param teamID ID of the team to find
    /// @return Returns the team with the given ID or throws an error if it doesn't exist
    static Team idToTeam(string teamID);

    static void deleteTeam(string teamID);

    static vector<Team> getAllTeams();

    /// @brief Creates a new team with a new ID
    /// @param name Name of the team
    /// @param address Adress of the team
    /// @param phoneNumber Phone number of the team
    /// @param director Current director of the team
    static Team createTeam(string name, string address, string phoneNumber, string director);

    string getName();

    string getID();

    void addPlayer(string playerID);

    vector<Player> getPlayers();

    static void removeTeamOrPlayerWithID(string ID);
};
