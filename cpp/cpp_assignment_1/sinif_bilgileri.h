#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

#include "structlar.h"

extern NotBilgisi netNot(Ogrenci, SinavKatsayilari);
extern string yuvarlanmisString(float);
extern NotBilgisi yilIciNot(Ogrenci, SinavKatsayilari);

struct SinifBilgisi
{
public:
    float enDusukNot = -1;
    float enYuksekNot = -1;
    float ortalama = 0;
    float standartSapma = 0;
    Ogrenci *ogrenciler;
    int ogrenciSayisi;
    SinavKatsayilari katsayilar;

    map<string, int> notDagilimi(bool print)
    {

        map<string, int> dagilim;

        for (unsigned int i = 0; i < ogrenciSayisi; i++)
        {
            NotBilgisi netNotBilgisi = netNot(*(ogrenciler + i), katsayilar);

            dagilim[netNotBilgisi.harf]++;
        }

        if (print)
        {
            cout << endl
                 << setw(40) << "Notlarin Sayisal Dagilimi (Net Nota Gore)" << endl;
            cout << setw(20) << "Harf Not" << setw(20) << "Alan Kisi Sayisi" << setw(20) << "Alan Kisi Yuzdesi" << endl
                 << string(60, '-') << endl;

            for (auto [k, v] : dagilim)
            {
                float notYuzdesi = (float)v / ogrenciSayisi * 100;

                cout << setw(20) << k << setw(20) << v << setw(20) << yuvarlanmisString(notYuzdesi) + "%" << endl;
            }
        }

        return dagilim;
    }

    /* Ogrenci | Baslangic */

    void ogrencileriYazdir()
    {
        for (unsigned int i = 0; i < ogrenciSayisi; i++)
        {

            Ogrenci ogr = *(ogrenciler + i);

            // Net notunu hesapla
            NotBilgisi netNotBilgisi = netNot(ogr, katsayilar);

            // Yil ici notunu hesapla
            NotBilgisi yilIciNotBilgisi = yilIciNot(ogr, katsayilar);

            // Ad Soyad ve Yil Sonu notunu yazdir Yazdir
            cout << setw(10) << ogr.no + 1;
            cout << setw(20) << ogr.ad + " " + ogr.soyad;
            cout << setw(20) << yilIciNotBilgisi.harf + " (" + yuvarlanmisString(yilIciNotBilgisi.sayisal) + ")";
            cout << setw(20) << netNotBilgisi.harf + " (" + yuvarlanmisString(netNotBilgisi.sayisal) + ")" << endl;
        }
    }
};