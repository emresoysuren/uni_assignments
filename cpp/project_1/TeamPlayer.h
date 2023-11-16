#pragma once

#include <optional>
#include <string>
#include <vector>

#include "util/StorableUnit.h"
#include "Team.h"
#include "Player.h"

class TeamPlayer : public StorableUnit
{
private:
    Team team;
    Player player;

    static const std::string FILE_PATH;

    virtual std::vector<std::string> getArgs() const;
    virtual std::string getPath() const;

public:
    TeamPlayer(Team team, Player player);
    ~TeamPlayer();

    void save() const;

    static std::vector<Player> getPlayersOfTeam(Team team);

    static std::optional<Team> getTeamOfPlayer(Player player);

    static void removeTeamOrPlayerWithID(std::string ID);
};