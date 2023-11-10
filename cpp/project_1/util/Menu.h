#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

// Menu option struct
struct MenuOption
{
    string title;
    function<void()> func;
};

/// @brief A class to create and handle menus visually in the terminal
class Menu
{
private:
    string title;
    vector<MenuOption> options;

    /// @brief Formats the option at the given index
    /// @param i The index of the option to format
    /// @param chosed Whether to format the option as chosed or not
    /// @return The formatted option
    string numberedOption(int i, bool chosed = false)
    {
        string optionPrefix;

        // Add ">" if the option is chosed
        if (chosed)
        {
            optionPrefix += "> ";
        }
        else
        {
            optionPrefix += "  ";
        }

        // Add the index and title of the option and return it
        return optionPrefix + "[" + to_string(i) + "] " + options[i].title;
    }

    /// @brief Prints the given text in green and bold
    /// @param text The text to print
    void printHighlighted(string text)
    {
        // Change color to green and bold
        cout << "\x1b[32m";
        cout << "\x1b[1m";

        cout << text;

        // Reset color and bold
        cout << "\x1b[22m";
        cout << "\x1b[34m";
    }

    /// @brief Prints the option at the given index
    /// @param selected The index of the option to print
    /// @param highlight Whether to highlight the option or not
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
    /// @brief Create a menu with the given options and title
    /// @param options The options of the menu
    /// @param title The title of the menu
    Menu(vector<MenuOption> options, string title = "")
        : options(options), title(title) {}

    ~Menu() {}

    /// @brief Start the menu with the given options
    void start()
    {
        int selected = 0;

        // Hide cursor
        cout << "\x1b[?25l";

        // Change color to blue
        cout << "\x1b[34m";

        // Print title if it exists
        if (title != "")
        {
            // Set underline
            cout << "\x1b[4m";

            // Format and print title
            cout << endl;
            cout << title + ":" << endl;

            // Remove underline
            cout << "\x1b[24m";

            // Change color to blue
            cout << "\x1b[34m";
        }

        if (options.size() == 0)
        {
            cout << "No options to show" << endl;
            return;
        }

        for (int i = 0; i < options.size(); i++)
        {
            // Print option
            printLineAt(i);

            // Print new line if it's not the last option
            if (i != options.size() - 1)
            {
                cout << endl;
            }
        }

        // Save cursor position
        cout << "\x1b[s";

        // Go to the selected option and print the line again to move the cursor to the end of the line
        cout << "\x1b[" + to_string(options.size() - 1 - selected) + "A";
        printLineAt(selected, true);

        // Wait for input and handle it until the user presses enter (13)
        char c;

        while (c != 13)
        {
            // Get single char without enter
            system("stty raw");
            c = getchar();
            system("stty cooked");

            // Handle input
            switch (c)
            {
            // Up arrow
            case 65:
                // Check if it's not the first option and move the cursor up if it's not
                if (selected > 0)
                {
                    printLineAt(selected);
                    selected--;
                    cout << "\x1b[A";
                    printLineAt(selected, true);
                    break;
                }
                printLineAt(selected, true);
                break;
            // Down arrow
            case 66:
                // Check if it's not the last option and move the cursor down if it's not
                if (selected < options.size() - 1)
                {
                    printLineAt(selected);
                    selected++;
                    cout << "\x1b[B";
                    printLineAt(selected, true);
                    break;
                }
                printLineAt(selected, true);
                break;
            default:
                // Print the line again to remove the input char
                printLineAt(selected, true);
                break;
            }
        }

        // Restore cursor position, color and show cursor
        cout << "\x1b[u"
             << "\x1b[0m"
             << "\x1b[?25h" << endl;

        // Call the function of the selected option
        options[selected].func();
    }
};
