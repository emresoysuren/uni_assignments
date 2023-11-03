#ifndef STRUCTLAR_H
#define STRUCTLAR_H

struct NotBilgisi;

#include <string>
using namespace std;

// Belirlenmiş not seviyeleri hakkindaki bilgileri içerir.
struct NotBilgisi
{
    string harf;
    float katsayi;
    float sayisal;
};

struct Ogrenci
{
    int no;
    string ad;
    string soyad;
    float vize;
    float odev[2];
    float kisa_sinav[2];
    float final_sinavi;
};

struct RastgeleOgrenciBilgileri
{
    int sira;
    int ogrenciSayisi;
    int calistirmaKaristirici;
};

struct SinavKatsayilari
{
    float odev;
    float kisa_sinav;
    float vize;
    float yilIciEtki = -1.0;
};

#endif