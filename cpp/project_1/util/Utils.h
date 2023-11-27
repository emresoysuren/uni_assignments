#pragma once

#include <ctime>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

/// @brief A class that provides some utility functions for the project
class Utils
{
public:
    /// @brief Converts a string to a date from the format of dd-mm-yyyy
    static std::tm stringToDate(std::string str);

    /// @brief Converts a date to a string in the format of dd-mm-yyyy
    static std::string dateToString(std::tm date);

    /// @brief Splits a string into a vector of strings using the given delimiter
    static std::vector<std::string> spiltString(std::string str, char delimiter);

    /// @brief Clears the screen
    static void clearScreen();

    /// @brief Gets an input from the user (clears the screen before getting input)
    /// @param title The title of the input to be shown to the user to get input
    static std::string getInput(std::string title);

    /// @brief Gets multiple inputs from the user (clears the screen before getting input)
    /// @param titles The titles of the inputs to be shown to the user to get input
    /// @return Returns a vector of strings containing the inputs (same order and size as the titles vector)
    static std::vector<std::string> getMultipleInputs(std::vector<std::string> titles);

    /// @brief Gets multiple inputs from the user (clears the screen before getting input)
    /// @param mainTitle The title of the input to be shown to the user
    /// (This title will be shown before all the other titles and won't be used to get input)
    /// @param titles The titles of the inputs to be shown to the user to get input
    /// @return Returns a vector of strings containing the inputs (same order and size as the titles vector)
    static std::vector<std::string> getMultipleInputs(std::string mainTitle, std::vector<std::string> titles);

    /// @brief Generates a random key
    static std::string generateRandomKey();

    /// @brief Converts a time in seconds to a string in the format of mm:ss
    static std::string secondsToString(int seconds);
};
