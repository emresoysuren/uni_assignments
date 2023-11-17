#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <optional>

class MenuContext;

struct MenuOption
{
    std::string title;
    std::optional<std::function<void(MenuContext)>> func;
};

/// @brief A class to create and handle menus visually in the terminal
class Menu
{
private:
    std::string title = "";
    std::string description;
    std::vector<MenuOption> options;
    bool showNoOptions;

    /// @brief Formats the option at the given index
    /// @param i The index of the option to format
    /// @param chosed Whether to format the option as chosed or not
    /// @return The formatted option
    std::string numberedOption(int i, std::vector<MenuOption> *opt, bool chosed = false) const;

    /// @brief Prints the option at the given index
    /// @param index The index of the option to print
    /// @param highlight Whether to highlight the option or not
    void printLineAt(int index, std::vector<MenuOption> *opt, bool highlight = false) const;

    void printDescription() const;

    static void resetConsole();

    static int getKey();

public:
    bool loopOptions = true;

    /// @brief Create a menu with the given options and title
    /// @param options The options of the menu
    /// @param title The title of the menu
    Menu(std::vector<MenuOption>, std::string, std::string = "", bool = true);

    ~Menu();

    void start(MenuContext context, bool useContext = true) const;
};
