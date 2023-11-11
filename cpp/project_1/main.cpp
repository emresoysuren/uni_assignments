#include <iostream>
#include <functional>
#include <vector>
using namespace std;

#include "Player.h"
#include "Team.h"
#include "./util/Menu.h"
#include "./util/MenuContext.h"

// Forward declarations
Menu mainMenu();
Menu teamMenu();
Menu teamListMenu();
Team createTeam();
Player createPlayer();
Menu addPlayerMenu(Team);
Menu manageTeamMenu(Team);
Menu managePlayerMenu(Player);
Menu managePlayersOfTeam(Team team);
Menu playerMenu();
Menu playersListMenu(
    function<void(MenuContext, Player)> = [](MenuContext context, Player player)
    { context.push(managePlayerMenu(player)); },
    string = "Manage a Player");
Menu manageTeamPlayerMenu(Team team, Player player);
void addPlayer(Team, Player);
Menu infoMenu();

int main()
{
    //  Seed the random number generator
    srand((unsigned int)time(NULL));

    // Start the main menu
    MenuContext::run(mainMenu());

    return 0;
}

Menu mainMenu()
{
    return Menu({
                    MenuOption{
                        "Manage Teams",
                        [](MenuContext context)
                        {
                            context.push(teamMenu());
                        },
                    },
                    MenuOption{
                        "Manage Players",
                        [](MenuContext context)
                        {
                            context.push(playerMenu());
                        },

                    },
                    MenuOption{
                        "Show Info",
                        [](MenuContext context)
                        {
                            context.push(infoMenu());
                        },
                    },
                },
                "Main Menu");
}

Menu teamMenu()
{
    return Menu({
                    {
                        "Create a New Team",
                        [](MenuContext context)
                        {
                            context.push(manageTeamMenu(createTeam()));
                        },
                    },
                    {
                        "Manage a Team",
                        [](MenuContext context)
                        {
                            context.push(teamListMenu);
                        },
                    },
                },
                "Manage Teams");
}

Menu teamListMenu()
{
    vector<MenuOption> options = {};

    for (Team team : Team::getAllTeams())
    {
        options.push_back(MenuOption{
            team.getName(),
            [team](MenuContext context)
            {
                context.push(manageTeamMenu(team));
            },
        });
    }

    return Menu(options, "Manage a Team (Found " + to_string(options.size()) + " teams)");
}

Menu managePlayersOfTeam(Team team)
{
    vector<MenuOption> options = {};

    for (Player player : team.getPlayers())
    {
        options.push_back(MenuOption{
            player.getName(),
            [team, player](MenuContext context)
            {
                context.push(manageTeamPlayerMenu(team, player));
            },
        });
    }

    return Menu(options, "Manage the Players of " + team.getName() + " (Team) (Found " + to_string(options.size()) + " players)");
}

Menu manageTeamPlayerMenu(Team team, Player player)
{

    return Menu({
                    {
                        "Manage Player",
                        [player](MenuContext context)
                        {
                            context.push(managePlayerMenu(player));
                        },
                    },
                    {
                        "Remove Player from the Team",
                        [team, ID = player.getID()](MenuContext context)
                        {
                            Team::removeTeamOrPlayerWithID(ID);
                            context.pop();
                        },
                    },
                },
                "Managing " + team.getName() + " (Team)");
}

Menu manageTeamMenu(Team team)
{
    return Menu({
                    {
                        "Add Player",
                        [team](MenuContext context)
                        {
                            context.push([team]()
                                         { return addPlayerMenu(team); });
                        },
                    },
                    {
                        "Manage Players",
                        [team](MenuContext context)
                        {
                            context.push([team]()
                                         { return managePlayersOfTeam(team); });
                        },
                    },
                    {
                        "Update Team",
                        [](MenuContext context) {},
                    },
                    {
                        "Delete the Team",
                        [ID = team.getID()](MenuContext context)
                        {
                            Team::deleteTeam(ID);
                            context.pop();
                        },
                    },
                },
                "Managing " + team.getName() + " (Team)");
}

Menu playerMenu()
{

    return Menu({
                    {
                        "Create Player",
                        [](MenuContext context)
                        {
                            context.push(managePlayerMenu(createPlayer()));
                        },
                    },
                    {
                        "Manage a Player",
                        [](MenuContext context)
                        {
                            context.push([]()
                                         { return playersListMenu(); });
                        },
                    },
                },
                "Manage Players");
}

Menu playersListMenu(function<void(MenuContext, Player)> callback, string title)
{

    vector<MenuOption> options = {};

    for (Player player : Player::getAllPlayers())
    {
        options.push_back(MenuOption{
            player.getName(),
            [player, callback](MenuContext context)
            {
                callback(context, player);
            },
        });
    }

    return Menu(options, title + " (Found " + to_string(options.size()) + " players)");
}

Menu addPlayerMenu(Team team)
{
    return playersListMenu([team](MenuContext context, Player player)
                           {
                             addPlayer(team, player);
                             context.pop(); },
                           "Managing the Players of " + team.getName() + " (Team)");
}

Menu managePlayerMenu(Player player)
{
    return Menu({
                    {
                        "Update Player",
                        [](MenuContext context) {},
                    },
                    {
                        "Delete Player",
                        [ID = player.getID()](MenuContext context)
                        {
                            Player::deletePlayer(ID);
                            context.pop();
                        },
                    },
                },
                "Managing " + player.getName() + " " + player.getSurname() + " (Player)");
}

Menu infoMenu()
{
    return Menu({
                    {
                        "Show Game Records",
                        [](MenuContext context) {},
                    },
                },
                "Info");
}

// Functional units

void addPlayer(Team team, Player player)
{
    team.addPlayer(player.getID());
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