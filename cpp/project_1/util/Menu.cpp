#include <sstream>

#include "Menu.h"
#include "MenuContext.h"

std::string Menu::numberedOption(int i, std::vector<MenuOption> *opt, bool chosed) const
{
    std::string optionPrefix;

    if (chosed)
    {
        optionPrefix += "> ";
    }
    else
    {
        optionPrefix += "  ";
    }

    return optionPrefix + "[" + std::to_string(i) + "] " + (*opt)[i].title;
}

void Menu::printLineAt(int index, std::vector<MenuOption> *opt, bool highlight) const
{
    std::cout << "\r\x1b[K";

    if (highlight)
    {
        if ((*opt)[index].func.has_value())
        {
            // Green color
            std::cout << "\x1b[92m";
        }
        else
        {
            // Red color
            std::cout << "\x1b[91m";
        }

        std::cout << numberedOption(index, opt, highlight);

        return;
    }

    if ((*opt)[index].func.has_value())
    {
        // Blue color
        std::cout << "\x1b[94m";
    }
    else
    {
        // Black color
        std::cout << "\x1b[90m";
    }

    std::cout << numberedOption(index, opt);
}

#ifdef _WIN32
// Windows specific code
#include <conio.h>

int Menu::getKey()
{
    int key;

    key = getch();

    return key;
}

#define UP_KEY 119
#define DOWN_KEY 115
#define ENTER_KEY 13
#define BACK_KEY '\b'

#else
// Unix/Linux specific code
#include <unistd.h>
#include <termios.h>

int Menu::getKey()
{
    struct termios originalTermios;
    int key;

    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    key = getchar();

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);

    return key;
}

#define UP_KEY 65
#define DOWN_KEY 66
#define ENTER_KEY 10
#define BACK_KEY 68

#endif

void Menu::printDescription() const
{
    std::stringstream ss(description);

    std::string line;

    std::cout << "\x1b[95m";

    while (getline(ss, line))
    {
        std::cout << "  " + line << std::endl;
    }
}

Menu::Menu(std::vector<MenuOption> options, std::string title, std::string description, bool showNoOptions)
    : options(options), title(title), description(description), showNoOptions(showNoOptions) {}

Menu::~Menu() {}

void Menu::start(MenuContext context, bool useContext) const
{
    std::vector<MenuOption> opt = this->options;

    if (useContext)
    {
        opt.push_back({
            context.isRoot() ? "Exit" : "Back",
            [](MenuContext context)
            {
                context.pop();
            },
        });
    }

    int selected = 0;

    std::cout << "\x1b[?25l";

    std::cout << "\x1b[94m";

    if (title != "")
    {

        std::cout << "\x1b[4m";

        // std::cout << std::endl;
        std::cout << title + ":" << std::endl;

        std::cout << "\x1b[24m";
    }

    printDescription();

    if (showNoOptions && options.size() == 0)
    {
        std::cout << "  No options to show" << std::endl;
    }

    for (int i = 0; i < opt.size(); i++)
    {
        printLineAt(i, &opt);

        if (i != opt.size() - 1)
        {
            std::cout << std::endl;
        }
    }

    // Save cursor position
    std::cout << "\x1b[s";

    // Move cursor up
    if (opt.size() > 1)
    {
        std::cout << "\x1b[" + std::to_string(opt.size() - 1 - selected) + "A";
    }

    printLineAt(selected, &opt, true);

    char c;

    while (c != ENTER_KEY || !opt[selected].func.has_value())
    {
        c = getKey();

        switch (c)
        {
        // Up arrow
        case UP_KEY:
            printLineAt(selected, &opt);

            if (selected > 0)
            {
                selected--;
                std::cout << "\x1b[A";
            }
            else if (loopOptions && opt.size() > 1)
            {
                selected = opt.size() - 1;
                std::cout << "\x1b[" + std::to_string(opt.size() - 1) + "B";
            }

            printLineAt(selected, &opt, true);
            break;
        // Down arrow
        case DOWN_KEY:
            printLineAt(selected, &opt);

            if (selected < opt.size() - 1)
            {
                selected++;
                std::cout << "\x1b[B";
            }
            else if (loopOptions && opt.size() > 1)
            {
                selected = 0;
                std::cout << "\x1b[" + std::to_string(opt.size() - 1) + "A";
            }

            printLineAt(selected, &opt, true);
            break;
        case BACK_KEY:
            selected = opt.size() - 1;
            c = ENTER_KEY;
            break;
        default:
            printLineAt(selected, &opt, true);
            break;
        }
    }

    resetConsole();

    opt[selected].func.value()(context);
}

void Menu::resetConsole()
{
    std::cout << "\x1b[u"
              << "\x1b[0m"
              << "\x1b[?25h" << std::endl;
}
