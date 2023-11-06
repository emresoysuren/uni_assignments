#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Menu
{
private:
    string baslik;
    vector<string> secenekler;

    string numaralandirilmisSecenek(int i, bool sec = false)
    {
        string secenekIsareti;

        if (sec)
        {
            secenekIsareti += "> ";
        }
        else
        {
            secenekIsareti += "  ";
        }

        return secenekIsareti + "[" + to_string(i) + "] " + secenekler[i];
    }

    void secimYazdir(string s)
    {
        cout << "\x1b[32m";
        cout << s;
        cout << "\x1b[34m";
    }

    void seciliSatiriYaz(int secim, bool sec = false)
    {
        cout << "\r\x1b[K";

        if (sec)
        {
            secimYazdir(numaralandirilmisSecenek(secim, sec));
            return;
        }

        cout << numaralandirilmisSecenek(secim);
    }

public:
    Menu(vector<string> secenekler, string baslik = "")
        : secenekler(secenekler), baslik(baslik) {}
    ~Menu() {}

    int baslat()
    {
        int secim = secenekler.size() - 1;

        cout << "\x1b[34m";

        if (baslik != "")
        {
            cout << "\x1b[4m";

            cout << endl;
            cout << baslik + ":" << endl;

            cout << "\x1b[0m";
            cout << "\x1b[34m";
        }

        for (int i = 0; i < secenekler.size(); i++)
        {

            if (i == secim)
            {
                seciliSatiriYaz(i, true);
                continue;
            }
            seciliSatiriYaz(i);
            cout << endl;
        }

        cout << "\x1b[4i";

        cout << "\x1b[s";

        char c;

        while (c != 13)
        {
            system("stty raw");
            c = getwchar();
            system("stty cooked");

            switch (c)
            {
            case 65:
                if (secim > 0)
                {
                    seciliSatiriYaz(secim);
                    secim--;
                    cout << "\x1b[A";
                    seciliSatiriYaz(secim, true);
                }
                break;
            case 66:
                if (secim < secenekler.size() - 1)
                {
                    seciliSatiriYaz(secim);
                    secim++;
                    cout << "\x1b[B";
                    seciliSatiriYaz(secim, true);
                }
                break;
            default:
                seciliSatiriYaz(secim, true);
                break;
            }
        }

        cout << "\x1b[u"
             << "\x1b[0m" << endl;

        return secim;
    }
};

#endif // MENU_H