#pragma once

#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Utils
{
public:
    static std::tm stringToDate(std::string str);
    static std::string dateToString(std::tm date);
    static std::vector<std::string> spiltString(std::string str, char delimiter);
    static void clearScreen();

    static std::string getInput(std::string title);

    static std::vector<std::string> getMultipleInputs(std::vector<std::string> titles);
    static std::vector<std::string> getMultipleInputs(std::string mainTitle, std::vector<std::string> titles);

    static std::string getUUID();

    static std::string secondsToString(int seconds);
};
