#include "Team.h"
#include "Match.h"
#include "Player.h"

const std::string Team::FILE_PATH = "teams.data";
const std::string Team::TEAM_PLAYER_FILE_PATH = "team_player.data";

/// @brief Converts a string to a Team object
/// @param line String to convert
/// @return Returns the converted Team object
Team Team::fromString(std::string line)
{
    std::string word;
    std::stringstream ss(line);
    std::vector<std::string> result;

    while (getline(ss, word, ' '))
    {
        result.push_back(word);
    }

    return Team(result[0], result[1], result[2], result[3], result[4]);
}

void Team::save() const
{
    std::ofstream file(FILE_PATH, std::ios::app);

    file << teamID << " " << name << " " << address << " " << phoneNumber << " " << director << std::endl;

    file.close();
}

Team::Team(std::string teamID, std::string name, std::string address, std::string phoneNumber, std::string director)
    : teamID(teamID), name(name), address(address), phoneNumber(phoneNumber), director(director)
{
}

Team::~Team() {}

Team Team::idToTeam(std::string teamID)
{
    std::string line;

    std::ifstream file(FILE_PATH);

    while (getline(file, line))
    {
        if (line.substr(0, line.find(" ")) == teamID)
        {
            return fromString(line);
        }
    }

    file.close();

    throw "Team not found";
};

void Team::deleteTeam(std::string teamID)
{
    removeTeamOrPlayerWithID(teamID);
    Match::deleteStatsOfTeamWithID(teamID);

    std::ifstream rfile(FILE_PATH);
    std::ofstream temp("temp.data");

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != teamID)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(FILE_PATH.c_str());
    rename("temp.data", FILE_PATH.c_str());
}

std::vector<Team> Team::getAllTeams()
{
    std::vector<Team> teams;
    std::string line;

    std::ifstream file(FILE_PATH, std::ios::app);

    while (getline(file, line))
    {
        teams.push_back(fromString(line));
    }

    file.close();

    return teams;
};

Team Team::createTeam(std::string name, std::string address, std::string phoneNumber, std::string director)
{
    // @todo Create UUIDs instead of giving random numbers
    Team team(std::to_string(rand()), name, address, phoneNumber, director);

    team.save();

    return team;
}

std::string Team::getName() const
{
    return name;
}

std::string Team::getID() const
{
    return teamID;
}

void Team::addPlayer(std::string playerID) const
{
    std::ifstream file(TEAM_PLAYER_FILE_PATH);

    std::string line;

    while (getline(file, line))
    {
        if (line.substr(line.find(" ") + 1) == playerID)
        {
            file.close();
            return;
        }
    }

    file.close();

    std::ofstream wfile(TEAM_PLAYER_FILE_PATH, std::ios::app);

    wfile << teamID << " " << playerID << std::endl;

    wfile.close();
}

std::vector<Player> Team::getPlayers() const
{
    std::ifstream file(TEAM_PLAYER_FILE_PATH, std::ios::app);

    std::vector<Player> players;

    std::string line;

    while (getline(file, line))
    {
        if (line.substr(0, line.find(" ")) == teamID)
        {
            players.push_back(Player::idToPlayer(line.substr(line.find(" ") + 1)));
        }
    }

    file.close();

    return players;
}

void Team::removeTeamOrPlayerWithID(std::string ID)
{
    std::ifstream rfile(TEAM_PLAYER_FILE_PATH);
    std::ofstream temp("temp.data");

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != ID && line.substr(line.find(" ") + 1) != ID)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(TEAM_PLAYER_FILE_PATH.c_str());
    rename("temp.data", TEAM_PLAYER_FILE_PATH.c_str());
}
