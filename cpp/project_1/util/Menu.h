#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

// Menu option struct
struct MenuOption
{
    string title;
    function<void()> func;
};

/// @brief A class to create and handle menus visually in the terminal
class Menu
{
private:
    string title = "";
    vector<MenuOption> options;

    /// @brief Formats the option at the given index
    /// @param i The index of the option to format
    /// @param chosed Whether to format the option as chosed or not
    /// @return The formatted option
    string numberedOption(int i, bool chosed = false);

    /// @brief Prints the given text in green and bold
    /// @param text The text to print
    void printHighlighted(string text);

    /// @brief Prints the option at the given index
    /// @param selected The index of the option to print
    /// @param highlight Whether to highlight the option or not
    void printLineAt(int selected, bool highlight = false);

public:
    bool loopOptions = true;

    /// @brief Create a menu with the given options and title
    /// @param options The options of the menu
    /// @param title The title of the menu
    Menu(vector<MenuOption> options, string title);

    ~Menu();

    /// @brief Start the menu with the given options
    void start();
};
