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
using namespace std;

#include "sinif_bilgileri.h"
#include "structlar.h"
#include "ogrenci.h"

int main()
{
    SinifBilgisi sinifBilgisi;

    cout << left;

    int rastgeleOgrenciBilgiSayisi = rand() % 1200;

    // Random fonksiyonunun seedini belirler.
    srand((unsigned int)time(NULL));

    // Agirlik bilgilerini ve ogrenci sayisini kullanicidan al.

    cout << "Odevlerin (2) agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.odev;

    cout << "Sinavlarin (2) agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.kisa_sinav;

    cout << "Vize agirligini belirleyiniz: ";
    cin >> sinifBilgisi.katsayilar.vize;

    while (sinifBilgisi.katsayilar.yilIciEtki < 0 || 1 < sinifBilgisi.katsayilar.yilIciEtki)
    {
        cout << "Yil ici puaninin gecme notuna etkisini belirleyiniz (Deger 0 ile 1 arasinda olmalidir.): ";
        cin >> sinifBilgisi.katsayilar.yilIciEtki;
    }

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> sinifBilgisi.ogrenciSayisi;

    // Ogrencileri depolamak icin array yaratir.
    sinifBilgisi.ogrenciler = new Ogrenci[sinifBilgisi.ogrenciSayisi];

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

        *(sinifBilgisi.ogrenciler + i) = ogr;
    }

    sinifBilgisi.ogrencileriYazdir();

    sinifBilgisi.notDagilimi(true);

    delete[] sinifBilgisi.ogrenciler;

    sinifBilgisi.bilgileriYazdir();

    cout << endl
         << "Programin Sonunu";

    return 0;
}
