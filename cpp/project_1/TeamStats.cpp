#include "TeamStats.h"
#include "Match.h"
#include "PlayerGoal.h"
#include "Team.h"
#include "Player.h"

const std::string TeamStats::FILE_PATH = "match_team_stats.data";

TeamStats::TeamStats(std::string statsID, Match match, Team team, std::vector<PlayerGoal> goals)
    : statsID(statsID), match(match), team(team), goals(goals) {}

TeamStats::TeamStats(Match match, Team team)
    : statsID(Utils::getUUID()), match(match), team(team) {}

std::vector<std::string> TeamStats::getArgs() const
{
    return {statsID, match.getID(), team.getID()};
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
    PlayerGoal::deleteGoalsWithStatsID(statsID);
    deleteStored();
}

std::vector<TeamStats> TeamStats::getTeamStatsWithMatch(Match match)
{
    std::vector<TeamStats> stats;

    for (std::vector<std::string> args : getAllStored(FILE_PATH))
    {
        if (args[1] == match.getID())
        {
            stats.push_back(fromArgs(args));
        }
    }

    return stats;
}

TeamStats TeamStats::fromArgs(std::vector<std::string> args)
{
    Match match = Match::idToMatch(args[1]);
    Team team = Team::idToTeam(args[2]);
    std::vector<PlayerGoal> goals = PlayerGoal::getGoalsWithStatsID(args[0]);

    return TeamStats(args[0], match, team, goals);
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
    std::vector<std::string> args = getStored(FILE_PATH, statsID);

    return fromArgs(args);
}

void TeamStats::changeTeam(Team team)
{
    PlayerGoal::deleteGoalsWithStatsID(statsID);
    this->team = team;
    resave();
}

std::vector<PlayerGoal> TeamStats::getGoals() const
{
    return PlayerGoal::getGoalsWithStatsID(statsID);
}

void TeamStats::addGoal(Player player, int time) const
{
    PlayerGoal(statsID, player.getID(), time).save();
}

void TeamStats::removeGoal(std::string playerGoalID) const
{
    PlayerGoal::idToPlayerGoal(playerGoalID).deleteGoal();
}