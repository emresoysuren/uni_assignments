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

#include <iostream>
#include <cmath>
using namespace std;

#include "Sinif.h"
#include "structlar.h"

int main()
{
    // Ciktiyi sola dayali yazdir.
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

    cout << "Yil içi puaninin geçme notuna etkisini belirleyiniz: ";

    {
        float yilIciEtki;

        cin >> yilIciEtki;

        yilIciEtki = yilIciEtki / pow(10, ceil(log10(yilIciEtki)));

        katsayilar.yilIciEtki = yilIciEtki;
    }

    cout << "Ogrenci sayisini belirleyiniz: ";
    cin >> ogrenciSayisi;

    // Icinde girilen ogrenci sayisi kadar ogrenci bulunan bir sinif olustur.

    Sinif sinifBilgisi(ogrenciSayisi, katsayilar);

    // Gerekli bilgileri yazdir.

    sinifBilgisi.ogrencileriYazdir();

    sinifBilgisi.notDagiliminiYazdir();

    sinifBilgisi.bilgileriYazdir();

    // Programin sona ulastigini belirt.

    cout << "\nProgramin Sonunu" << endl;

    return 0;
}
