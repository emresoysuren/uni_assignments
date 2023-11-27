#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <optional>

class MenuContext;

/// @brief A struct that represents a menu option
struct MenuOption
{
    /// @brief The title of the option
    std::string title;

    /// @brief It's what will be executed when the option is chosen.
    /// If it's empty, the option will be disabled.
    /// It takes a MenuContext as a parameter to allow the option to manipulate the menu stack
    std::optional<std::function<void(MenuContext)>> func;
};

/// @brief A class to create and handle menus visually in the terminal
class Menu
{
private:
    /// @brief The title of the menu
    std::string title = "";

    /// @brief The description of the menu
    std::string description;

    /// @brief The options of the menu
    std::vector<MenuOption> options;

    /// @brief Whether to show the "No options to show" message or not
    bool showNoOptions;

    /// @brief Formats the option at the given index (creates selection and number prefixes)
    /// @param i The index of the option to format
    /// @param opt The options to format
    /// @param chosed Whether to format the option as chosed or not
    /// @return The formatted option
    std::string numberedOption(int i, std::vector<MenuOption> *opt, bool chosed = false) const;

    /// @brief Prints the option at the given index as formatted
    /// @param index The index of the option to print
    /// @param opt The options to print
    /// @param highlight Whether to highlight the option or not
    void printLineAt(int index, std::vector<MenuOption> *opt, bool highlight = false) const;

    /// @brief Prints the description of the menu with formatting it if it's not empty
    void printDescription() const;

    /// @brief Resets the console to its default state
    static void resetConsole();

    /// @brief Gets a single key from the user
    static int getKey();

public:
    /// @brief Whether to loop the menu or not
    bool loopOptions = true;

    /// @brief Create a menu with the given options and title
    /// @param options The options of the menu
    /// @param title The title of the menu
    Menu(std::vector<MenuOption>, std::string, std::string = "", bool = true);

    ~Menu();

    /// @brief Starts the menu and passes the given context to its options
    /// @param context The context to pass to the options
    /// @param usePopButton Whether to add the pop button or not
    void start(MenuContext context, bool usePopButton = true) const;
};
