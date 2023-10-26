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
#include <cstring>
#include <math.h>
#include <map>
using namespace std;

struct AgirlikKatsayileri
{
    float odev;
    float kisaSinav;
    float vize;
};

struct Ogrenci
{
    string isim;
    string soyisim;
    float vize;
    float odev[2];
    float kisa_sinav[2];
};

// Belirlenmiş not seviyeleri hakkindaki bilgileri içerir.
struct NotBilgisi
{
    string harf;
    float katsayi;
    float sayisalNot;
};

struct Sinif
{
    float enDusukNot = -1;
    float enYuksekNot = -1;
    float ortalama = 0;
    float standartSapma = 0;
};

int rastgeleSayi(int, int);
Ogrenci rastgeleOgrenciOlustur();
void ogrenciYilsonuNotuYazdir(Ogrenci, AgirlikKatsayileri);
NotBilgisi notuBul(float);
NotBilgisi yilSonuNotuHesapla(Ogrenci, AgirlikKatsayileri);

int main()
{

    // Random fonksiyonunun seedini belirler.
    srand((unsigned int)time(NULL));

    // Sinav ve odev agirlik bilgilerini kullanicidan al.
    AgirlikKatsayileri agirliklar;

    // Odev agirligini kullanicidan al.
    cout << "Odevlerin (2) agirligini belirleyiniz: ";
    cin >> agirliklar.odev;

    // Sinav agirligini kullanicidan al.
    cout << "Sinavlarin (2) agirligini belirleyiniz: ";
    cin >> agirliklar.kisaSinav;

    // Vize agirligini kullanicidan al.
    cout << "Vize agirligini belirleyiniz: ";
    cin >> agirliklar.vize;

    // Ogrenci sayisi bilgisini al.
    int ogrenciSayisi;

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> ogrenciSayisi;

    Sinif sinif;

    // Standart Sapma ve Notların Dagilimini bulmak icin liste olusturulur.
    // NotBilgisi *notlar = (NotBilgisi *)malloc(sizeof(NotBilgisi) * ogrenciSayisi);
    NotBilgisi *notlar = new NotBilgisi[ogrenciSayisi];
    map<string, int> notuAlanlar;

    string baslik = "Ogrenciler ve Yil Sonu Notlari";

    printf("\n|%*s%s%*s|\n", (41 - strlen(baslik.c_str())) / 2, "", baslik.c_str(), (41 - strlen(baslik.c_str())) / 2, "");
    printf("|%-20s|%-20s|\n", "Adi Soyadi", "Harf Not (Sayisal)");

    // Verilen sayida rastgele ad ve soyadlar ile
    // rastgele not değerlerinde ogrenciler oluştur.
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        Ogrenci ogr = rastgeleOgrenciOlustur();

        // Sinif bilgilerini yil sonu notuyla gunceller
        NotBilgisi yilSonuNotu = yilSonuNotuHesapla(ogr, agirliklar);

        sinif.ortalama += yilSonuNotu.sayisalNot / ogrenciSayisi;

        notuAlanlar[yilSonuNotu.harf]++;

        if (sinif.enDusukNot == -1 || yilSonuNotu.sayisalNot < sinif.enDusukNot)
        {
            sinif.enDusukNot = yilSonuNotu.sayisalNot;
        }
        if (yilSonuNotu.sayisalNot > sinif.enYuksekNot)
        {
            sinif.enYuksekNot = yilSonuNotu.sayisalNot;
        }

        *(notlar + i) = yilSonuNotu;

        ogrenciYilsonuNotuYazdir(ogr, agirliklar);
    }

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        NotBilgisi notBilgisi = *(notlar + i);

        sinif.standartSapma += pow(notBilgisi.sayisalNot - sinif.ortalama, 2);
    }

    delete[] notlar;

    sinif.standartSapma = sqrt(sinif.standartSapma / (ogrenciSayisi - 1));

    baslik = "Sinif Bilgileri";

    printf("\n|%*s%s%*s|\n", (83 - strlen(baslik.c_str())) / 2, "", baslik.c_str(), (83 - strlen(baslik.c_str())) / 2, "");
    printf("|%-20s|%-20s|%-20s|%-20s|\n", "En Dusuk Not", "En Yuksek Not", "Ortalama", "Standart Sapma");
    printf("|%-20.2f|%-20.2f|%-20.2f|%-20.2f|\n", sinif.enDusukNot, sinif.enYuksekNot, sinif.ortalama, sinif.standartSapma);

    baslik = "Notlarin Sayisal Dagilimi";

    printf("\n|%*s%s%*s|\n", (41 - strlen(baslik.c_str())) / 2, "", baslik.c_str(), (41 - strlen(baslik.c_str())) / 2, "");
    printf("|%-20s|%-20s|\n", "Harf Not", "Alan Kisi Sayisi");

    for (auto [k, v] : notuAlanlar)
    {
        printf("|%-20s|%-20d|\n", k.c_str(), v);
    }

    cout << "\nProgramin Sonuna Ulasildi";

    return 0;
}

/* Ogrenci | Baslangic */

void ogrenciYilsonuNotuYazdir(Ogrenci ogr, AgirlikKatsayileri agirliklar)
{
    // Yil sonu notunu hesapla
    NotBilgisi yilSonuNotu = yilSonuNotuHesapla(ogr, agirliklar);

    // Ad Soyad ve Yil Sonu notunu yazdir Yazdir
    printf("|%-20s|%-20s|\n", (ogr.isim + " " + ogr.soyisim).c_str(), (yilSonuNotu.harf + " (" + to_string(yilSonuNotu.sayisalNot) + ")").c_str());
}

NotBilgisi yilSonuNotuHesapla(Ogrenci ogr, AgirlikKatsayileri agirliklar)
{
    float yilSonuNotu = (ogr.odev[0] + ogr.odev[1]) * (agirliklar.odev / 100) + (ogr.kisa_sinav[0] + ogr.kisa_sinav[1]) * (agirliklar.kisaSinav / 100) + ogr.vize * (agirliklar.vize / 100);

    NotBilgisi notBilgisi = notuBul(yilSonuNotu);

    notBilgisi.sayisalNot = yilSonuNotu;

    return notBilgisi;
}

Ogrenci rastgeleOgrenciOlustur()
{

    // Rastgele isim secimi yapilirken kulanilicak isimlerin bulundugi liste.
    const string isim[10] = {
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
    };

    // Rastgele soyismi secimi yapilirken kulanilicak soyisimlerin bulundugi liste.
    const string soyisim[10] = {
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
    };

    // Rastgele bir şekilde %20'si 80 ile 100 arasi, %50'si 80 ile 50 arasi, %30'u 50 ile 0 arasi
    // ogrencinin notlarina atanabilicek notlar oluşturur.
    const int atanabilicekNotlar[10] = {
        rastgeleSayi(81, 100),
        rastgeleSayi(81, 100),
        rastgeleSayi(51, 80),
        rastgeleSayi(51, 80),
        rastgeleSayi(51, 80),
        rastgeleSayi(51, 80),
        rastgeleSayi(51, 80),
        rastgeleSayi(0, 50),
        rastgeleSayi(0, 50),
        rastgeleSayi(0, 50),
    };

    // Ogrencinin bilgilerini rastgele oluşturup bunu döner.
    return Ogrenci{
        isim[rastgeleSayi(0, 9)],
        soyisim[rastgeleSayi(0, 9)],
        (float)atanabilicekNotlar[rastgeleSayi(0, 9)],
        {

            (float)atanabilicekNotlar[rastgeleSayi(0, 9)],
            (float)atanabilicekNotlar[rastgeleSayi(0, 9)],
        },
        {

            (float)atanabilicekNotlar[rastgeleSayi(0, 9)],
            (float)atanabilicekNotlar[rastgeleSayi(0, 9)],
        },
    };
}

/* Ogrenci | Bitis */

/* Fonksiyonel | Baslangic */

// Verilen min ve max değerlerine göre rastgele bir sayi seçer. min ve max dahildir.
int rastgeleSayi(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

/* Fonksiyonel | Bitis */

/* Sinav Notu | Baslangic */

// Mevcut olan bütün modlar büyükten küçüğe siralanir.
const NotBilgisi sinvaNotlari[9] = {
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
NotBilgisi notuBul(float sayiNot)
{
    // Sinav notlarindaki notlarda yüksek nottan başlayarak sirayla
    // ilerle ve not için gereken minimum not sağlandiğinda fonksiyondan dön.
    for (int i = 0; i < 9; i++)
    {
        NotBilgisi notBilgisi = sinvaNotlari[i];

        if (sayiNot > notBilgisi.sayisalNot)
        {
            return notBilgisi;
        }
    }

    throw "Harf not degeri cevrilemedi.";
}

/* Sinav Notu | Bitis */