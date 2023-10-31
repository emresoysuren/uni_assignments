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

struct AgirlikKatsayileri
{
    float odev;
    float kisaSinav;
    float vize;
    float yilIciEtki = -1.0;
};

struct Ogrenci
{
    string isim;
    string soyisim;
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
NotBilgisi netNotuHesapla(Ogrenci, AgirlikKatsayileri);
int rastgeleNot();
NotBilgisi yilIciNotuHesapla(Ogrenci, AgirlikKatsayileri);
string yuvarlanmisString(float);

int main()
{

    cout << left;

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

    // Yil ici puaninin gecme notuna etkisini kullanicidan al.
    while (agirliklar.yilIciEtki < 0 || 1 < agirliklar.yilIciEtki)
    {
        cout << "Yil ici puaninin gecme notuna etkisini belirleyiniz (Deger 0 ile 1 arasinda olmalidir.): ";
        cin >> agirliklar.yilIciEtki;
    }

    // Ogrenci sayisi bilgisini al.
    int ogrenciSayisi;

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> ogrenciSayisi;

    Sinif sinif;

    // Standart Sapma ve Notların Dagilimini bulmak icin liste olusturulur.
    // NotBilgisi *notlar = (NotBilgisi *)malloc(sizeof(NotBilgisi) * ogrenciSayisi);
    NotBilgisi *notlar = new NotBilgisi[ogrenciSayisi];
    map<string, int> notuAlanlar;

    cout << endl
         << setw(60) << "Ogrenciler ve Notlari" << endl;
    cout << setw(20) << "Adi Soyadi" << setw(20) << "Yil Ici Not" << setw(20) << "Net Not" << endl
         << string(60, '-') << endl;

    // Verilen sayida rastgele ad ve soyadlar ile
    // rastgele not değerlerinde ogrenciler oluştur.
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        Ogrenci ogr = rastgeleOgrenciOlustur();

        // Sinif bilgilerini net notuyla gunceller
        NotBilgisi netNot = netNotuHesapla(ogr, agirliklar);

        sinif.ortalama += netNot.sayisalNot / ogrenciSayisi;

        notuAlanlar[netNot.harf]++;

        if (sinif.enDusukNot == -1 || netNot.sayisalNot < sinif.enDusukNot)
        {
            sinif.enDusukNot = netNot.sayisalNot;
        }

        if (netNot.sayisalNot > sinif.enYuksekNot)
        {
            sinif.enYuksekNot = netNot.sayisalNot;
        }

        *(notlar + i) = netNot;

        ogrenciYilsonuNotuYazdir(ogr, agirliklar);
    }

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        NotBilgisi notBilgisi = *(notlar + i);

        sinif.standartSapma += pow(notBilgisi.sayisalNot - sinif.ortalama, 2);
    }

    delete[] notlar;

    sinif.standartSapma = sqrt(sinif.standartSapma / (ogrenciSayisi - 1));

    cout << endl
         << setw(100) << "Sinif Bilgileri" << endl;
    cout << setw(20) << "Ogrenci Sayisi" << setw(20) << "En Dusuk Not" << setw(20) << "En Yuksek Not" << setw(20) << "Ortalama" << setw(20) << "Standart Sapma" << endl
         << string(100, '-') << endl;
    cout << setw(20) << ogrenciSayisi << setw(20) << setprecision(5) << sinif.enDusukNot << setw(20) << setprecision(5) << sinif.enYuksekNot << setw(20) << setprecision(5) << sinif.ortalama << setw(20) << setprecision(5) << sinif.standartSapma << endl;

    cout << endl
         << setw(40) << "Notlarin Sayisal Dagilimi (Net Nota Gore)" << endl;
    cout << setw(20) << "Harf Not" << setw(20) << "Alan Kisi Sayisi" << setw(20) << "Alan Kisi Yuzdesi" << endl
         << string(60, '-') << endl;

    for (auto [k, v] : notuAlanlar)
    {
        float yuzde = (float)v / ogrenciSayisi * 100;

        cout << setw(20) << k << setw(20) << v << setw(20) << yuvarlanmisString(yuzde) + "%" << endl;
    }

    cout << endl
         << "Programin Sonunu";

    return 0;
}

/* Ogrenci | Baslangic */

void ogrenciYilsonuNotuYazdir(Ogrenci ogr, AgirlikKatsayileri agirliklar)
{
    // Net notunu hesapla
    NotBilgisi netNot = netNotuHesapla(ogr, agirliklar);

    // Yil ici notunu hesapla
    NotBilgisi yilIciNot = yilIciNotuHesapla(ogr, agirliklar);

    // Ad Soyad ve Yil Sonu notunu yazdir Yazdir
    cout << setw(20) << ogr.isim + " " + ogr.soyisim;
    cout << setw(20) << yilIciNot.harf + " (" + yuvarlanmisString(yilIciNot.sayisalNot) + ")";
    cout << setw(20) << netNot.harf + " (" + yuvarlanmisString(netNot.sayisalNot) + ")" << endl;
}

NotBilgisi netNotuHesapla(Ogrenci ogr, AgirlikKatsayileri agirliklar)
{

    float yilIciEtki = agirliklar.yilIciEtki;

    float netNot = yilIciNotuHesapla(ogr, agirliklar).sayisalNot * yilIciEtki + (1 - yilIciEtki) * ogr.final_sinavi;

    NotBilgisi notBilgisi = notuBul(netNot);

    notBilgisi.sayisalNot = netNot;

    return notBilgisi;
}

NotBilgisi yilIciNotuHesapla(Ogrenci ogr, AgirlikKatsayileri agirliklar)
{
    float agirlikPaydasi = agirliklar.kisaSinav * 2 + agirliklar.odev * 2 + agirliklar.vize;

    float yilIciNot = (ogr.odev[0] + ogr.odev[1]) * (agirliklar.odev / agirlikPaydasi) + (ogr.kisa_sinav[0] + ogr.kisa_sinav[1]) * (agirliklar.kisaSinav / agirlikPaydasi) + ogr.vize * (agirliklar.vize / agirlikPaydasi);

    NotBilgisi notBilgisi = notuBul(yilIciNot);

    notBilgisi.sayisalNot = yilIciNot;

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

    // Ogrencinin bilgilerini rastgele oluşturup bunu döner.
    return Ogrenci{
        isim[rastgeleSayi(0, 9)],
        soyisim[rastgeleSayi(0, 9)],
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
    string yazi = to_string(sayi);
    return yazi.substr(0, yazi.find(".") + 3);
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

        if (sayiNot >= notBilgisi.sayisalNot)
        {
            return notBilgisi;
        }
    }

    throw "Harf not degeri cevrilemedi.";
}

/* Sinav Notu | Bitis */