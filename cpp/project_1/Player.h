#pragma once

#include <string>
#include <ctime>
#include <map>
using namespace std;

#include "Team.h"

enum PlayingPosition
{
    kaleci,
    defans,
    ortasaha,
    forvet,
};

class Player
{
private:
    string playerID;
    string name;
    string surname;
    Team team;
    int licenseID;
    PlayingPosition position;
    int salary;
    tm dateOfBirth;

    PlayingPosition stringToPosition(string position)
    {
        static map<string, int> positions = {
            {"kaleci", PlayingPosition::kaleci},
            {"defans", PlayingPosition::defans},
            {"ortasaha", PlayingPosition::ortasaha},
            {"forvet", PlayingPosition::forvet},
        };

        switch (positions[position])
        {
        case 0:
            return PlayingPosition::kaleci;
        case 1:
            return PlayingPosition::defans;
        case 2:
            return PlayingPosition::ortasaha;
        case 3:
            return PlayingPosition::forvet;
        default:
            throw "Pozisyon bulunamadi";
        }
    }

public:
    Player(string playerID, string name, string surname, int teamID, int licenseID, string position, int salary, tm dateOfBirth)
        : playerID(playerID), name(name), surname(surname), team(Team::idToTeam(teamID)), licenseID(licenseID), position(stringToPosition(position)), salary(salary), dateOfBirth(dateOfBirth)
    {
    }
    ~Player() {}
};
