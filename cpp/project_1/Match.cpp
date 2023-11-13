#include "Match.h"
#include "util/Utils.h"
#include "Team.h"
#include "TeamStats.h"

const std::string Match::FILE_PATH = "matches.data";
const std::string Match::STATS_FILE_PATH = "match_team_stats.data";

Match::Match(std::string ID, std::tm date, TeamStats team1, TeamStats team2)
    : matchID(ID), date(date), team1(team1), team2(team2) {}

Match::~Match() {}

TeamStats Match::getWinner() const
{
    if (team1.getGoals() > team2.getGoals())
    {
        return team1;
    }

    return team2;
}

TeamStats Match::getLoser() const
{
    if (team1.getGoals() > team2.getGoals())
    {
        return team2;
    }

    return team1;
}

void Match::saveMatch() const
{
    std::ofstream file(FILE_PATH, std::ios::app);

    file << getID() << " " << Utils::dateToString(date) << std::endl;

    file.close();
}

void Match::saveStats() const
{
    std::ofstream file(STATS_FILE_PATH, std::ios::app);

    file << getID() << " " << team1.getTeam().getID() << " " << team1.getGoals() << std::endl;

    file << getID() << " " << team2.getTeam().getID() << " " << team2.getGoals() << std::endl;

    file.close();
}

std::string Match::getID() const
{
    return matchID;
}

Match Match::createMatch(std::tm date, TeamStats team1, TeamStats team2)
{
    Match match = Match(std::to_string(rand()), date, team1, team2);

    match.saveMatch();
    match.saveStats();

    return match;
}

void Match::deleteMatch(std::string matchID)
{
    deleteStatsOfMatchWithID(matchID);

    std::ifstream rfile(FILE_PATH);
    std::ofstream temp("temp.data");

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != matchID)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(FILE_PATH.c_str());
    rename("temp.data", FILE_PATH.c_str());
}

void Match::deleteStatsOfMatchWithID(std::string matchID)
{
    std::ifstream rfile(STATS_FILE_PATH);
    std::ofstream temp("temp.data");

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != matchID)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(STATS_FILE_PATH.c_str());
    rename("temp.data", STATS_FILE_PATH.c_str());
}

void Match::deleteStatsOfTeamWithID(std::string playerID)
{
    std::ifstream rfile(STATS_FILE_PATH);

    std::string line;

    while (getline(rfile, line))
    {
        std::vector<std::string> args = Utils::spiltString(line, ' ');

        if (args[1] == playerID)
        {
            deleteMatch(args[0]);
        }
    }

    rfile.close();
}

std::vector<Match> Match::getAllMatches()
{
    std::vector<Match> mathes;
    std::string line;

    std::ifstream file(FILE_PATH);

    while (getline(file, line))
    {
        mathes.push_back(fromString(line));
    }

    file.close();

    return mathes;
}

Match Match::fromString(std::string str)
{
    std::ifstream file(STATS_FILE_PATH);

    std::string line;

    TeamStats *stats = (TeamStats *)calloc(2, sizeof(TeamStats));

    short statsSaveCount = 0;

    while (getline(file, line) && statsSaveCount < 2)
    {
        if (line.substr(0, line.find(" ")) == str.substr(0, str.find(" ")))
        {
            std::stringstream ss(line);

            std::string *args = new std::string[3];

            std::string word;

            for (int i = 0; i < 3; i++)
            {
                getline(ss, word, ' ');
                args[i] = word;
            }

            *(stats + statsSaveCount) = TeamStats(Team::idToTeam(args[1]), stoi(args[2]));

            statsSaveCount++;

            delete[] args;
        }
    }

    Match match = Match(str.substr(0, str.find(" ")), Utils::stringToDate(str.substr(str.find(" "))), *stats, *(stats + 1));

    delete stats;

    file.close();

    return match;
}
