#pragma once

#include <ctime>
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
};
