#include "TeamStats.h"
#include "Team.h"

TeamStats::TeamStats(Team team, int goals)
    : team(team), goals(goals) {}

int TeamStats::getGoals() const
{
    return goals;
}

Team TeamStats::getTeam() const
{
    return team;
}