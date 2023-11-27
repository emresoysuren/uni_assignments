#include "Match.h"
#include "util/Utils.h"
#include "Team.h"
#include "TeamStats.h"
#include "PlayerGoal.h"

const std::string Match::FILE_PATH = "matches.data";

Match::Match(std::string ID, std::tm date)
    : matchID(ID), date(date) {}

Match::Match(std::tm date)
    : matchID(generateUniquePrimaryKey(FILE_PATH)), date(date) {}

Match::~Match() {}

TeamStats Match::getWinner() const
{
    std::vector<TeamStats> teams = getStats();

    if (teams[0].getGoals().size() > teams[1].getGoals().size())
    {
        return teams[0];
    }

    return teams[1];
}

TeamStats Match::getLoser() const
{
    std::vector<TeamStats> teams = getStats();

    if (teams[0].getGoals().size() > teams[1].getGoals().size())
    {
        return teams[1];
    }

    return teams[0];
}

bool Match::isDraw() const
{
    std::vector<TeamStats> teams = getStats();

    return teams[0].getGoals().size() == teams[1].getGoals().size();
}

std::string Match::getID() const
{
    return matchID;
}

void Match::create(std::vector<Team> teams)
{
    save();
    TeamStats(*this, teams[0]).save();
    TeamStats(*this, teams[1]).save();
}

void Match::deleteMatch() const
{
    for (TeamStats stats : getStats())
    {
        stats.deleteStats();
    }

    deleteStored();
}

Match Match::idToMatch(std::string matchID)
{
    std::vector<std::string> match = getStored(FILE_PATH, matchID);

    return Match(match[0], Utils::stringToDate(match[1]));
};

std::vector<TeamStats> Match::getStats() const
{
    return TeamStats::getTeamStatsWithMatch(*this);
}

std::vector<Match> Match::getAllMatches()
{
    std::vector<Match> result;

    for (std::vector<std::string> match : getAllStored(FILE_PATH))
    {
        result.push_back(Match(match[0], Utils::stringToDate(match[1])));
    }

    return result;
}

std::string Match::getPath() const
{
    return FILE_PATH;
}

std::vector<std::string> Match::getArgs() const
{
    return {matchID, Utils::dateToString(date)};
}

std::tm Match::getDate() const
{
    return date;
}

void Match::setDate(std::tm newValue)
{
    date = newValue;
    resave();
}

bool Match::operator<(const Match &other) const
{
    return matchID < other.matchID;
}
