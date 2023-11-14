#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <array>

class Utils;
class Team;

#include "TeamStats.h"
class TeamStats;

class Match
{
private:
    static const std::string FILE_PATH;
    static const std::string STATS_FILE_PATH;
    std::string matchID;
    TeamStats team1;
    TeamStats team2;
    std::tm date;

    void saveMatch() const;

    void saveStats() const;

    static Match fromString(std::string line);

public:
    Match(std::string matchID, std::tm date, TeamStats team1, TeamStats team2);
    ~Match();

    static Match createMatch(std::tm date, TeamStats team1, TeamStats team2);

    TeamStats getWinner() const;

    TeamStats getLoser() const;

    std::string getID() const;

    std::tm getDate() const;

    static void deleteMatch(std::string matchID);

    static std::vector<Match> getAllMatches();

    static void deleteStatsOfMatchWithID(std::string matchID);

    static void deleteStatsOfTeamWithID(std::string playerID);
};