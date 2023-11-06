#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

struct MenuOption
{
    string title;
    function<void()> func;
};

class Menu
{
private:
    string title;
    vector<MenuOption> options;

    string numberedOption(int i, bool chosed = false)
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

        return optionPrefix + "[" + to_string(i) + "] " + options[i].title;
    }

    void printHighlighted(string text)
    {
        cout << "\x1b[32m";
        cout << text;
        cout << "\x1b[34m";
    }

    void printLineAt(int selected, bool highlight = false)
    {
        cout << "\r\x1b[K";

        if (highlight)
        {
            printHighlighted(numberedOption(selected, highlight));
            return;
        }

        cout << numberedOption(selected);
    }

public:
    Menu(vector<MenuOption> options, string title = "")
        : options(options), title(title) {}

    ~Menu() {}

    void start()
    {
        int selected = 0;

        cout << "\x1b[34m";

        if (title != "")
        {
            cout << "\x1b[4m";

            cout << endl;
            cout << title + ":" << endl;

            cout << "\x1b[0m";
            cout << "\x1b[34m";
        }

        for (int i = 0; i < options.size(); i++)
        {

            if (i == selected)
            {
                printLineAt(i, true);
            }
            else
            {
                printLineAt(i);
            }

            if (i != options.size() - 1)
            {
                cout << endl;
            }
        }

        cout << "\x1b[4i";

        cout << "\x1b[s";

        // Go to the first element and print the line again to move the cursor to the end

        cout << "\x1b[" + to_string(options.size() - 1 - selected) + "A";

        printLineAt(selected, true);

        char c;

        while (c != 13)
        {
            system("stty raw");
            c = getwchar();
            system("stty cooked");

            switch (c)
            {
            case 65:
                if (selected > 0)
                {
                    printLineAt(selected);
                    selected--;
                    cout << "\x1b[A";
                    printLineAt(selected, true);
                }
                break;
            case 66:
                if (selected < options.size() - 1)
                {
                    printLineAt(selected);
                    selected++;
                    cout << "\x1b[B";
                    printLineAt(selected, true);
                }
                break;
            default:
                printLineAt(selected, true);
                break;
            }
        }

        cout << "\x1b[u"
             << "\x1b[0m" << endl;

        options[selected].func();
    }
};
