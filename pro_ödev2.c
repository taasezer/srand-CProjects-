#include <stdio.h>
#include <math.h>

void toplama(int sayiAdet);
void cikarma(int sayiAdet);
void carpma(int sayiAdet);
void bolme(int sayiAdet);
void usAlma(double a, double b);
void karekok(double a);
void trigonometrikIslemler(double a);

int main() {
    int secim, sayiAdet;

    // Kullanıcıdan işlem seçimi al
    printf("Yapmak istediğiniz işlemi seçin:\n");
    printf("1. Toplama\n");
    printf("2. Çıkarma\n");
    printf("3. Çarpma\n");
    printf("4. Bölme\n");
    printf("5. Üslü Alma (ilk sayı ^ ikinci sayı)\n");
    printf("6. Karekök Alma (bir sayı)\n");
    printf("7. Trigonometri (sin, cos, tan) - (ilk sayı için)\n");
    printf("Seçiminiz: ");
    scanf("%d", &secim);

    // Kullanıcıdan sayı adedini al
    if (secim >= 1 && secim <= 4) {
        printf("Kaç sayı ile işlem yapmak istiyorsunuz? ");
        scanf("%d", &sayiAdet);
    } else if (secim == 5 || secim == 6 || secim == 7) {
        sayiAdet = 1; // Bu işlemler için sadece bir sayı yeterlidir
    } else {
        printf("Geçersiz seçim!\n");
        return 0;
    }

    // Seçime göre ilgili fonksiyonu çağır
    switch (secim) {
        case 1:
            toplama(sayiAdet);
            break;
        case 2:
            cikarma(sayiAdet);
            break;
        case 3:
            carpma(sayiAdet);
            break;
        case 4:
            bolme(sayiAdet);
            break;
        case 5: {
            double a, b;
            printf("Üslü alma işlemi için iki sayı girin (a^b): ");
            scanf("%lf %lf", &a, &b);
            usAlma(a, b);
            break;
        }
        case 6: {
            double a;
            printf("Karekök almak istediğiniz sayıyı girin: ");
            scanf("%lf", &a);
            karekok(a);
            break;
        }
        case 7: {
            double a;
                        printf("Trigonometri işlemi için bir sayı girin (radyan cinsinden): ");
            scanf("%lf", &a);
            trigonometrikIslemler(a);
            break;
        }
        default:
            printf("Geçersiz seçim!\n");
    }

    return 0;
}

// Toplama işlemi
void toplama(int sayiAdet) {
    double toplam = 0;
    for (int i = 0; i < sayiAdet; i++) {
        double sayi;
        printf("%d. sayıyı girin: ", i + 1);
        scanf("%lf", &sayi);
        toplam += sayi;
    }
    printf("Toplam: %.2lf\n", toplam);
}

// Çıkarma işlemi
void cikarma(int sayiAdet) {
    double sonuc;
    printf("1. sayıyı girin: ");
    scanf("%lf", &sonuc);
    for (int i = 1; i < sayiAdet; i++) {
        double sayi;
        printf("%d. sayıyı girin: ", i + 1);
        scanf("%lf", &sayi);
        sonuc -= sayi;
    }
    printf("Sonuç: %.2lf\n", sonuc);
}

// Çarpma işlemi
void carpma(int sayiAdet) {
    double sonuc = 1;
    for (int i = 0; i < sayiAdet; i++) {
        double sayi;
        printf("%d. sayıyı girin: ", i + 1);
        scanf("%lf", &sayi);
        sonuc *= sayi;
    }
    printf("Çarpım: %.2lf\n", sonuc);
}

// Bölme işlemi
void bolme(int sayiAdet) {
    double sonuc;
    printf("1. sayıyı girin: ");
    scanf("%lf", &sonuc);
    for (int i = 1; i < sayiAdet; i++) {
        double sayi;
        printf("%d. sayıyı girin: ", i + 1);
        scanf("%lf", &sayi);
        if (sayi != 0) {
            sonuc /= sayi;
        } else {
            printf("Bir sayıyı sıfıra bölemezsiniz!\n");
            return;
        }
    }
    printf("Sonuç: %.2lf\n", sonuc);
}

// Üslü alma işlemi
void usAlma(double a, double b) {
    printf("Sonuç: %.2lf\n", pow(a, b));
}

// Karekök alma işlemi
void karekok(double a) {
    if (a >= 0) {
        printf("Sonuç: %.2lf\n", sqrt(a));
    } else {
        printf("Negatif sayının karekökü alınamaz!\n");
    }
}

// Trigonometri işlemleri
void trigonometrikIslemler(double a) {
    printf("Sinüs: %.2lf\n", sin(a));
    printf("Kosinüs: %.2lf\n", cos(a));
    printf("Tanjant: %.2lf\n", tan(a));
}