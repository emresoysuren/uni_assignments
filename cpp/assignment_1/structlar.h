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

#ifndef STRUCTLAR_H
#define STRUCTLAR_H

#include <string>
using namespace std;

// Belirlenmiş not seviyeleri hakkindaki bilgileri içerir.
struct NotBilgisi
{
    string harf;
    float katsayi;
    float sayisal;
};

struct SinavKatsayilari
{
    float odev;
    float kisa_sinav;
    float vize;
    float yilIciEtki;
};

#endif