#include <iostream>
using namespace std;

#include "Player.h"
#include "Team.h"
#include "./util/Menu.h"

// Forward declarations
void startMainMenu();
void startTeamMenu();
void startTeamListMenu();
Team createTeam();
void startManageTeamMenu(Team);
void startPlayerMenu();
void startInfoMenu();

int main()
{
    //  Seed the random number generator
    srand((unsigned int)time(NULL));

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
             MenuOption{
                 "Exit",
                 []()
                 {
                     exit(0);
                 },
             },
         },
         "Main Menu")
        .start();
}

Team createTeam()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    string name, address, phoneNumber, director;

    cout << "Enter the information of the team:" << endl;

    cout << "Name: ";
    cin >> name;

    cout << "Address: ";
    cin >> address;

    cout << "Phone Number: ";
    cin >> phoneNumber;

    cout << "Director: ";
    cin >> director;

    return Team::createTeam(name, address, phoneNumber, director);
}

void startTeamMenu()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Create a New Team", []()
              {
                  startManageTeamMenu(createTeam());
              }},
             {"Manage a Team", startTeamListMenu},
             {"Back", startMainMenu},
         },
         "Manage Teams")
        .start();
}

void startTeamListMenu()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    vector<MenuOption> options = {};

    for (Team team : Team::getAllTeams())
    {
        options.push_back(MenuOption{
            team.getName(),
            [team]()
            {
                startManageTeamMenu(team);
            },
        });
    }

    // @todo: Fix here it doesn't show any team and wired count of teams
    options.push_back({"Back", startTeamMenu});

    Menu(options, "Manage a Team (Found " + to_string(options.size() - 1) + " teams)").start();
}

void startManageTeamMenu(Team team)
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
             {
                 "Delete the Team",
                 [ID = team.getID()]()
                 {
                     Team::deleteTeam(ID);
                     startTeamListMenu();
                 },
             },
             {"Back", startTeamListMenu},
         },
         "Managing " + team.getName() + " Team")
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