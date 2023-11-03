/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİgİsBÖLÜMÜ bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır.
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI....: 1
**				ÖgRsNCİ bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. ADI......: Emre Soysüren
**				ÖgRsNCİ bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. NUMARASI.: G221210049
**				DERS GRUBU.......: C
****************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include "sinif_bilgileri.h"
#include "structlar.h"
using namespace std;

int rastgeleSayi(int, int);
int rastgeleNot(int, RastgeleOgrenciBilgileri);
string yuvarlanmisString(float);
NotBilgisi yilIciNot(Ogrenci, SinavKatsayilari);
NotBilgisi harfNotBul(float);
Ogrenci rastgeleOgrenci(RastgeleOgrenciBilgileri);
NotBilgisi netNot(Ogrenci, SinavKatsayilari);

int main()
{
    SinifBilgisi sinifBilgisi;

    cout << left;

    // Random fonksiyonunun seedini belirler.
    srand((unsigned int)time(NULL));

    // Sinav ve odev agirlik bilgilerini kullanicidan al.

    // Odev agirligini kullanicidan al.
    cout << "Odevlerin (2) agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.odev;

    // Sinav agirligini kullanicidan al.
    cout << "Sinavlarin (2) agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.kisa_sinav;

    // Vize agirligini kullanicidan al.
    cout << "Vize agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.vize;

    // Yil ici puaninin gecme notuna etkisini kullanicidan al.
    while (sinifBilgisi.katsayilar.yilIciEtki < 0 || 1 < sinifBilgisi.katsayilar.yilIciEtki)
    {
        cout << "Yil ici puaninin gecme notuna etkisini belirleyiniz (Deger 0 ile 1 arasinda olmalidir.): ";
        cin >> sinifBilgisi.katsayilar.yilIciEtki;
    }

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> sinifBilgisi.ogrenciSayisi;

    int rastgeleOgrenciBilgiSayisi = rastgeleSayi(0, 1199);

    // Standart Sapma ve Notlarin Dagilimini bulmak icin liste olusturulur.
    // NotBilgisi *notBilgileri = new NotBilgisi[ogrenciSayisi];
    sinifBilgisi.ogrenciler = new Ogrenci[sinifBilgisi.ogrenciSayisi];

    cout << endl
         << setw(70) << "Ogrenciler ve Notlari" << endl;

    cout << setw(10) << "Sira" << setw(20) << "Adi Soyadi" << setw(20) << "Yil Ici Not" << setw(20) << "Net Not" << endl
         << string(70, '-') << endl;

    // Verilen sayida rastgele ad ve soyadlar ile
    // rastgele not degeslerinde bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. ogrenciler oluştur.
    for (int i = 0; i < sinifBilgisi.ogrenciSayisi; i++)
    {

        RastgeleOgrenciBilgileri rastgeleBilgiler = {
            i,
            sinifBilgisi.ogrenciSayisi,
            rastgeleOgrenciBilgiSayisi,
        };

        Ogrenci ogr = rastgeleOgrenci(rastgeleBilgiler);

        // Sinif bilgilerini net notuyla gunceller
        NotBilgisi netNotBilgisi = netNot(ogr, sinifBilgisi.katsayilar);

        sinifBilgisi.ortalama += netNotBilgisi.sayisal / sinifBilgisi.ogrenciSayisi;

        if (sinifBilgisi.enDusukNot == -1 || netNotBilgisi.sayisal < sinifBilgisi.enDusukNot)
        {
            sinifBilgisi.enDusukNot = netNotBilgisi.sayisal;
        }

        if (netNotBilgisi.sayisal > sinifBilgisi.enYuksekNot)
        {
            sinifBilgisi.enYuksekNot = netNotBilgisi.sayisal;
        }

        *(sinifBilgisi.ogrenciler + i) = ogr;
    }

    for (int i = 0; i < sinifBilgisi.ogrenciSayisi; i++)
    {
        NotBilgisi notBilgisi = netNot(*(sinifBilgisi.ogrenciler + i), sinifBilgisi.katsayilar);

        sinifBilgisi.standartSapma += pow(notBilgisi.sayisal - sinifBilgisi.ortalama, 2);
    }

    sinifBilgisi.ogrencileriYazdir();

    sinifBilgisi.notDagilimi(true);

    delete[] sinifBilgisi.ogrenciler;

    sinifBilgisi.standartSapma = sqrt(sinifBilgisi.standartSapma / (sinifBilgisi.ogrenciSayisi - 1));

    cout << endl
         << setw(100) << "Sinif Bilgileri" << endl;
    cout << setw(20) << "Ogrenci Sayisi" << setw(20) << "Yil Ici Etkisi" << setw(20) << "En Dusuk Not" << setw(20) << "En Yuksek Not" << setw(20) << "Ortalama" << setw(20) << "Standart Sapma" << endl
         << string(120, '-') << endl;
    cout << setw(20) << sinifBilgisi.ogrenciSayisi << setw(20) << yuvarlanmisString(sinifBilgisi.katsayilar.yilIciEtki * 100) + "%" << setw(20) << setprecision(5) << sinifBilgisi.enDusukNot << setw(20) << setprecision(5) << sinifBilgisi.enYuksekNot << setw(20) << setprecision(5) << sinifBilgisi.ortalama << setw(20) << setprecision(5) << sinifBilgisi.standartSapma << endl;

    cout << endl
         << "Programin Sonunu";

    return 0;
}

NotBilgisi netNot(Ogrenci ogr, SinavKatsayilari katsayilar)
{
    float netNot = yilIciNot(ogr, katsayilar).sayisal * katsayilar.yilIciEtki + (1 - katsayilar.yilIciEtki) * ogr.final_sinavi;

    NotBilgisi notBilgisi = harfNotBul(netNot);

    notBilgisi.sayisal = netNot;

    return notBilgisi;
}

NotBilgisi yilIciNot(Ogrenci ogr, SinavKatsayilari katsayilar)
{
    float agirlikPaydasi = katsayilar.kisa_sinav * 2 + katsayilar.odev * 2 + katsayilar.vize;

    float yilIciNot = (ogr.odev[0] + ogr.odev[1]) * (katsayilar.odev / agirlikPaydasi) + (ogr.kisa_sinav[0] + ogr.kisa_sinav[1]) * (katsayilar.kisa_sinav / agirlikPaydasi) + ogr.vize * (katsayilar.vize / agirlikPaydasi);

    NotBilgisi notBilgisi = harfNotBul(yilIciNot);

    notBilgisi.sayisal = yilIciNot;

    return notBilgisi;
}

Ogrenci rastgeleOgrenci(RastgeleOgrenciBilgileri bilgi)
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
    return Ogrenci{
        bilgi.sira,
        ad[rastgeleSayi(0, 29)],
        soyad[rastgeleSayi(0, 29)],
        (float)rastgeleNot(0, bilgi),
        {
            (float)rastgeleNot(1, bilgi),
            (float)rastgeleNot(2, bilgi),
        },
        {
            (float)rastgeleNot(3, bilgi),
            (float)rastgeleNot(4, bilgi),
        },
        (float)rastgeleNot(5, bilgi),
    };
}

/* Ogrenci | Bitis */

/* Fonksiyonel | Baslangic */

// Verilen min ve max degeslerine bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. göre rastgele bir sayi seçer. min ve max dahildir.
int rastgeleSayi(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Rastgele bir şekilde %20'si 80 ile 100 arasi, %50'si 80 ile 50 arasi, %30'u 50 ile 0 arasi
// ogrencinin notlarina atanabilicek notlar oluşturur.
int rastgeleNot(int notNo, RastgeleOgrenciBilgileri bilgi)
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

string yuvarlanmisString(float sayi)
{
    string sayiStringi = to_string(sayi);
    return sayiStringi.substr(0, sayiStringi.find(".") + 3);
}

/* Fonksiyonel | Bitis */

/* Sinav Notu | Baslangic */

// Mevcut olan bütün modlar büyükten bunlari tersten bir sekilde yuzdeliklerini belirleyerek rastgelelik yaratır. küçügessiralanir.
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

/* Sinav Notu | Bitis */