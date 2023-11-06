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

#ifndef OGRENCI_H
#define OGRENCI_H

#include <string>
using namespace std;

#include "structlar.h"
#include "Sinif.h"

class Ogrenci
{
public:
    int no;
    string ad;
    string soyad;
    float vize;
    float odev[2];
    float kisa_sinav[2];
    float final_sinavi;

    NotBilgisi netNot(SinavKatsayilari katsayilar)
    {
        float sayisalNot = yilIciNot(katsayilar).sayisal * katsayilar.yilIciEtki + (1 - katsayilar.yilIciEtki) * final_sinavi;

        NotBilgisi notBilgisi = harfNotBul(sayisalNot);

        notBilgisi.sayisal = sayisalNot;

        return notBilgisi;
    }

    NotBilgisi yilIciNot(SinavKatsayilari katsayilar)
    {
        float agirlikPaydasi = katsayilar.kisa_sinav * 2 + katsayilar.odev * 2 + katsayilar.vize;

        float yilIciNot = (odev[0] + odev[1]) * (katsayilar.odev / agirlikPaydasi) + (kisa_sinav[0] + kisa_sinav[1]) * (katsayilar.kisa_sinav / agirlikPaydasi) + vize * (katsayilar.vize / agirlikPaydasi);

        NotBilgisi notBilgisi = harfNotBul(yilIciNot);

        notBilgisi.sayisal = yilIciNot;

        return notBilgisi;
    }

    static Ogrenci rastgeleOgrenci(int no, int ogrenciSayisi)
    {
        // Rastgele isim secimi yapilirken kulanilicak isimlerin bulundugi liste.
        static const string ad[30] = {
            "Ali",
            "Veli",
            "Ayse",
            "Ahmet",
            "Mehmet",
            "Yaren",
            "Zeynep",
            "Hatice",
            "Murat",
            "Pelin",
            "Ufuk",
            "Mustafa",
            "Ceren",
            "Hasan",
            "Dilek",
            "Erol",
            "Ebru",
            "Evrim",
            "Engin",
            "Sevgi",
            "Tuba",
            "Bilge",
            "Aysun",
            "Seda",
            "Baturay",
            "Mesut",
            "Ilkay",
            "Serdar",
            "Elif",
            "Osman",
        };

        // Rastgele soyismi secimi yapilirken kulanilicak soyisimlerin bulundugi liste.
        static const string soyad[30] = {
            "Yilmaz",
            "Ates",
            "Cavus",
            "Kara",
            "Yakin",
            "Kaya",
            "Cetin",
            "Sert",
            "Gonul",
            "Aydin",
            "Aksel",
            "Dal",
            "Tahtaci",
            "Kulaksiz",
            "Yildiz",
            "Temel",
            "Topal",
            "Aytac",
            "Gunduz",
            "Yuksel",
            "Cengiz",
            "Yildirim",
            "Gul",
            "Akar",
            "Olpak",
            "Arslan",
            "Saf",
            "Atay",
            "Ekici",
            "Tas",
        };

        // Ogrencinin bilgilerini rastgele oluşturup bunu döner.

        Ogrenci ogr;

        ogr.no = no;
        ogr.ad = ad[rastgeleSayi(0, 29)];
        ogr.soyad = soyad[rastgeleSayi(0, 29)];
        ogr.vize = rastgeleNot(ogrenciSayisi);
        ogr.kisa_sinav[0] = rastgeleNot(ogrenciSayisi);
        ogr.kisa_sinav[1] = rastgeleNot(ogrenciSayisi);
        ogr.odev[0] = rastgeleNot(ogrenciSayisi);
        ogr.odev[1] = rastgeleNot(ogrenciSayisi);
        ogr.final_sinavi = rastgeleNot(ogrenciSayisi);

        return ogr;
    }

private:
    // Mevcut olan bütün modlar büyükten bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. küçügessiralanir.

    // Verilen sayisal nota göre sinav notunu bulur.
    // Bulunan sinav notu harf, katsayi ve alt not bilgilerini bulundurur.
    static NotBilgisi harfNotBul(float sayisalNot)
    {
        const NotBilgisi harfNotlar[9] = {
            {"AA", 4.0, 90},
            {"BA", 3.5, 85},
            {"BB", 3.0, 80},
            {"CB", 2.5, 75},
            {"CC", 2.0, 65},
            {"DC", 1.5, 58},
            {"DD", 1.0, 50},
            {"FD", 0.5, 40},
            {"FF", 0.0, 0},
        };

        // Sinav notlarindaki notlarda yüksek nottan başlayarak sirayla
        // ilerle ve not için gereken minimum not saglsndigisda bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. fonksiyondan dön.
        for (int i = 0; i < 9; i++)
        {
            NotBilgisi notBilgisi = harfNotlar[i];

            if (sayisalNot >= notBilgisi.sayisal)
            {
                return notBilgisi;
            }
        }

        throw;
    }

    // Verilen min ve max degeslerine bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. göre rastgele bir sayi seçer. min ve max dahildir.
    static int rastgeleSayi(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    // Rastgele bir şekilde %20'si 80 ile 100 arasi, %50'si 80 ile 50 arasi, %30'u 50 ile 0 arasi
    // ogrencinin notlarina atanabilicek notlar oluşturur.
    static float rastgeleNot(int ogrenciSayisi)
    {
        static float altNotDagilimi[2];

        int sinavSayisi = ogrenciSayisi * 6;

        while (true)
        {
            switch (rastgeleSayi(0, 2))
            {
            case 0:
                if (altNotDagilimi[0] < round(sinavSayisi * 0.2))
                {
                    altNotDagilimi[0]++;
                    return (float)rastgeleSayi(81, 100);
                }
                break;
            case 1:
                if (altNotDagilimi[1] < sinavSayisi - round(sinavSayisi * 0.2) - round(sinavSayisi * 0.3))
                {
                    altNotDagilimi[1]++;
                    return (float)rastgeleSayi(51, 80);
                }
                break;
            case 2:
                if (altNotDagilimi[2] < round(sinavSayisi * 0.3))
                {
                    altNotDagilimi[2]++;
                    return (float)rastgeleSayi(0, 50);
                }
                break;
            }
        }
    };
};
#endif