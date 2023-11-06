#ifndef FUTBOLCU_H
#define FUTBOLCU_H

#include <string>
#include <ctime>
#include <map>
using namespace std;

#include "Takim.h"

enum Pozisyon
{
    kaleci,
    defans,
    ortasaha,
    forvet,
};

class Futbolcu
{
private:
    string tc;
    string adi;
    string soyadi;
    Takim takim;
    int lisansNo;
    Pozisyon pozisyon;
    int ucreti;
    tm dogumTarihi;

    Pozisyon stringiPozisyonYap(string pozisyon)
    {
        map<string, int> pozisyonlar = {
            {"kaleci", Pozisyon::kaleci},
            {"defans", Pozisyon::defans},
            {"ortasaha", Pozisyon::ortasaha},
            {"forvet", Pozisyon::forvet},
        };

        switch (pozisyonlar[pozisyon])
        {
        case 0:
            return Pozisyon::kaleci;
        case 1:
            return Pozisyon::defans;
        case 2:
            return Pozisyon::ortasaha;
        case 3:
            return Pozisyon::forvet;
        default:
            throw "Pozisyon bulunamadi";
        }
    }

public:
    Futbolcu(string tc, string adi, string soyadi, int takimNo, int lisansNo, string pozisyon, int ucreti, tm dogumTarihi)
        : tc(tc), adi(adi), soyadi(soyadi), takim(Takim::takimNoIleBul(takimNo)), lisansNo(lisansNo), pozisyon(stringiPozisyonYap(pozisyon)), ucreti(ucreti), dogumTarihi(dogumTarihi)
    {
    }
    ~Futbolcu() {}
};

#endif // FUTBOLCU_H