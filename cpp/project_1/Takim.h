#pragma once

#include <string>
using namespace std;

class Takim
{
private:
    int takimNo;
    string isim;
    string adres;
    string tel;
    unsigned int oyuncuSayisi;
    string yonetici;

public:
    Takim(int takimNo, string isim, string adres, string tel, unsigned int oyuncuSayisi, string yonetici)
        : takimNo(takimNo), isim(isim), adres(adres), tel(tel), oyuncuSayisi(oyuncuSayisi), yonetici(yonetici)
    {
    }
    ~Takim() {}

    static Takim takimNoIleBul(int takimNo)
    {
        return Takim(takimNo, "", "", "", 0, "");
    }
};
