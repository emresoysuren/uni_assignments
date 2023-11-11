#pragma once

#include <vector>
#include <functional>
using namespace std;

#include "Menu.h"
class Menu;

class MenuContext
{
private:
    vector<function<Menu()>> context;

    void startMenu(Menu menu);

public:
    MenuContext();
    ~MenuContext();

    bool isRoot();

    void push(Menu menu);
    void push(function<Menu()> menu);

    void pop();

    static void run(Menu menu);
};