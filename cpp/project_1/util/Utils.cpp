#include "Utils.h"

std::tm Utils::stringToDate(std::string str)
{
    std::tm date;

    std::string word;

    std::stringstream ss(str);

    getline(ss, word, '-');
    date.tm_mday = std::stoi(word);

    getline(ss, word, '-');
    date.tm_mon = std::stoi(word);

    getline(ss, word, '-');
    date.tm_year = std::stoi(word);

    return date;
}

std::string Utils::dateToString(std::tm date)
{
    return std::to_string(date.tm_mday) + "-" + std::to_string(date.tm_mon) + "-" + std::to_string(date.tm_year);
}

std::vector<std::string> Utils::spiltString(std::string str, char delimiter)
{
    std::vector<std::string> result;

    std::string word;

    std::stringstream ss = std::stringstream(str);

    while (getline(ss, word, delimiter))
    {
        result.push_back(word);
    }

    return result;
}

void Utils::clearScreen()
{
    // Clear the screen
    std::cout << "\x1b[2J";
    // Move the cursor to the top left
    std::cout << "\x1b[H";
}