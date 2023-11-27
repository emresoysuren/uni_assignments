#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <array>

#include "util/StorableUnit.h"

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

    void create(std::vector<Team>);

    std::vector<TeamStats> getStats() const;

    TeamStats getWinner() const;

    TeamStats getLoser() const;

    std::string getID() const;

    std::tm getDate() const;

    void setDate(std::tm);

    void deleteMatch() const;

    static Match idToMatch(std::string);

    static std::vector<Match> getAllMatches();

    bool isDraw() const;

    bool operator<(const Match &other) const;
};