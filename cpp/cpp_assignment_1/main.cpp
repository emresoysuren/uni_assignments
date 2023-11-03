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
#include "ogrenci.h"
using namespace std;

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

    int rastgeleOgrenciBilgiSayisi = rand() % 1200;

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

        Ogrenci ogr = Ogrenci::rastgeleOgrenci(rastgeleBilgiler);

        // Sinif bilgilerini net notuyla gunceller
        NotBilgisi netNotBilgisi = ogr.netNot(sinifBilgisi.katsayilar);

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
        NotBilgisi notBilgisi = (sinifBilgisi.ogrenciler + i)->netNot(sinifBilgisi.katsayilar);

        sinifBilgisi.standartSapma += pow(notBilgisi.sayisal - sinifBilgisi.ortalama, 2);
    }

    sinifBilgisi.ogrencileriYazdir();

    sinifBilgisi.notDagilimi(true);

    delete[] sinifBilgisi.ogrenciler;

    sinifBilgisi.standartSapma = sqrt(sinifBilgisi.standartSapma / (sinifBilgisi.ogrenciSayisi - 1));

    sinifBilgisi.bilgileriYazdir();

    cout << endl
         << "Programin Sonunu";

    return 0;
}
