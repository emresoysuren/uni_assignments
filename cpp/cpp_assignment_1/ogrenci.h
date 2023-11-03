#ifndef OGRENCI_H
#define OGRENCI_H

#include <string>
using namespace std;

#include "structlar.h"

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
        float netNot = yilIciNot(katsayilar).sayisal * katsayilar.yilIciEtki + (1 - katsayilar.yilIciEtki) * final_sinavi;

        NotBilgisi notBilgisi = harfNotBul(netNot);

        notBilgisi.sayisal = netNot;

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

    static Ogrenci rastgeleOgrenci(RastgeleOgrenciBilgileri bilgi)
    {

        // Rastgele isim secimi yapilirken kulanilicak isimlerin bulundugi liste.
        const string ad[30] = {
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
        const string soyad[30] = {
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

        ogr.no = bilgi.sira;
        ogr.ad = ad[rastgeleSayi(0, 29)];
        ogr.soyad = soyad[rastgeleSayi(0, 29)];
        ogr.vize = (float)rastgeleNot(0, bilgi);
        ogr.kisa_sinav[0] = (float)rastgeleNot(1, bilgi);
        ogr.kisa_sinav[1] = (float)rastgeleNot(2, bilgi);
        ogr.odev[0] = (float)rastgeleNot(3, bilgi);
        ogr.odev[1] = (float)rastgeleNot(4, bilgi);
        ogr.final_sinavi = (float)rastgeleNot(5, bilgi);

        return ogr;
    }

private:
    // Mevcut olan bütün modlar büyükten bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. küçügessiralanir.
    NotBilgisi harfNotlar[9] = {
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

    // Verilen sayisal nota göre sinav notunu bulur.
    // Bulunan sinav notu harf, katsayi ve alt not bilgilerini bulundurur.
    NotBilgisi harfNotBul(float sayisalNot)
    {
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

        throw "Harf not degeri cevrilemedi.";
    }

    // Verilen min ve max degeslerine bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. göre rastgele bir sayi seçer. min ve max dahildir.
    static int rastgeleSayi(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    // Rastgele bir şekilde %20'si 80 ile 100 arasi, %50'si 80 ile 50 arasi, %30'u 50 ile 0 arasi
    // ogrencinin notlarina atanabilicek notlar oluşturur.
    static int rastgeleNot(int notNo, RastgeleOgrenciBilgileri bilgi)
    {

        // Bu sekilde calistirmaKaristirici ya programin basinda rastgele atanan sayi sayesinde
        // program her calismasinda farkli bir sekilde sinav atamalarini yapicaktir.

        int yuzdelik = bilgi.sira + bilgi.calistirmaKaristirici;

        int yuzdelikDegisimSutunPeriyodu = (notNo + bilgi.calistirmaKaristirici % 6) % (bilgi.calistirmaKaristirici % 6);

        // yuzdelikDegisimSutunPeriyodu == 0 : Columnu yenile
        // yuzdelikDegisimSutunPeriyodu + siraNo % 6 == 0 : Columnu 1er 1er kaydirarak yenile
        // yuzdelikDegisimSutunPeriyodu + (<<katsayi>> * siraNo % 6) == 0 : Columnu katsayi ile kaydirarak yenile

        // Rastgele sayida sutunu rastgele bir bicimde secerek degistirir
        // ve bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik saglar.
        if (yuzdelikDegisimSutunPeriyodu + (((int)pow((bilgi.calistirmaKaristirici % 6), (bilgi.calistirmaKaristirici % 3)) % 6 * bilgi.sira) % 6) == 0)
        {
            yuzdelik = bilgi.ogrenciSayisi - bilgi.sira + bilgi.calistirmaKaristirici;
        }

        // 0 - 1 => 81, 100
        // 2 - 6 => 51, 80
        // 7 - 9 => 0, 50
        switch (yuzdelik % 10)
        {
        case 0:
        case 1:
            return rastgeleSayi(81, 100);
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            return rastgeleSayi(51, 81);
        default:
            return rastgeleSayi(0, 50);
        }
    }
};

#endif