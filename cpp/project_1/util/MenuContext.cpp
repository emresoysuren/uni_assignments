#include "MenuContext.h"
#include "Menu.h"
#include "Utils.h"

MenuContext::MenuContext() {}
MenuContext::~MenuContext() {}

void MenuContext::startMenu(Menu menu, bool usePopButton) const
{
    Utils::clearScreen();

    menu.start(*this, usePopButton);
}

void MenuContext::push(Menu menu, bool usePopButton, bool replace)
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

    startMenu(menu, usePopButton);
}

void MenuContext::push(std::function<Menu()> menu, bool usePopButton, bool replace)
{
    if (replace)
    {
        context.back() = menu;
    }
    else
    {
        context.push_back(menu);
    }

    startMenu(menu(), usePopButton);
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

void MenuContext::run(Menu menu, bool usePopButton)
{
    MenuContext context;
    context.push(menu, usePopButton);
}
