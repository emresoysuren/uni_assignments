#include "Utils.h"

std::tm Utils::stringToDate(std::string str)
{
    std::tm date;

    std::vector<std::string> dateParts = spiltString(str, '-');

    if (dateParts.size() != 3)
    {
        throw std::invalid_argument("Invalid date format");
    }

    date.tm_mday = std::stoi(dateParts[0]);
    date.tm_mon = std::stoi(dateParts[1]);
    date.tm_year = std::stoi(dateParts[2]);

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

std::string Utils::generateRandomKey()
{
    std::string result;

    result = std::to_string(rand());

    return result;
}

std::string Utils::getInput(std::string title)
{
    return getMultipleInputs({title})[0];
}

std::vector<std::string> Utils::getMultipleInputs(std::vector<std::string> titles)
{
    return getMultipleInputs("", titles);
}

std::vector<std::string> Utils::getMultipleInputs(std::string mainTitle, std::vector<std::string> titles)
{
    clearScreen();

    if (mainTitle != "")
    {
        std::cout << mainTitle << std::endl;
    }

    std::vector<std::string> result;

    for (std::string title : titles)
    {
        std::cout << title;

        std::string input;

        std::cin >> input;

        result.push_back(input);
    }

    std::cin.ignore();

    return result;
}

std::string Utils::secondsToString(int seconds)
{
    std::stringstream ss("");

    int minutes = floor(seconds / 60);

    int secondsLeft = seconds % 60;

    ss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << secondsLeft;

    return ss.str();
}

std::tm Utils::getDateInput(std::string title)
{
    try
    {
        return Utils::stringToDate(Utils::getInput(title));
    }
    catch (const std::exception &_)
    {
        return getDateInput(title);
    }
}

bool Utils::isDateBefore(std::tm date1, std::tm date2)
{
    if (date1.tm_year < date2.tm_year)
    {
        return true;
    }
    else if (date1.tm_year > date2.tm_year)
    {
        return false;
    }

    // If the years are equal

    if (date1.tm_mon < date2.tm_mon)
    {
        return true;
    }
    else if (date1.tm_mon > date2.tm_mon)
    {
        return false;
    }

    // If the months are equal

    if (date1.tm_mday < date2.tm_mday)
    {
        return true;
    }
    else if (date1.tm_mday > date2.tm_mday)
    {
        return false;
    }

    // If the days are equal

    return false;
}
