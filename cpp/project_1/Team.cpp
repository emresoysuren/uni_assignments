#include "Team.h"

const string Team::FILE_PATH = "teams.data";
const string Team::TEAM_PLAYER_FILE_PATH = "team_player.data";

/// @brief Converts a string to a Team object
/// @param line String to convert
/// @return Returns the converted Team object
Team Team::fromString(string line)
{
    string word;
    stringstream ss(line);
    vector<string> result;

    while (getline(ss, word, ' '))
    {
        result.push_back(word);
    }

    return Team(result[0], result[1], result[2], result[3], result[4]);
}

void Team::saveTeam(Team team)
{
    ofstream file(FILE_PATH, ios::app);

    file << team.teamID << " " << team.name << " " << team.address << " " << team.phoneNumber << " " << team.director << endl;

    file.close();
}

Team::Team(string teamID, string name, string address, string phoneNumber, string director)
    : teamID(teamID), name(name), address(address), phoneNumber(phoneNumber), director(director)
{
}

Team::~Team() {}

Team Team::idToTeam(string teamID)
{
    string line;

    ifstream file(FILE_PATH, ios::app);

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

void Team::deleteTeam(string teamID)
{
    removeTeamOrPlayerWithID(teamID);

    ifstream rfile(FILE_PATH);
    ofstream temp("temp.data");

    string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != teamID)
        {
            temp << line << endl;
        }
    }

    rfile.close();
    temp.close();

    remove(FILE_PATH.c_str());
    rename("temp.data", FILE_PATH.c_str());
}

vector<Team> Team::getAllTeams()
{
    vector<Team> teams;
    string line;

    ifstream file(FILE_PATH, ios::app);

    while (getline(file, line))
    {
        teams.push_back(fromString(line));
    }

    file.close();

    return teams;
};

Team Team::createTeam(string name, string address, string phoneNumber, string director)
{
    // @todo Create UUIDs instead of giving random numbers
    Team team(to_string(rand()), name, address, phoneNumber, director);

    saveTeam(team);

    cout << "Team created: " << team.teamID << " " << team.name << " " << team.address << " " << team.phoneNumber << " " << team.director << endl;

    return team;
}

string Team::getName()
{
    return name;
}

string Team::getID()
{
    return teamID;
}

void Team::addPlayer(string playerID)
{
    ifstream file(TEAM_PLAYER_FILE_PATH);

    string line;

    while (getline(file, line))
    {
        if (line.substr(line.find(" ") + 1) == playerID)
        {
            file.close();
            return;
        }
    }

    file.close();

    ofstream wfile(TEAM_PLAYER_FILE_PATH, ios::app);

    wfile << teamID << " " << playerID << endl;

    wfile.close();
}

vector<Player> Team::getPlayers()
{
    ifstream file(TEAM_PLAYER_FILE_PATH, ios::app);

    vector<Player> players;

    string line;

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

void Team::removeTeamOrPlayerWithID(string ID)
{
    ifstream rfile(TEAM_PLAYER_FILE_PATH);
    ofstream temp("temp.data");

    string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != ID && line.substr(line.find(" ") + 1) != ID)
        {
            temp << line << endl;
        }
    }

    rfile.close();
    temp.close();

    remove(TEAM_PLAYER_FILE_PATH.c_str());
    rename("temp.data", TEAM_PLAYER_FILE_PATH.c_str());
}
