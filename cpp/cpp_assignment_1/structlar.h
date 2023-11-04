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
    float yilIciEtki = -1.0;
};

#endif