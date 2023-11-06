/****************************************************************************
**					          SAKARYA ÜNİVERSİTESİ
**			        BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				        BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI....: 1
**				ÖĞRENCİ ADI......: Emre Soysüren
**				ÖĞRENCİ NUMARASI.: G221210049
**				DERS GRUBU.......: 2. Öğretim / C Grubu
****************************************************************************/

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include "structlar.h"
#include "Ogrenci.h"

struct Sinif
{
public:
    map<string, int> notDagilimi;
    int ogrenciSayisi;

    Sinif(int ogrenciSayisi, SinavKatsayilari katsayilar) : ogrenciSayisi(ogrenciSayisi), katsayilar(katsayilar)
    {
        // Ogrencileri depolamak icin array yaratir.
        ogrenciler = new Ogrenci[ogrenciSayisi];

        // Verilen sayida rastgele ad ve soyadlar ile
        // rastgele not degeslerinde bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır ve ogrenciler oluştur.
        for (int i = 0; i < ogrenciSayisi; i++)
        {
            Ogrenci ogr = Ogrenci::rastgeleOgrenci(i, ogrenciSayisi);

            *(ogrenciler + i) = ogr;

            // Hesaplanmis degerleri olustur

            NotBilgisi notBilgisi = ogr.netNot(katsayilar);

            notDagilimi[notBilgisi.harf]++;

            // Ortalamayi hesapla
            ortalama += notBilgisi.sayisal / ogrenciSayisi;

            // "En" degerlerini belirle
            if (enDusukNot == -1 || notBilgisi.sayisal < enDusukNot)
            {
                enDusukNot = notBilgisi.sayisal;
            }

            if (notBilgisi.sayisal > enYuksekNot)
            {
                enYuksekNot = notBilgisi.sayisal;
            }
        }

        standartSapma = standartSapmaHesapla(ortalama);
    }

    ~Sinif()
    {
        delete[] ogrenciler;
    }

    void notDagiliminiYazdir()
    {

        tabloYazdir({"Notlarin Sayisal Dagilimi (Net Nota Gore)", "Harf Not", "Alan Kişi Sayisi", "Alan Kişi Yüzdesi"});

        for (auto [k, v] : notDagilimi)
        {
            float notYuzdesi = (float)v / ogrenciSayisi * 100;

            tabloYazdir({}, {k, to_string(v), yuvarlanmisString(notYuzdesi) + "%"});
        }
    }

    void ogrencileriYazdir()
    {

        tabloYazdir({"Ogrenciler ve Notlari", "Sira", "Adi Soyadi", "Yil Ici Not", "Net Not"});

        for (unsigned int i = 0; i < ogrenciSayisi; i++)
        {

            Ogrenci ogr = *(ogrenciler + i);

            // Net notunu hesapla
            NotBilgisi netNotBilgisi = ogr.netNot(katsayilar);

            // Yil ici notunu hesapla
            NotBilgisi yilIciNotBilgisi = ogr.yilIciNot(katsayilar);

            // Ad Soyad ve Yil Sonu notunu yazdir Yazdir
            tabloYazdir({}, {to_string(ogr.no + 1), ogr.ad + " " + ogr.soyad, yilIciNotBilgisi.harf + " (" + yuvarlanmisString(yilIciNotBilgisi.sayisal) + ")", netNotBilgisi.harf + " (" + yuvarlanmisString(netNotBilgisi.sayisal) + ")"});
        }
    }

    void bilgileriYazdir()
    {
        tabloYazdir({"Sinif Bilgileri", "Ogrenci Sayisi", "Yil Ici Etkisi", "En Dusuk Not", "En Yuksek Not", "Ortalama", "Standart Sapma"},
                    {to_string(ogrenciSayisi), yuvarlanmisString(katsayilar.yilIciEtki * 100) + "%", yuvarlanmisString(enDusukNot), yuvarlanmisString(enYuksekNot), yuvarlanmisString(ortalama), yuvarlanmisString(standartSapma)});
    }

private:
    Ogrenci *ogrenciler;
    SinavKatsayilari katsayilar;

    // Hesaplanmis degerler
    float enDusukNot = -1;
    float enYuksekNot = -1;
    float ortalama = 0;
    float standartSapma = 0;

    float standartSapmaHesapla(float ortalama)
    {
        float deger = 0;

        for (int i = 0; i < ogrenciSayisi; i++)
        {
            NotBilgisi notBilgisi = (ogrenciler + i)->netNot(katsayilar);
            deger += pow(notBilgisi.sayisal - ortalama, 2);
        }

        return sqrt(deger / (ogrenciSayisi - 1));
    }

    string yuvarlanmisString(float sayi)
    {
        string sayiStringi = to_string(sayi);
        return sayiStringi.substr(0, sayiStringi.find(".") + 3);
    }

    void tabloYazdir(vector<string> basliklar, vector<string> degerler = {}, int genislik = 20, bool baslik = true)
    {
        if (basliklar.size() > 0)
        {
            cout << endl;

            if (baslik)
            {
                int satirBoyutu = genislik * (basliklar.size() - 1);

                int solKenar = floor((satirBoyutu - basliklar[0].size()) / 2);

                cout << setw(satirBoyutu) << string(solKenar - 2, '-') + "[ " + basliklar[0] + " ]" + string(satirBoyutu - basliklar[0].size() - solKenar - 2, '-') << endl;
            }

            for (string baslik : basliklar)
            {
                if (baslik == basliklar[0])
                {
                    continue;
                }

                cout << setw(genislik) << baslik;
            }

            cout << endl
                 << string(genislik * (basliklar.size() - 1), '-') << endl;
        }

        if (degerler.size() > 0)
        {
            for (string deger : degerler)
            {
                cout << setw(genislik) << deger;
            }

            cout << endl;
        }
    }
};
