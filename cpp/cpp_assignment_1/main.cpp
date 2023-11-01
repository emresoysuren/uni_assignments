/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI....: 1
**				ÖĞRENCİ ADI......: Emre Soysüren
**				ÖĞRENCİ NUMARASI.: G221210049
**				DERS GRUBU.......: C
****************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
using namespace std;

struct SinavKatsayilari
{
    float odev;
    float kisa_sinav;
    float vize;
    float yilIciEtki = -1.0;
};

struct Ogrenci
{
    string ad;
    string soyad;
    float vize;
    float odev[2];
    float kisa_sinav[2];
    float final_sinavi;
};

// Belirlenmiş not seviyeleri hakkindaki bilgileri içerir.
struct NotBilgisi
{
    string harf;
    float katsayi;
    float sayisal;
};

struct SinifBilgisi
{
    float enDusukNot = -1;
    float enYuksekNot = -1;
    float ortalama = 0;
    float standartSapma = 0;
};

int rastgeleSayi(int, int);
Ogrenci rastgeleOgrenci();
void ogrenciyiYazdir(Ogrenci, SinavKatsayilari);
NotBilgisi harfNotBul(float);
NotBilgisi netNot(Ogrenci, SinavKatsayilari);
int rastgeleNot();
NotBilgisi yilIciNot(Ogrenci, SinavKatsayilari);
string yuvarlanmisString(float);

int main()
{

    cout << left;

    // Random fonksiyonunun seedini belirler.
    srand((unsigned int)time(NULL));

    // Sinav ve odev agirlik bilgilerini kullanicidan al.
    SinavKatsayilari katsayilar;

    // Odev agirligini kullanicidan al.
    cout << "Odevlerin (2) agirligini belirleyiniz: ";
    cin >> katsayilar.odev;

    // Sinav agirligini kullanicidan al.
    cout << "Sinavlarin (2) agirligini belirleyiniz: ";
    cin >> katsayilar.kisa_sinav;

    // Vize agirligini kullanicidan al.
    cout << "Vize agirligini belirleyiniz: ";
    cin >> katsayilar.vize;

    // Yil ici puaninin gecme notuna etkisini kullanicidan al.
    while (katsayilar.yilIciEtki < 0 || 1 < katsayilar.yilIciEtki)
    {
        cout << "Yil ici puaninin gecme notuna etkisini belirleyiniz (Deger 0 ile 1 arasinda olmalidir.): ";
        cin >> katsayilar.yilIciEtki;
    }

    // Ogrenci sayisi bilgisini al.
    int ogrenciSayisi;

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> ogrenciSayisi;

    SinifBilgisi sinifBilgisi;

    // Standart Sapma ve Notların Dagilimini bulmak icin liste olusturulur.
    NotBilgisi *notBilgileri = new NotBilgisi[ogrenciSayisi];
    map<string, int> notDagilimi;

    cout << endl
         << setw(70) << "Ogrenciler ve Notlari" << endl;

    cout << setw(10) << "Sira" << setw(20) << "Adi Soyadi" << setw(20) << "Yil Ici Not" << setw(20) << "Net Not" << endl
         << string(70, '-') << endl;

    // Verilen sayida rastgele ad ve soyadlar ile
    // rastgele not değerlerinde ogrenciler oluştur.
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        Ogrenci ogr = rastgeleOgrenci();

        // Sinif bilgilerini net notuyla gunceller
        NotBilgisi netNotBilgisi = netNot(ogr, katsayilar);

        sinifBilgisi.ortalama += netNotBilgisi.sayisal / ogrenciSayisi;

        notDagilimi[netNotBilgisi.harf]++;

        if (sinifBilgisi.enDusukNot == -1 || netNotBilgisi.sayisal < sinifBilgisi.enDusukNot)
        {
            sinifBilgisi.enDusukNot = netNotBilgisi.sayisal;
        }

        if (netNotBilgisi.sayisal > sinifBilgisi.enYuksekNot)
        {
            sinifBilgisi.enYuksekNot = netNotBilgisi.sayisal;
        }

        *(notBilgileri + i) = netNotBilgisi;

        cout << setw(10) << i + 1;

        ogrenciyiYazdir(ogr, katsayilar);
    }

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        NotBilgisi notBilgisi = *(notBilgileri + i);

        sinifBilgisi.standartSapma += pow(notBilgisi.sayisal - sinifBilgisi.ortalama, 2);
    }

    delete[] notBilgileri;

    sinifBilgisi.standartSapma = sqrt(sinifBilgisi.standartSapma / (ogrenciSayisi - 1));

    cout << endl
         << setw(100) << "Sinif Bilgileri" << endl;
    cout << setw(20) << "Ogrenci Sayisi" << setw(20) << "En Dusuk Not" << setw(20) << "En Yuksek Not" << setw(20) << "Ortalama" << setw(20) << "Standart Sapma" << endl
         << string(100, '-') << endl;
    cout << setw(20) << ogrenciSayisi << setw(20) << setprecision(5) << sinifBilgisi.enDusukNot << setw(20) << setprecision(5) << sinifBilgisi.enYuksekNot << setw(20) << setprecision(5) << sinifBilgisi.ortalama << setw(20) << setprecision(5) << sinifBilgisi.standartSapma << endl;

    cout << endl
         << setw(40) << "Notlarin Sayisal Dagilimi (Net Nota Gore)" << endl;
    cout << setw(20) << "Harf Not" << setw(20) << "Alan Kisi Sayisi" << setw(20) << "Alan Kisi Yuzdesi" << endl
         << string(60, '-') << endl;

    for (auto [k, v] : notDagilimi)
    {
        float notYuzdesi = (float)v / ogrenciSayisi * 100;

        cout << setw(20) << k << setw(20) << v << setw(20) << yuvarlanmisString(notYuzdesi) + "%" << endl;
    }

    cout << endl
         << "Programin Sonunu";

    return 0;
}

/* Ogrenci | Baslangic */

void ogrenciyiYazdir(Ogrenci ogr, SinavKatsayilari katsayilar)
{
    // Net notunu hesapla
    NotBilgisi netNotBilgisi = netNot(ogr, katsayilar);

    // Yil ici notunu hesapla
    NotBilgisi yilIciNotBilgisi = yilIciNot(ogr, katsayilar);

    // Ad Soyad ve Yil Sonu notunu yazdir Yazdir
    cout << setw(20) << ogr.ad + " " + ogr.soyad;
    cout << setw(20) << yilIciNotBilgisi.harf + " (" + yuvarlanmisString(yilIciNotBilgisi.sayisal) + ")";
    cout << setw(20) << netNotBilgisi.harf + " (" + yuvarlanmisString(netNotBilgisi.sayisal) + ")" << endl;
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

Ogrenci rastgeleOgrenci()
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
        ad[rastgeleSayi(0, 29)],
        soyad[rastgeleSayi(0, 29)],
        (float)rastgeleNot(),
        {

            (float)rastgeleNot(),
            (float)rastgeleNot(),
        },
        {

            (float)rastgeleNot(),
            (float)rastgeleNot(),
        },
        (float)rastgeleNot(),
    };
}

/* Ogrenci | Bitis */

/* Fonksiyonel | Baslangic */

// Verilen min ve max değerlerine göre rastgele bir sayi seçer. min ve max dahildir.
int rastgeleSayi(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Rastgele bir şekilde %20'si 80 ile 100 arasi, %50'si 80 ile 50 arasi, %30'u 50 ile 0 arasi
// ogrencinin notlarina atanabilicek notlar oluşturur.
int rastgeleNot()
{
    // 0 - 1 => 81, 100
    // 2 - 6 => 51, 80
    // 7 - 9 => 0, 50
    switch (rastgeleSayi(0, 9))
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

// Mevcut olan bütün modlar büyükten küçüğe siralanir.
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
    // ilerle ve not için gereken minimum not sağlandiğinda fonksiyondan dön.
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