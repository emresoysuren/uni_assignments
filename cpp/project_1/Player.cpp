#include "Player.h"

const string Player::FILE_PATH = "players.data";

void Player::savePlayer(Player player)
{
    ofstream file(FILE_PATH, ios::app);

    file << player.playerID << " " << player.name << " " << player.surname << " " << player.licenseID << " " << player.position << " " << player.salary << " ";
    file << to_string(player.dateOfBirth.tm_mday) + "-" + to_string(player.dateOfBirth.tm_mon) + "-" + to_string(player.dateOfBirth.tm_year) << endl;

    file.close();
}

Player::Player(string playerID, string name, string surname, int licenseID, PlayingPosition position, int salary, tm dateOfBirth)
    : playerID(playerID), name(name), surname(surname), licenseID(licenseID), position(numToPosition(position)), salary(salary), dateOfBirth(dateOfBirth) {}

Player::~Player() {}

Player Player::createPlayer(string name, string surname, PlayingPosition position, int salary, tm dateOfBirth)
{
    Player player(to_string(rand()), name, surname, rand(), position, salary, dateOfBirth);

    savePlayer(player);

    return player;
}

void Player::deletePlayer(string playerID)
{
    Team::removeTeamOrPlayerWithID(playerID);

    ifstream rfile(FILE_PATH);
    ofstream temp("temp.data", ios::app);

    string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(" ")) != playerID)
        {
            temp << line << endl;
        }
    }

    rfile.close();
    temp.close();

    remove(FILE_PATH.c_str());
    rename("temp.data", FILE_PATH.c_str());
}

PlayingPosition Player::numToPosition(int position)
{
    static map<int, PlayingPosition> positions = {
        {PlayingPosition::keeper, PlayingPosition::keeper},
        {PlayingPosition::defender, PlayingPosition::defender},
        {PlayingPosition::midfielder, PlayingPosition::midfielder},
        {PlayingPosition::forward, PlayingPosition::forward},
    };

    return positions[position];
}

vector<Player> Player::getAllPlayers()
{
    vector<Player> players;
    string line;

    ifstream file(FILE_PATH);

    while (getline(file, line))
    {
        players.push_back(fromString(line));
    }

    file.close();

    return players;
};

Player Player::fromString(string line)
{
    string word;
    stringstream ss(line);
    vector<string> result;

    while (getline(ss, word, ' '))
    {
        result.push_back(word);
    }

    tm dateOfBirth;

    ss = stringstream(result[6]);

    getline(ss, word, '-');
    dateOfBirth.tm_mday = stoi(word);

    getline(ss, word, '-');
    dateOfBirth.tm_mon = stoi(word);

    getline(ss, word, '-');
    dateOfBirth.tm_year = stoi(word);

    return Player(result[0], result[1], result[2], stoi(result[3]), numToPosition(stoi(result[4])), stoi(result[5]), dateOfBirth);
}

Player Player::idToPlayer(string playerID)
{
    string line;

    ifstream file(FILE_PATH, ios::app);

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

string Player::getID() const
{
    return playerID;
}

string Player::getName() const
{
    return name;
}

string Player::getSurname() const
{
    return surname;
}
