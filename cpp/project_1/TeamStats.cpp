#include "TeamStats.h"
#include "Team.h"

const std::string TeamStats::FILE_PATH = "match_team_stats.data";

TeamStats::TeamStats(Match match, Team team, int goals)
    : match(match), team(team), goals(goals) {}

std::vector<std::string> TeamStats::getArgs() const
{
    return {match.getID(), team.getID(), std::to_string(goals)};
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
        if (args[0] == match.getID())
        {
            stats.push_back(TeamStats(match, Team::idToTeam(args[1]), std::stoi(args[2])));
        }
    }

    return stats;
}

void TeamStats::removeTeamMatchesWithTeamID(std::string teamID)
{
    for (std::string key : findKeysContains(FILE_PATH, teamID))
    {
        Match::idToMatch(key).deleteMatch();
    }
}

std::vector<Match> TeamStats::getMatchesWithTeam(Team team)
{
    std::vector<Match> matches;

    for (std::string key : StorableUnit::findKeysContains(FILE_PATH, team.getID()))
    {
        matches.push_back(Match::idToMatch(key));
    }

    return matches;
}

int TeamStats::getGoals() const
{
    return goals;
}

Team TeamStats::getTeam() const
{
    return team;
}