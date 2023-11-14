#include "Player.h"
#include "util/Utils.h"
#include "Team.h"
#include "Match.h"

const std::string Player::FILE_PATH = "players.data";

void Player::save() const
{
    std::ofstream file(FILE_PATH, std::ios::app);

    file << playerID << " " << name << " " << surname << " " << licenseID << " " << position << " " << salary << " ";
    file << Utils::dateToString(dateOfBirth) << std::endl;

    file.close();
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

void Player::deletePlayer(std::string playerID)
{
    Team::removeTeamOrPlayerWithID(playerID);
    Match::deleteStatsOfTeamWithID(playerID);

    std::ifstream rfile(FILE_PATH);
    std::ofstream temp("temp.data", std::ios::app);

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != playerID)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(FILE_PATH.c_str());
    rename("temp.data", FILE_PATH.c_str());
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
    std::string line;

    std::ifstream file(FILE_PATH);

    while (getline(file, line))
    {
        players.push_back(fromString(line));
    }

    file.close();

    return players;
};

Player Player::fromString(std::string line)
{
    std::string word;
    std::stringstream ss(line);
    std::vector<std::string> result;

    while (getline(ss, word, ' '))
    {
        result.push_back(word);
    }

    return Player(result[0], result[1], result[2], result[3], numToPosition(stoi(result[4])), stoi(result[5]), Utils::stringToDate(result[6]));
}

Player Player::idToPlayer(std::string playerID)
{
    std::string line;

    std::ifstream file(FILE_PATH, std::ios::app);

    while (getline(file, line))
    {
        if (line.substr(0, line.find(" ")) == playerID)
        {
            return fromString(line);
        }
    }

    file.close();

    throw "Player not found";
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
}

void Player::setName(std::string name)
{
    this->name = name;
}

void Player::setSurname(std::string surname)
{
    this->surname = surname;
}

void Player::setSalary(int salary)
{
    this->salary = salary;
}

void Player::setPosition(PlayingPosition position)
{
    this->position = position;
}

void Player::setLicenseID(std::string licenseID)
{
    this->licenseID = licenseID;
}
