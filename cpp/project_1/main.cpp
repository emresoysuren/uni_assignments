#include <iostream>
#include <functional>
#include <vector>
#include <ctime>
using namespace std;

#include "Player.h"
#include "Team.h"
#include "TeamStats.h"
#include "Match.h"
#include "./util/Menu.h"
#include "./util/MenuContext.h"
#include "./util/Utils.h"
#include "TeamPlayer.h"

// Forward declarations
Menu mainMenu();
Menu teamMenu();
Menu manageTeamMenu(Team);
Menu teamListMenu(
    function<void(MenuContext, Team)> = [](MenuContext context, Team team)
    { context.push([team]()
                   { return manageTeamMenu(team); }); },
    string = "Manage a Team");
Team createTeam();
Player createPlayer();
Menu addPlayerMenu(Team);
Menu managePlayerMenu(Player);
Menu managePlayersOfTeam(Team);
Menu playerMenu();
Menu playersListMenu(
    function<void(MenuContext, Player)> = [](MenuContext context, Player player)
    { context.push([player]()
                   { return managePlayerMenu(player); }); },
    string = "Manage a Player");
Menu manageTeamPlayerMenu(Team, Player);
Menu manageGameRecordsMenu();
Menu manageMatchMenu(Match);
Menu matchListMenu();
Match createMatch();
Menu updatePlayerMenu(Player);
void updatePlayerName(Player);
Menu updateTeamMenu(Team);

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
                        "Manage Game Records",
                        [](MenuContext context)
                        {
                            context.push(manageGameRecordsMenu());
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
                            context.push([]()
                                         { return teamListMenu(); });
                        },
                    },
                },
                "Manage Teams");
}

Menu teamListMenu(function<void(MenuContext, Team)> callback, string title)
{
    vector<MenuOption> options = {};

    for (Team team : Team::getAllTeams())
    {
        options.push_back(MenuOption{
            team.getName(),
            [team, callback](MenuContext context)
            {
                callback(context, team);
            },
        });
    }

    return Menu(options, title + " (Found " + to_string(options.size()) + " teams)");
}

Menu managePlayersOfTeam(Team team)
{
    vector<MenuOption> options = {};

    for (Player player : team.getPlayers())
    {
        options.push_back(MenuOption{
            player.getName() + " " + player.getSurname(),
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
                            context.push([player]()
                                         { return managePlayerMenu(player); });
                        },
                    },
                    {
                        "Remove Player from the Team",
                        [ID = player.getID()](MenuContext context)
                        {
                            TeamPlayer::removeTeamOrPlayerWithID(ID);
                            context.pop();
                        },
                    },
                },
                "Managing " + team.getName() + " (Team)");
}

Menu manageTeamMenu(Team team)
{
    // In order the menu to be updated, we need to access the team object from the file
    team = Team::idToTeam(team.getID());

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
                        [team](MenuContext context)
                        {
                            context.push([team]()
                                         { return updateTeamMenu(team); });
                        },
                    },
                    {
                        "Delete the Team",
                        [team](MenuContext context)
                        {
                            team.deleteTeam();
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
                            context.push([]()
                                         { return managePlayerMenu(createPlayer()); });
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
            player.getName() + " " + player.getSurname(),
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
                            team.addPlayer(player);
                            context.pop(); },
                           "Managing the Players of " + team.getName() + " (Team)");
}

Menu managePlayerMenu(Player player)
{
    // In order the menu to be updated, we need to access the player object from the file
    player = Player::idToPlayer(player.getID());

    return Menu({
                    {
                        "Update Player",
                        [player](MenuContext context)
                        {
                            context.push([player]()
                                         { return updatePlayerMenu(player); });
                        },
                    },
                    {
                        "Delete Player",
                        [player](MenuContext context)
                        {
                            player.deletePlayer();
                            context.pop();
                        },
                    },
                },
                "Managing " + player.getName() + " " + player.getSurname() + " (Player)");
}

Menu manageGameRecordsMenu()
{
    return Menu({
                    {
                        "Create a Game Record",
                        [](MenuContext context)
                        {
                            context.push(manageMatchMenu(createMatch()));
                        },
                    },
                    {
                        "Manage a Game Record",
                        [](MenuContext context)
                        {
                            context.push(matchListMenu);
                        },
                    },
                    {
                        "Show Game Records",
                        [](MenuContext context) {

                        },
                    },
                    {
                        "Show Scores",
                        [](MenuContext context) {},
                    },
                    {
                        "Matches in This Week",
                        [](MenuContext context) {},
                    },
                },
                "Manage Game Records");
}

Menu matchListMenu()
{
    vector<MenuOption> options = {};

    for (Match match : Match::getAllMatches())
    {
        options.push_back(MenuOption{
            Utils::dateToString(match.getDate()) + " " + match.getWinner().getTeam().getName() + " " + match.getLoser().getTeam().getName() + " [" + to_string(match.getWinner().getGoals()) + ":" + to_string(match.getLoser().getGoals()) + "]",
            [match](MenuContext context)
            {
                context.push(manageMatchMenu(match));
            },
        });
    }

    return Menu(options, "Manage a Team (Found " + to_string(options.size()) + " teams)");
}

Menu manageMatchMenu(Match match)
{
    return Menu({
                    {
                        "Update Match",
                        [](MenuContext context) {},
                    },
                    {
                        "Delete Match",
                        [ID = match.getID()](MenuContext context)
                        {
                            Match::deleteMatch(ID);
                            context.pop();
                        },
                    },
                },
                match.getWinner().getTeam().getName() + " " + match.getLoser().getTeam().getName() + " [" + to_string(match.getWinner().getGoals()) + ":" + to_string(match.getLoser().getGoals()) + "]" + " (Match)");
}

// Functional units

// Update functions

Menu updatePlayerMenu(Player player)
{
    // In order the menu to be updated, we need to access the player object from the file
    player = Player::idToPlayer(player.getID());

    return Menu({
                    {
                        "Name: " + player.getName(),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            string name;
                            cout << "Enter the new name: ";
                            cin >> name;
                            player.setName(name);

                            cin.ignore();

                            context.reload();
                        },
                    },
                    {
                        "Surname: " + player.getSurname(),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            string surname;
                            cout << "Enter the new surname: ";
                            cin >> surname;
                            player.setSurname(surname);

                            cin.ignore();

                            context.reload();
                        },
                    },
                    {
                        "License ID: " + player.getLicenseID(),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            string licenseID;
                            cout << "Enter the new license ID: ";
                            cin >> licenseID;
                            player.setLicenseID(licenseID);

                            cin.ignore();

                            context.reload();
                        },
                    },
                    {
                        "Position: " + to_string(player.getPosition()),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            int pos;
                            cout << "Enter the new position: ";
                            cin >> pos;
                            player.setPosition(Player::numToPosition(pos));

                            cin.ignore();

                            context.reload();
                        },
                    },
                    {
                        "Salary: " + to_string(player.getSalary()),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            int salary;
                            cout << "Enter the new salary: ";
                            cin >> salary;
                            player.setSalary(salary);

                            cin.ignore();

                            context.reload();
                        },
                    },
                    {
                        "Date Of Birth: " + Utils::dateToString(player.getDate()),
                        [player](MenuContext context) mutable
                        {
                            Utils::clearScreen();

                            string date;
                            cout << "Enter the new date of birth: ";
                            cin >> date;
                            player.setDate(Utils::stringToDate(date));

                            cin.ignore();

                            context.reload();
                        },
                    },
                },
                "Update " + player.getName() + " " + player.getSurname() + " (Player)");
}

Menu updateTeamMenu(Team team)
{
    // In order the menu to be updated, we need to access the player object from the file
    team = Team::idToTeam(team.getID());

    return Menu({{
                     "Name: " + team.getName(),
                     [team](MenuContext context) mutable
                     {
                         Utils::clearScreen();

                         string name;
                         cout << "Enter the new name: ";
                         cin >> name;
                         team.setName(name);

                         cin.ignore();

                         context.reload();
                     },
                 },
                 {
                     "Address: " + team.getAddr(),
                     [team](MenuContext context) mutable
                     {
                         Utils::clearScreen();

                         string address;
                         cout << "Enter the new address: ";
                         cin >> address;
                         team.setAddr(address);

                         cin.ignore();

                         context.reload();
                     },
                 },
                 {
                     "Phone Number: " + team.getPhone(),
                     [team](MenuContext context) mutable
                     {
                         Utils::clearScreen();

                         string phoneNumber;
                         cout << "Enter the new phone number: ";
                         cin >> phoneNumber;
                         team.setPhone(phoneNumber);

                         cin.ignore();

                         context.reload();
                     },
                 },
                 {
                     "Director: " + team.getDirector(),
                     [team](MenuContext context) mutable
                     {
                         Utils::clearScreen();

                         string director;
                         cout << "Enter the new director: ";
                         cin >> director;
                         team.setDirector(director);

                         cin.ignore();

                         context.reload();
                     },
                 }

                },
                "Update " + team.getName() + " (Team)");
}

// Creation functions

Team createTeam()
{
    Utils::clearScreen();

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

    cin.ignore();

    return Team::createTeam(name, address, phoneNumber, director);
}

Player createPlayer()
{
    Utils::clearScreen();

    string name, surname, licenseID;
    int position, salary;
    tm dateOfBirth;

    cout << "Enter the information of the player:" << endl;

    cout << "Name: ";
    cin >> name;

    cout << "Surname: ";
    cin >> surname;

    cout << "Position: ";
    cin >> position;

    cout << "License ID: ";
    cin >> licenseID;

    cout << "Salary: ";
    cin >> salary;

    cout << "Date of Birth: ";
    cin >> dateOfBirth.tm_mday >> dateOfBirth.tm_mon >> dateOfBirth.tm_year;

    cin.ignore();

    return Player::createPlayer(name, surname, licenseID, Player::numToPosition(position), salary, dateOfBirth);
}

Match createMatch()
{

    TeamStats *stats = (TeamStats *)calloc(2, sizeof(TeamStats));
    Team *t = (Team *)calloc(1, sizeof(Team));

    for (int i = 0; i < 2; i++)
    {
        int goals;

        Utils::clearScreen();

        teamListMenu([t](MenuContext context, Team team)
                     { *t = team; },
                     "Select the #" + to_string(i + 1) + " Team")
            .start();

        Utils::clearScreen();

        cout << "Enter the goals of " << t->getName() << ": ";
        cin >> goals;

        stats[i] = TeamStats(*t, goals);

        // @TODO : Find out why this is needed
        cin.ignore();
    }

    delete t;

    Utils::clearScreen();

    tm date;

    cout << "Enter the date of the match: ";
    cin >> date.tm_mday >> date.tm_mon >> date.tm_year;

    Match match = Match::createMatch(date, stats[0], stats[1]);

    delete stats;

    cin.ignore();

    return match;
}
