#include "Futbolcu.h"
#include "Takim.h"
#include "./util/Menu.h"

int main()
{
    Menu menu({
        "Takimi Yonet",
        "Oyunculari Yonet",
        "Genel Bilgileri Goster",
    });

    switch (menu.baslat())
    {
    case 0:
        Menu({
                 "Takim Olustur",
                 "Takim Sil",
                 "Takima Oyuncu Ekle",
                 "Takimdan Oyuncu Sil",
                 "Takimdaki Oyuncuyu Guncelle",
                 "Takimdaki Oyunculari Listele",
                 "Geri Dön",
             },
             "Takimi Yonet")
            .baslat();
        break;
    case 1:
        Menu({
                 "Oyuncu Ekle",
                 "Oyuncu Sil",
                 "Oyuncu Guncelle",
                 "Oyunculari Listele",
                 "Geri Dön",
             },
             "Oyunculari Yonet")
            .baslat();
        break;
    case 2:
        Menu({
                 "Oyun kayitlarini goster",
                 "Geri Dön",
             },
             "Genel Bilgileri Goster")
            .baslat();
        break;
    default:
        throw "Hatali secim!";
    }

    return 0;
}