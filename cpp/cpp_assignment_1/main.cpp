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

#include "sinif.h"
#include "structlar.h"
#include "ogrenci.h"

int main()
{

    cout << left;

    // Random fonksiyonunun seedini belirler.
    srand((unsigned int)time(NULL));

    // Agirlik katsayilarini ve ogrenci sayisini kullanicidan al.
    SinavKatsayilari katsayilar;

    int ogrenciSayisi;

    cout << "Odevlerin (2) agirligini belirleyiniz: ";
    cin >> katsayilar.odev;

    cout << "Sinavlarin (2) agirligini belirleyiniz: ";
    cin >> katsayilar.kisa_sinav;

    cout << "Vize agirligini belirleyiniz: ";
    cin >> katsayilar.vize;

    while (katsayilar.yilIciEtki < 0 || 1 < katsayilar.yilIciEtki)
    {
        cout << "Yil ici puaninin gecme notuna etkisini belirleyiniz (Deger 0 ile 1 arasinda olmalidir.): ";
        cin >> katsayilar.yilIciEtki;
    }

    cout << "Ogrenci Sayisini belirleyiniz: ";
    cin >> ogrenciSayisi;

    // Icinde girilen ogrenci sayisi kadar ogrenci bulunan bir sinif olustur.

    Sinif sinifBilgisi(ogrenciSayisi, katsayilar);

    // Gerekli bilgileri yazdir.

    sinifBilgisi.ogrencileriYazdir();

    sinifBilgisi.notDagilimi(true);

    sinifBilgisi.bilgileriYazdir();

    // Programin sona ulastigini belirt.

    cout << "\nProgramin Sonunu" << endl;

    return 0;
}
