#include  <stdio.h>

// Ortalama hesaplama fonksiyonu
float hesaplaOrtalama(float vize, float proje, float final) {
    return (vize * 0.3) + (proje * 0.3) + (final * 0.4);
}

// Harf notu hesaplama fonksiyonu
char* hesaplaHarfNotu(float ortalama) {
    if (ortalama >= 90) return "AA";
    else if (ortalama >= 80) return "BA";
    else if (ortalama >= 70) return "BB";
    else if (ortalama >= 60) return "CB";
    else if (ortalama >= 50) return "CC";
    else if (ortalama >= 40) return "DC";
    else if (ortalama >= 30) return "DD";
    else return "FF";
}

// Başarı durumu belirleme fonksiyonu
char* belirleBasariDurumu(char* harfNotu) {
    if (harfNotu[0] == 'A' || harfNotu[0] == 'B' || harfNotu[0] == 'C' || harfNotu[0] == 'D') {
        if (harfNotu[1] == 'D') return "Başarısız";
        else return "Başarılı";
    }
    return "Başarısız";
}

int main() {
    int ogrenciSayisi;

    printf("Kaç öğrencinin notlarını girmek istiyorsunuz? ");
    scanf("%d", &ogrenciSayisi);

    for (int i = 0; i < ogrenciSayisi; i++) {
        float vize, proje, final, ortalama;
        char* harfNotu;
        char* basariDurumu;

        printf("\n%d. öğrencinin notlarını giriniz:\n", i + 1);
        printf("Vize notu: ");
        scanf("%f", &vize);
        printf("Proje notu: ");
        scanf("%f", &proje);
        printf("Final notu: ");
        scanf("%f", &final);

        ortalama = hesaplaOrtalama(vize, proje, final);
        harfNotu = hesaplaHarfNotu(ortalama);
        basariDurumu = belirleBasariDurumu(harfNotu);

        printf("\nSonuçlar:\n");
        printf("Ortalama: %.2f\n", ortalama);
        printf("Harf Notu: %s\n", harfNotu);
        printf("Başarı Durumu: %s\n", basariDurumu);
    }

    return 0;
}
