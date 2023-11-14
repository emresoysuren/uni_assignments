#include "Player.h"
#include "util/Utils.h"
#include "Team.h"
#include "Match.h"
#include "TeamPlayer.h"

const std::string Player::FILE_PATH = "players.data";

std::vector<std::string> Player::getArgs() const
{
    return {playerID, name, surname, licenseID, std::to_string(position), std::to_string(salary), Utils::dateToString(dateOfBirth)};
}

std::string Player::getPath() const
{
    return FILE_PATH;
}

Player::Player(std::string playerID, std::string name, std::string surname, std::string licenseID, PlayingPosition position, int salary, tm dateOfBirth)
    : playerID(playerID), name(name), surname(surname), licenseID(licenseID), position(numToPosition(position)), salary(salary), dateOfBirth(dateOfBirth) {}

Player::~Player() {}

Player Player::createPlayer(std::string name, std::string surname, std::string licenseID, PlayingPosition position, int salary, tm dateOfBirth)
{
    Player player(std::to_string(rand()), name, surname, licenseID, position, salary, dateOfBirth);

    player.save();

    return player;
}

void Player::deletePlayer() const
{
    TeamPlayer::removeTeamOrPlayerWithID(playerID);
    Match::deleteStatsOfTeamWithID(playerID);

    deleteStored();
}

PlayingPosition Player::numToPosition(int position)
{
    static std::map<int, PlayingPosition> positions = {
        {PlayingPosition::keeper, PlayingPosition::keeper},
        {PlayingPosition::defender, PlayingPosition::defender},
        {PlayingPosition::midfielder, PlayingPosition::midfielder},
        {PlayingPosition::forward, PlayingPosition::forward},
    };

    return positions[position];
}

std::vector<Player> Player::getAllPlayers()
{
    std::vector<Player> players;

    for (std::vector<std::string> player : StorableUnit::getAllStored(FILE_PATH))
    {
        players.push_back(Player(player[0], player[1], player[2], player[3], numToPosition(stoi(player[4])), stoi(player[5]), Utils::stringToDate(player[6])));
    }

    return players;
};

Player Player::idToPlayer(std::string playerID)
{
    std::vector<std::string> player = getStored(FILE_PATH, playerID);

    return Player(player[0], player[1], player[2], player[3], numToPosition(stoi(player[4])), stoi(player[5]), Utils::stringToDate(player[6]));
};

// Getters and setters

std::string Player::getID() const
{
    return playerID;
}

std::string Player::getName() const
{
    return name;
}

std::string Player::getSurname() const
{
    return surname;
}

std::tm Player::getDate() const
{
    return dateOfBirth;
}

int Player::getSalary() const
{
    return salary;
}

PlayingPosition Player::getPosition() const
{
    return position;
}

std::string Player::getLicenseID() const
{
    return licenseID;
}

void Player::setDate(std::tm date)
{
    dateOfBirth = date;
    resave();
}

void Player::setName(std::string name)
{
    this->name = name;
    resave();
}

void Player::setSurname(std::string surname)
{
    this->surname = surname;
    resave();
}

void Player::setSalary(int salary)
{
    this->salary = salary;
    resave();
}

void Player::setPosition(PlayingPosition position)
{
    this->position = position;
    resave();
}

void Player::setLicenseID(std::string licenseID)
{
    this->licenseID = licenseID;
    resave();
}
