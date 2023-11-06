#include "Futbolcu.h"
#include "Takim.h"
#include "./util/Menu.h"

void anaMenuBaslat();
void takimMenusuBaslat();
void oyuncuMenusuBaslat();
void genelBilgiMenusuBaslat();

int main()
{

    anaMenuBaslat();

    return 0;
}

void anaMenuBaslat()
{
    cout << "\x1b[2J";
    cout << "\x1b[H";

    Menu({
             MenuOgesi{
                 "Takimi Yonet",
                 takimMenusuBaslat,
             },
             MenuOgesi{
                 "Oyunculari Yonet",
                 oyuncuMenusuBaslat,

             },
             MenuOgesi{
                 "Genel Bilgileri Goster",
                 genelBilgiMenusuBaslat,
             },
         },
         "Ana Menu")
        .baslat();
}

void takimMenusuBaslat()
{
    Menu({
             {"Takim Olustur", []() {}},
             {"Takim Sil", []() {}},
             {"Takima Oyuncu Ekle", []() {}},
             {"Takimdan Oyuncu Sil", []() {}},
             {"Takimdaki Oyuncuyu Guncelle", []() {}},
             {"Takimdaki Oyunculari Listele", []() {}},
             {"Geri Don", anaMenuBaslat},
         },
         "Takimi Yonet")
        .baslat();
}

void oyuncuMenusuBaslat()
{
    Menu({
             {"Oyuncu Ekle", []() {}},
             {"Oyuncu Sil", []() {}},
             {"Oyuncu Guncelle", []() {}},
             {"Oyunculari Listele", []() {}},
             {"Geri Don", anaMenuBaslat},
         },
         "Oyunculari Yonet")
        .baslat();
}

void genelBilgiMenusuBaslat()
{
    Menu({
             {"Oyun kayitlarini goster", []() {}},
             {"Geri Don", anaMenuBaslat},
         },
         "Genel Bilgileri Goster")
        .baslat();
}