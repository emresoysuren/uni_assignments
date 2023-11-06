#pragma once

#include <string>
using namespace std;

class Team
{
private:
    int teamID;
    string name;
    string adress;
    string phoneNumber;
    unsigned int playerCount;
    string director;

public:
    Team(int teamID, string name, string adress, string phoneNumber, unsigned int playerCount, string director)
        : teamID(teamID), name(name), adress(adress), phoneNumber(phoneNumber), playerCount(playerCount), director(director)
    {
    }
    ~Team() {}

    static Team idToTeam(int teamID)
    {
        return Team(teamID, "", "", "", 0, "");
    }
};
