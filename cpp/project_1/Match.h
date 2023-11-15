#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <array>

#include "util/StorableUnit.h"

class Utils;
class Team;
class TeamStats;

class Match : public StorableUnit
{
private:
    static const std::string FILE_PATH;
    std::string matchID;
    std::tm date;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    Match(std::string matchID, std::tm date);
    Match(std::tm date);
    ~Match();

    void create(TeamStats team1, TeamStats team2);

    std::vector<TeamStats> getStats() const;

    TeamStats getWinner() const;

    TeamStats getLoser() const;

    std::string getID() const;

    std::tm getDate() const;

    void deleteMatch() const;

    static Match idToMatch(std::string);

    static std::vector<Match> getAllMatches();
};