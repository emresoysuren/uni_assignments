#pragma once

#include <vector>
#include <functional>

class Menu;

class MenuContext
{
private:
    std::vector<std::function<Menu()>> context;

    void startMenu(Menu menu) const;

public:
    MenuContext();
    ~MenuContext();

    bool isRoot() const;

    void push(Menu menu);
    void push(std::function<Menu()> menu);

    void pop();

    void reload() const;

    static void run(Menu menu);
};