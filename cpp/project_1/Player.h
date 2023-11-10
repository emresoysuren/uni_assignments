#pragma once

#include <string>
#include <ctime>
#include <map>
using namespace std;

#include "Team.h"

/// @brief Enum to represent the position of a player playing in a team
enum PlayingPosition
{
    keeper,
    defender,
    midfielder,
    forward,
};

/// @brief A class to represent a player
class Player
{
private:
    string playerID;
    string name;
    string surname;
    int licenseID;
    PlayingPosition position;
    int salary;
    tm dateOfBirth;

    static const string FILE_PATH;

    static void savePlayer(Player player)
    {
        ofstream file(FILE_PATH, ios::app);

        file << player.playerID << " " << player.name << " " << player.surname << " " << player.licenseID << " " << player.position << " " << player.salary << " ";
        file << to_string(player.dateOfBirth.tm_mday) + "-" + to_string(player.dateOfBirth.tm_mon) + "-" + to_string(player.dateOfBirth.tm_year) << endl;

        file.close();
    }

public:
    /// @brief Creates a new Player object
    /// @param playerID ID of the player
    /// @param name Name of the player
    /// @param surname Surame of the player
    /// @param teamID The id of the team the player is in
    /// @param position The position of the player playing in the team
    /// @param salary Salary of the player
    /// @param dateOfBirth Date of birth of the player
    Player(string playerID, string name, string surname, int licenseID, PlayingPosition position, int salary, tm dateOfBirth)
        : playerID(playerID), name(name), surname(surname), licenseID(licenseID), position(numToPosition(position)), salary(salary), dateOfBirth(dateOfBirth) {}
    ~Player() {}

    static Player createPlayer(string name, string surname, PlayingPosition position, int salary, tm dateOfBirth)
    {
        Player player(to_string(rand()), name, surname, rand(), position, salary, dateOfBirth);

        savePlayer(player);

        return player;
    }

    static void deletePlayer(string playerID)
    {
        ifstream file(FILE_PATH);
        ofstream temp("temp.data");

        string line;

        while (getline(file, line))
        {
            if (line.substr(0, line.find(" ")) != playerID)
            {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove(FILE_PATH.c_str());
        rename("temp.data", FILE_PATH.c_str());
    }

    /// @brief Converts a number to a PlayingPosition
    /// @param position Position of the player as a number
    /// @return Returns the PlayingPosition corresponding to the given number
    static PlayingPosition numToPosition(int position)
    {
        static map<int, PlayingPosition> positions = {
            {PlayingPosition::keeper, PlayingPosition::keeper},
            {PlayingPosition::defender, PlayingPosition::defender},
            {PlayingPosition::midfielder, PlayingPosition::midfielder},
            {PlayingPosition::forward, PlayingPosition::forward},
        };

        return positions[position];
    }

    static vector<Player> getAllPlayers()
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

    static Player fromString(string line)
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

    string getID()
    {
        return playerID;
    }

    string getName()
    {
        return name;
    }

    string getSurname()
    {
        return surname;
    }
};

const string Player::FILE_PATH = "players.data";