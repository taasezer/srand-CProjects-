#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Kitap bilgilerini tutan struct
struct Kitap {
    int id;
    string baslik;
    string yazar;
    int yayinYili;
};

// Kitap listesini tutan global vektör
vector<Kitap> kutuphane;

// Kullanıcıdan kitap bilgilerini alarak kitap ekleme
void kitapEkle() {
    Kitap yeniKitap;

    cout << "\n--- Kitap Ekle ---\n";
    cout << "Kitap ID: ";
    cin >> yeniKitap.id;
    cin.ignore();  // newline karakterini temizle

    cout << "Kitap Başliği: ";
    getline(cin, yeniKitap.baslik);

    cout << "Kitap Yazari: ";
    getline(cin, yeniKitap.yazar);

    cout << "Yayin Yili: ";
    cin >> yeniKitap.yayinYili;

    kutuphane.push_back(yeniKitap);
    cout << "Kitap başariyla eklendi!\n";
}

// Kitapları listeleme
void kitaplariListele() {
    cout << "\n--- Kütüphanedeki Kitaplar ---\n";
    for (const auto& kitap : kutuphane) {
        cout << "ID: " << kitap.id
             << " | Başlik: " << kitap.baslik
             << " | Yazar: " << kitap.yazar
             << " | Yil: " << kitap.yayinYili << endl;
    }
    if (kutuphane.empty()) {
        cout << "Kütüphanede kitap bulunmuyor.\n";
    }
}

// Kullanıcıdan kelime alarak başlığa göre arama yapma
void kitapAra() {
    string aranan;
    cin.ignore(); // Önceki cin'den kalan newline karakterini temizle
    cout << "\nAranacak kitap başligi (tamami veya parçasi): ";
    getline(cin, aranan);

    cout << "\n--- Arama Sonuçlari ---\n";
    bool bulundu = false;

    for (const auto& kitap : kutuphane) {
        if (kitap.baslik.find(aranan) != string::npos) {
            cout << "ID: " << kitap.id
                 << " | Başlik: " << kitap.baslik
                 << " | Yazar: " << kitap.yazar
                 << " | Yil: " << kitap.yayinYili << endl;
            bulundu = true;
        }
    }

    if (!bulundu) {
        cout << "Aradiginiz kriterde kitap bulunamadi.\n";
    }
}

int main() {
    int secim;

    do {
        cout << "\n=== Kütüphane Sistemi ===\n";
        cout << "1. Kitap Ekle\n";
        cout << "2. Kitaplari Listele\n";
        cout << "3. Kitap Ara\n";
        cout << "4. Çikiş\n";
        cout << "Seçiminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                kitapEkle();
                break;
            case 2:
                kitaplariListele();
                break;
            case 3:
                kitapAra();
                break;
            case 4:
                cout << "Programdan çikiliyor...\n";
                break;
            default:
                cout << "Geçersiz seçim. Tekrar deneyin.\n";
        }

    } while (secim != 4);

    return 0;
}

