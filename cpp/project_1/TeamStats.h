#pragma once

#include "Match.h"
class Match;

#include "Team.h"
class Team;

#include "util/StorableUnit.h"

class TeamStats : public StorableUnit
{
private:
    static const std::string FILE_PATH;
    std::string statsID;
    Match match;
    Team team;
    int goals;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    TeamStats(std::string, Match, Team, int = 0);

    TeamStats(Match, Team, int = 0);

    void save() const;

    void deleteStats() const;

    static std::vector<TeamStats> getTeamStatsWithMatch(Match);

    static std::vector<Match> getMatchesWithTeam(Team);

    static void removeTeamMatchesWithTeamID(std::string);

    static TeamStats idToTeamStats(std::string);

    int getGoals() const;

    std::string getID() const;

    Team getTeam() const;

    Match getMatch() const;

    void setGoals(int);

    void setTeam(Team);
};