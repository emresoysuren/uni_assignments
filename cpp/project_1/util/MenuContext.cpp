#include "MenuContext.h"
#include "Menu.h"
#include "Utils.h"

MenuContext::MenuContext() {}
MenuContext::~MenuContext() {}

void MenuContext::startMenu(Menu menu, bool useContext) const
{
    Utils::clearScreen();

    menu.start(*this, useContext);
}

void MenuContext::push(Menu menu, bool useContext, bool replace)
{
    if (replace)
    {
        context.back() = [menu]()
        { return menu; };
    }
    else
    {
        context.push_back([menu]()
                          { return menu; });
    }

    startMenu(menu, useContext);
}

void MenuContext::push(std::function<Menu()> menu, bool useContext, bool replace)
{
    if (replace)
    {
        context.back() = menu;
    }
    else
    {
        context.push_back(menu);
    }

    startMenu(menu(), useContext);
}

bool MenuContext::isRoot() const
{
    return context.size() == 1;
}

void MenuContext::pop()
{
    if (isRoot())
    {
        return;
    }

    context.pop_back();
    startMenu(context.back()());
}

void MenuContext::reload() const
{
    startMenu(context.back()());
}

void MenuContext::run(Menu menu, bool useContext)
{
    MenuContext context;
    context.push(menu, useContext);
}
