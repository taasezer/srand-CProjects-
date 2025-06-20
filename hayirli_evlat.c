#include <stdio.h>
#include <string.h>

#define MAX_RANDEVU 10
#define SAAT_UZUNLUGU 6
#define ISIM_UZUNLUGU 30

typedef struct {
    char saat[SAAT_UZUNLUGU]; // Randevu saati
    char isim[ISIM_UZUNLUGU]; // Randevu alan kişinin ismi
    int dolu; // Randevunun dolu olup olmadığını belirten durum
} Randevu;

Randevu randevular[MAX_RANDEVU]; // Randevu dizisi

// Randevu almak için kullanılan fonksiyon
void randevuAl() {
    char saat[SAAT_UZUNLUGU]; // Girilecek saat
    char isim[ISIM_UZUNLUGU]; // Girilecek isim
    printf("Randevu almak istediğiniz saati girin (Saat:Dakika formatında): ");
    scanf("%s", saat);
    printf("Adınızı girin: ");
    scanf("%s", isim);

    // Girilen saatin dolu olup olmadığını kontrol et
    for (int i = 0; i < MAX_RANDEVU; i++) {
        if (strcmp(randevular[i].saat, saat) == 0) {
            printf("Bu saat dolu. Lütfen başka bir saat deneyin.\n");
            return; // Eğer doluysa fonksiyonu sonlandır
        }
    }

    // Randevu alacak boş yer bul
    for (int i = 0; i < MAX_RANDEVU; i++) {
        if (randevular[i].dolu == 0) {
            strcpy(randevular[i].saat, saat); // Saati kaydet
            strcpy(randevular[i].isim, isim); // İsimi kaydet
            randevular[i].dolu = 1; // Randevuyu dolu olarak işaretle
            printf("Randevunuz başarıyla alındı: %s, %s\n", isim, saat);
            return; // Randevu alındıktan sonra fonksiyonu sonlandır
        }
    }

    printf("Tüm randevu saatleri dolu.\n"); // Eğer tüm randevular doluysa
}
// made by TahaSezer
// Randevu iptali için kullanılan fonksiyon
void randevuIptal() {
    char saat[SAAT_UZUNLUGU]; // İptal edilecek randevu saati
    char isim[ISIM_UZUNLUGU]; // İptal edilecek randevu sahibi ismi
    printf("İptal etmek istediğiniz randevu saatini girin (Saat:Dakika formatında): ");
    scanf("%s", saat);
    printf("Adınızı girin: ");
    scanf("%s", isim);

    // Girilen saatin ve ismin eşleşip eşleşmediğini kontrol et
    for (int i = 0; i < MAX_RANDEVU; i++) {
        if (strcmp(randevular[i].saat, saat) == 0 && randevular[i].dolu == 1 && strcmp(randevular[i].isim, isim) == 0) {
            randevular[i].dolu = 0; // Randevuyu iptal et
            printf("Randevunuz başarıyla iptal edildi: %s, %s\n", isim, saat);
            return; // İptal edildikten sonra fonksiyonu sonlandır
        }
    }

    printf("Bu saatte alınmış bir randevu bulunmamaktadır.\n"); // Eğer randevu bulunamazsa
}

// Alınmış randevuları görüntülemek için kullanılan fonksiyon
void randevulariGor() {
    printf("Alınmış randevular:\n");
    for (int i = 0; i < MAX_RANDEVU; i++) {
        if (randevular[i].dolu == 1) {
            printf("- %s: %s\n", randevular[i].isim, randevular[i].saat); // Dolu olan randevuları yazdır
        }
    }
}

int main() {
    int secim; // Kullanıcının seçeceği işlem

    do {
        printf("\nBerber Randevu Sistemi\n");
        printf("1. Randevu Al\n");
        printf("2. Randevu İptal Et\n");
        printf("3. Alınmış Randevuları Gör\n");
        printf("4. Çıkış\n");
        printf("Seçiminizi yapın: ");
        scanf("%d", &secim); // Kullanıcının seçim yapması

        switch (secim) {
            case 1:
                randevuAl(); // Randevu alma fonksiyonunu çağır
                break;
            case 2:
                randevuIptal(); // Randevu iptal etme fonksiyonunu çağır
                break;
            case 3:
                randevulariGor(); // Alınmış randevuları gösterme fonksiyonunu çağır
                break;
            case 4:
                printf("Çıkılıyor...\n"); // Çıkış mesajı
                break;
            default:
                printf("Geçersiz seçim. Lütfen tekrar deneyin.\n"); // Geçersiz seçim durumunda uyarı
        }
    } while (secim != 4); // Kullanıcı çıkış yapana kadar döngü devam eder

    return 0; // Programın başarılı bir şekilde sonlandığını belirtir
}