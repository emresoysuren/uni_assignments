#include "Player.h"
#include "Team.h"
#include "./util/Menu.h"

void startMainMenu();
void startTeamMenu();
void startManageTeamMenu();
void startPlayerMenu();
void startInfoMenu();

int main()
{

    startMainMenu();

    return 0;
}

void startMainMenu()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             MenuOption{
                 "Manage Teams",
                 startTeamMenu,
             },
             MenuOption{
                 "Manage Players",
                 startPlayerMenu,

             },
             MenuOption{
                 "Show Info",
                 startInfoMenu,
             },
         },
         "Main Menu")
        .start();
}

void startTeamMenu()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             {"Create a New Team", []() {}},
             {"Manage a Team", startManageTeamMenu},
             {"Back", startMainMenu},
         },
         "Manage Teams")
        .start();
}

void startManageTeamMenu()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             {"Add Player", []() {}},
             {"Delete Player", []() {}},
             {"Update Player", []() {}},
             {"List Players", []() {}},
             {"Delete a Player", []() {}},
             {"Back", startTeamMenu},
         },
         "Manage Team")
        .start();
}

void startPlayerMenu()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             {"Create Player", []() {}},
             {"Delete Player", []() {}},
             {"Update Player", []() {}},
             {"List Players", []() {}},
             {"Back", startMainMenu},
         },
         "Manage Players")
        .start();
}

void startInfoMenu()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             {"Show Game Records", []() {}},
             {"Back", startMainMenu},
         },
         "Info")
        .start();
}