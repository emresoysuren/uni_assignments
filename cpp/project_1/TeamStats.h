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
    Match match;
    Team team;
    int goals;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    TeamStats(Match, Team, int = 0);

    void save() const;

    void deleteStats() const;

    static std::vector<TeamStats> getTeamStatsWithMatch(Match);

    static void removeTeamMatchesWithTeamID(std::string);

    int getGoals() const;

    Team getTeam() const;
};