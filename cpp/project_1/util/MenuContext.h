#pragma once

#include <vector>
#include <functional>

class Menu;

class MenuContext
{
private:
    std::vector<std::function<Menu()>> context;

    void startMenu(Menu menu, bool useContext = true) const;

public:
    MenuContext();
    ~MenuContext();

    bool isRoot() const;

    void push(Menu menu, bool useContext = true);
    void push(std::function<Menu()> menu, bool useContext = true);

    void pop();

    void reload() const;

    static void run(Menu menu, bool useContext = true);
};