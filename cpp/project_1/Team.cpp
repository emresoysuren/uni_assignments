#include "Team.h"
#include "Match.h"
#include "Player.h"
#include "TeamPlayer.h"

const std::string Team::FILE_PATH = "teams.data";

Team::Team(std::string teamID, std::string name, std::string address, std::string phoneNumber, std::string director)
    : teamID(teamID), name(name), address(address), phoneNumber(phoneNumber), director(director)
{
}

Team::~Team() {}

Team Team::idToTeam(std::string teamID)
{
    std::vector<std::string> team = getStored(FILE_PATH, teamID);

    return Team(team[0], team[1], team[2], team[3], team[4]);
};

void Team::deleteTeam() const
{
    TeamPlayer::removeTeamOrPlayerWithID(teamID);
    Match::deleteStatsOfTeamWithID(teamID);
    deleteStored();
}

std::vector<Team> Team::getAllTeams()
{
    std::vector<Team> result;

    for (std::vector<std::string> team : getAllStored(FILE_PATH))
    {
        result.push_back(Team(team[0], team[1], team[2], team[3], team[4]));
    }

    return result;
};

Team Team::createTeam(std::string name, std::string address, std::string phoneNumber, std::string director)
{
    Team team(std::to_string(rand()), name, address, phoneNumber, director);

    team.save();

    return team;
}

void Team::addPlayer(Player player) const
{
    TeamPlayer(*this, player).save();
}

std::vector<Player> Team::getPlayers() const
{
    return TeamPlayer::getPlayersOfTeam(*this);
}

std::vector<std::string> Team::getArgs() const
{
    return {teamID, name, address, phoneNumber, director};
}

std::string Team::getPath() const
{
    return FILE_PATH;
}

std::string Team::getName() const
{
    return name;
}

std::string Team::getID() const
{
    return teamID;
}

std::string Team::getAddr() const
{
    return address;
}

std::string Team::getPhone() const
{
    return phoneNumber;
}

std::string Team::getDirector() const
{
    return director;
}

void Team::setName(std::string newValue)
{
    name = newValue;
    resave();
}

void Team::setAddr(std::string newValue)
{
    address = newValue;
    resave();
}

void Team::setPhone(std::string newValue)
{
    phoneNumber = newValue;
    resave();
}

void Team::setDirector(std::string newValue)
{
    director = newValue;
    resave();
}