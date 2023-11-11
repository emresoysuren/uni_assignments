#pragma once

#include <vector>
using namespace std;

#include "Menu.h"
class Menu;

class MenuContext
{
private:
    vector<Menu> context;

    void startMenu(Menu menu);

public:
    MenuContext();
    ~MenuContext();

    bool isRoot();

    void push(Menu menu);

    void pop();

    static void run(Menu menu);
};