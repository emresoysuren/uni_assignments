#include "Menu.h"

string Menu::numberedOption(int i, vector<MenuOption> *opt, bool chosed) const
{
    string optionPrefix;

    if (chosed)
    {
        optionPrefix += "> ";
    }
    else
    {
        optionPrefix += "  ";
    }

    return optionPrefix + "[" + to_string(i) + "] " + (*opt)[i].title;
}

void Menu::printHighlighted(string text) const
{
    // Green color
    cout << "\x1b[32m";

    cout << text;

    // Reset color
    cout << "\x1b[34m";
}

void Menu::printLineAt(int selected, vector<MenuOption> *opt, bool highlight) const
{
    cout << "\r\x1b[K";

    if (highlight)
    {
        printHighlighted(numberedOption(selected, opt, highlight));
        return;
    }

    cout << numberedOption(selected, opt);
}

Menu::Menu(vector<MenuOption> options, string title)
    : options(options), title(title) {}

Menu::~Menu() {}

void Menu::start(MenuContext context) const
{
    vector<MenuOption> opt = this->options;

    opt.push_back({
        context.isRoot() ? "Exit" : "Back",
        [](MenuContext context)
        {
            context.pop();
        },
    });

    int selected = 0;

    cout << "\x1b[?25l";

    cout << "\x1b[34m";

    if (title != "")
    {

        cout << "\x1b[4m";

        cout << endl;
        cout << title + ":" << endl;

        cout << "\x1b[24m";

        cout << "\x1b[34m";
    }

    if (options.size() == 0)
    {
        cout << "  No options to show" << endl;
    }

    for (int i = 0; i < opt.size(); i++)
    {
        printLineAt(i, &opt);

        if (i != opt.size() - 1)
        {
            cout << endl;
        }
    }

    // Save cursor position
    cout << "\x1b[s";

    // Move cursor up
    if (opt.size() > 1)
    {
        cout << "\x1b[" + to_string(opt.size() - 1 - selected) + "A";
    }

    printLineAt(selected, &opt, true);

    char c;

    while (c != 13)
    {

        system("stty raw");
        c = getchar();
        system("stty cooked");

        switch (c)
        {

        // Up arrow
        case 65:
            // If the selected option is not the first one
            if (selected > 0)
            {
                printLineAt(selected, &opt);
                selected--;
                cout << "\x1b[A";
                printLineAt(selected, &opt, true);
                break;
            }

            if (loopOptions && opt.size() > 1)
            {
                printLineAt(selected, &opt);
                selected = opt.size() - 1;
                cout << "\x1b[" + to_string(opt.size() - 1) + "B";
            }

            printLineAt(selected, &opt, true);
            break;
        // Down arrow
        case 66:

            if (selected < opt.size() - 1)
            {
                printLineAt(selected, &opt);
                selected++;
                cout << "\x1b[B";
                printLineAt(selected, &opt, true);
                break;
            }

            if (loopOptions && opt.size() > 1)
            {
                printLineAt(selected, &opt);
                selected = 0;
                cout << "\x1b[" + to_string(opt.size() - 1) + "A";
            }

            printLineAt(selected, &opt, true);
            break;
        default:

            printLineAt(selected, &opt, true);
            break;
        }
    }

    cout << "\x1b[u"
         << "\x1b[0m"
         << "\x1b[?25h" << endl;

    opt[selected].func(context);
}
