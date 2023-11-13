#pragma once

#include "Team.h"
class Team;

class TeamStats
{
private:
    Team team;
    int goals;

public:
    TeamStats(Team team, int goals = 0);

    int getGoals() const;

    Team getTeam() const;
};