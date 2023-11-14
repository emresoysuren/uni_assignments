#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

class MenuContext;

struct MenuOption
{
    std::string title;
    std::function<void(MenuContext)> func;
};

/// @brief A class to create and handle menus visually in the terminal
class Menu
{
private:
    std::string title = "";
    std::vector<MenuOption> options;

    /// @brief Formats the option at the given index
    /// @param i The index of the option to format
    /// @param chosed Whether to format the option as chosed or not
    /// @return The formatted option
    std::string numberedOption(int i, std::vector<MenuOption> *opt, bool chosed = false) const;

    /// @brief Prints the given text in green and bold
    /// @param text The text to print
    void printHighlighted(std::string text) const;

    /// @brief Prints the option at the given index
    /// @param selected The index of the option to print
    /// @param highlight Whether to highlight the option or not
    void printLineAt(int selected, std::vector<MenuOption> *opt, bool highlight = false) const;

    static int getKey();

    static const int UP_ARROW;
    static const int DOWN_ARROW;
    static const int ENTER_KEY;

    void start(MenuContext context, bool useContext) const;

public:
    bool loopOptions = true;

    /// @brief Create a menu with the given options and title
    /// @param options The options of the menu
    /// @param title The title of the menu
    Menu(std::vector<MenuOption> options, std::string title);

    ~Menu();

    /// @brief Start the menu with the given options
    void start(MenuContext context) const;

    void start() const;
};
