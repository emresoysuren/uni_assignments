#include "Match.h"
#include "util/Utils.h"
#include "Team.h"
#include "TeamStats.h"

const std::string Match::FILE_PATH = "matches.data";

Match::Match(std::string ID, std::tm date)
    : matchID(ID), date(date) {}

Match::Match(std::tm date)
    : matchID(Utils::getUUID()), date(date) {}

Match::~Match() {}

TeamStats Match::getWinner() const
{
    std::vector<TeamStats> teams = getStats();

    if (teams[0].getGoals() > teams[1].getGoals())
    {
        return teams[0];
    }

    return teams[1];
}

TeamStats Match::getLoser() const
{
    std::vector<TeamStats> teams = getStats();

    if (teams[0].getGoals() > teams[1].getGoals())
    {
        return teams[1];
    }

    return teams[0];
}

std::string Match::getID() const
{
    return matchID;
}

void Match::create(TeamStats team1, TeamStats team2)
{
    save();
    team1.save();
    team2.save();
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