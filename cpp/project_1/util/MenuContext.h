#pragma once

#include <vector>
#include <functional>

class Menu;

/// @brief A class that provides an easy interface for navigating through menus
class MenuContext
{
private:
    /// @brief The stack of menus. The Menus are stored as functions so that they can update their state
    std::vector<std::function<Menu()>> context;

    /// @brief Starts the given menu
    /// @param menu The menu to start
    /// @param usePopButton If true, the menu will be started with a pop button
    void startMenu(Menu menu, bool usePopButton = true) const;

public:
    MenuContext();
    ~MenuContext();

    /// @brief Checks if the current menu is the root menu
    bool isRoot() const;

    /// @brief Pushes the given menu to the stack and starts it
    /// @param menu The menu to push. It will be converted to a function that returns the menu
    /// @param usePopButton If true, the menu will be started with a pop button
    /// @param replace If true, the current menu will be replaced with the given menu
    void push(Menu menu, bool usePopButton = true, bool replace = false);

    /// @brief Pushes the given menu to the stack and starts it
    /// @param menu The menu as a function that returns the menu to push to the stack
    /// @param usePopButton If true, the menu will be started with a pop button
    /// @param replace If true, the current menu will be replaced with the given menu
    void push(std::function<Menu()> menu, bool usePopButton = true, bool replace = false);

    /// @brief Pops the current menu from the stack and starts the previous menu
    void pop();

    /// @brief Reloads the current (last) menu in the stack
    void reload() const;

    /// @brief Runs the given menu with binding it with a new MenuContext
    /// @param menu The menu to run
    /// @param usePopButton If true, the menu will be started with a pop button
    static void run(Menu menu, bool usePopButton = true);
};