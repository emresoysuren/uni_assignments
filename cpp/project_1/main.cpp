#include "Player.h"
#include "Team.h"
#include "./util/Menu.h"

// Forward declarations
void startMainMenu();
void startTeamMenu();
void startManageTeamMenu();
void startPlayerMenu();
void startInfoMenu();

int main()
{
    // Start the main menu
    startMainMenu();

    return 0;
}

void startMainMenu()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
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
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
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
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
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
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
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
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Show Game Records", []() {}},
             {"Back", startMainMenu},
         },
         "Info")
        .start();
}