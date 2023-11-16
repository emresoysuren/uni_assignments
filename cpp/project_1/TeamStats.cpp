#include "TeamStats.h"
#include "Team.h"

const std::string TeamStats::FILE_PATH = "match_team_stats.data";

TeamStats::TeamStats(std::string statsID, Match match, Team team, int goals)
    : statsID(statsID), match(match), team(team), goals(goals) {}

TeamStats::TeamStats(Match match, Team team, int goals)
    : statsID(Utils::getUUID()), match(match), team(team), goals(goals) {}

std::vector<std::string> TeamStats::getArgs() const
{
    return {statsID, match.getID(), team.getID(), std::to_string(goals)};
}

std::string TeamStats::getPath() const
{
    return FILE_PATH;
}

void TeamStats::save() const
{
    StorableUnit::save();
}

void TeamStats::deleteStats() const
{
    deleteStored();
}

std::vector<TeamStats> TeamStats::getTeamStatsWithMatch(Match match)
{
    std::vector<TeamStats> stats;

    for (std::vector<std::string> args : getAllStored(FILE_PATH))
    {
        if (args[1] == match.getID())
        {
            stats.push_back(TeamStats(args[0], match, Team::idToTeam(args[2]), std::stoi(args[3])));
        }
    }

    return stats;
}

void TeamStats::removeTeamMatchesWithTeamID(std::string teamID)
{
    for (std::vector<std::string> args : findKeysContains(FILE_PATH, teamID))
    {
        Match::idToMatch(args[1]).deleteMatch();
    }
}

std::vector<Match> TeamStats::getMatchesWithTeam(Team team)
{
    std::vector<Match> matches;

    for (std::vector<std::string> args : StorableUnit::findKeysContains(FILE_PATH, team.getID()))
    {
        matches.push_back(Match::idToMatch(args[1]));
    }

    return matches;
}

int TeamStats::getGoals() const
{
    return goals;
}

std::string TeamStats::getID() const
{
    return statsID;
}

Team TeamStats::getTeam() const
{
    return team;
}

Match TeamStats::getMatch() const
{
    return match;
}

TeamStats TeamStats::idToTeamStats(std::string statsID)
{
    std::vector<std::string> stats = getStored(FILE_PATH, statsID);

    return TeamStats(stats[0], Match::idToMatch(stats[1]), Team::idToTeam(stats[2]), std::stoi(stats[3]));
}

void TeamStats::setGoals(int newValue)
{
    goals = newValue;
    resave();
}

void TeamStats::setTeam(Team newValue)
{
    team = newValue;
    resave();
}