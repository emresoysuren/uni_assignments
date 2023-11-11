#include <iostream>
#include <functional>
using namespace std;

#include "Player.h"
#include "Team.h"
#include "./util/Menu.h"

// Forward declarations
void startMainMenu();
void startTeamMenu();
void startTeamListMenu();
Team createTeam();
void startAddPlayerMenu(Team);
void startManageTeamMenu(Team);
void startManagePlayerMenu(Player);
void startManagePlayersOfTeam(Team team);
void startPlayersListMenu(function<void(Player)> = startManagePlayerMenu);
void startManageTeamPlayerMenu(Team team, Player player);
void addPlayer(Team, Player);
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

Player createPlayer()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    string name, surname;
    int position, salary;
    tm dateOfBirth;

    cout << "Enter the information of the player:" << endl;

    cout << "Name: ";
    cin >> name;

    cout << "Surname: ";
    cin >> surname;

    cout << "Position: ";
    cin >> position;

    cout << "Salary: ";
    cin >> salary;

    cout << "Date of Birth: ";
    cin >> dateOfBirth.tm_mday >> dateOfBirth.tm_mon >> dateOfBirth.tm_year;

    return Player::createPlayer(name, surname, Player::numToPosition(position), salary, dateOfBirth);
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

    options.push_back({"Back", startTeamMenu});

    Menu(options, "Manage a Team (Found " + to_string(options.size() - 1) + " teams)").start();
}

void startManagePlayersOfTeam(Team team)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    vector<MenuOption> options = {};

    for (Player player : team.getPlayers())
    {
        options.push_back(MenuOption{
            player.getName(),
            [team, player]()
            {
                startManageTeamPlayerMenu(team, player);
            },
        });
    }

    options.push_back({"Back", [team]()
                       {
                           startManageTeamMenu(team);
                       }});

    Menu(options, "Manage Player in " + team.getName() + " (Found " + to_string(options.size() - 1) + " players)").start();
}

void startManageTeamPlayerMenu(Team team, Player player)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Manage Player", [player]()
              {
                  startManagePlayerMenu(player);
              }},
             // @todo: Add remove player from team fuctionality
             {"Remove Player from the Team", []() {}},
             {"Back", [team]()
              {
                  startManagePlayersOfTeam(team);
              }},
         },
         "Managing Team:" + team.getName())
        .start();
}

void startManageTeamMenu(Team team)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Add Player", [team]()
              {
                  startAddPlayerMenu(team);
              }},
             {"Manage Players", [team]()
              {
                  startManagePlayersOfTeam(team);
              }},
             {"Update Team", []() {}},
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
         "Managing Team:" + team.getName())
        .start();
}

void startPlayerMenu()
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Create Player", []()
              {
                  startManagePlayerMenu(createPlayer());
              }},
             {"Manage a Player", []()
              {
                  startPlayersListMenu();
              }},
             {"Back", startMainMenu},
         },
         "Manage Players")
        .start();
}

void startPlayersListMenu(function<void(Player)> callback)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    vector<MenuOption> options = {};

    for (Player player : Player::getAllPlayers())
    {
        options.push_back(MenuOption{
            player.getName(),
            [player, callback]()
            {
                callback(player);
            },
        });
    }

    options.push_back({"Back", startPlayerMenu});

    Menu(options, "Manage a Player (Found " + to_string(options.size() - 1) + " players)").start();
}

void addPlayer(Team team, Player player)
{
    team.addPlayer(player.getID());
}

void startAddPlayerMenu(Team team)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    startPlayersListMenu([team](Player player)
                         {
                             addPlayer(team, player);
                             startManageTeamMenu(team); });
}

void startManagePlayerMenu(Player player)
{
    // Clear the screen
    cout << "\x1b[2J";
    // Move the cursor to the top left
    cout << "\x1b[H";

    Menu({
             {"Update Player", []() {}},
             {"Delete Player", [ID = player.getID()]()
              {
                  Player::deletePlayer(ID);
                  startPlayersListMenu();
              }},
             {"Back", []()
              {
                  startPlayersListMenu();
              }},
         },
         "Managing Player: " + player.getName() + " " + player.getSurname())
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