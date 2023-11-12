#pragma once

#include <vector>
#include <functional>

#include "Menu.h"
class Menu;

class MenuContext
{
private:
    std::vector<std::function<Menu()>> context;

    void startMenu(Menu menu);

public:
    MenuContext();
    ~MenuContext();

    bool isRoot() const;

    void push(Menu menu);
    void push(std::function<Menu()> menu);

    void pop();

    static void run(Menu menu);
};