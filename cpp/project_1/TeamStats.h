#pragma once

#include <string>
#include <vector>

#include "util/StorableUnit.h"

#include "PlayerGoal.h"
class PlayerGoal;

#include "Match.h"
class Match;

#include "Team.h"
class Team;

class Player;

class TeamStats : public StorableUnit
{
private:
    static const std::string FILE_PATH;
    std::string statsID;
    Match match;
    Team team;
    std::vector<PlayerGoal> goals;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

    static TeamStats fromArgs(std::vector<std::string>);

public:
    TeamStats(std::string, Match, Team, std::vector<PlayerGoal>);

    TeamStats(Match, Team);

    void save() const;

    void deleteStats() const;

    static std::vector<TeamStats> getTeamStatsWithMatch(Match);

    static std::vector<Match> getMatchesWithTeam(Team);

    static void removeTeamMatchesWithTeamID(std::string);

    static TeamStats idToTeamStats(std::string);

    std::string getID() const;

    Team getTeam() const;

    Match getMatch() const;

    std::vector<PlayerGoal> getGoals() const;
    void addGoal(Player player, int time) const;
    void removeGoal(std::string playerGoalID) const;

    void changeTeam(Team);
};