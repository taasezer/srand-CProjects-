// MadeByFerit
// Kutuphane yonetim sistemi C++ diliyle
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Kitap sinifi kitap bilgilerinin tutuldugu sinif
class Kitap {
private:
    int id;
    string ad;
    string yazar;
    int yil;

public:
    Kitap(int id, string ad, string yazar, int yil) {
        this->id = id;
        this->ad = ad;
        this->yazar = yazar;
        this->yil = yil;
    }

    int getId() const {
        return id;
    }

    string getAd() const {
        return ad;
    }

    string getYazar() const {
        return yazar;
    }

    int getYil() const {
        return yil;
    }

    void goster() const {
        cout << "ID: " << id << " | Ad: " << ad << " | Yazar: " << yazar << " | Yil: " << yil << endl;
    }
};

// Kutuphane sinifi kitaplarin tutuldugu ve islemlerin yapildigi sinif
class Kutuphane {
private:
    vector<Kitap> kitaplar;
    int sonrakiId;

public:
    Kutuphane() {
        sonrakiId = 1; // MadeByFerit
    }

    // Kitap ekleme fonksiyonu
    void kitapEkle(const string& ad, const string& yazar, int yil) {
        Kitap yeniKitap(sonrakiId, ad, yazar, yil);
        kitaplar.push_back(yeniKitap);
        cout << "Kitap eklendi. ID: " << sonrakiId << endl;
        sonrakiId++;
    }

    // Kayitli butun kitaplari listeleme fonksiyonu
    void kitapListele() const {
        if (kitaplar.empty()) {
            cout << "Kutuphane bos." << endl;
            return;
        }
        cout << "--- Kitap Listesi ---" << endl;
        for (const auto& kitap : kitaplar) {
            kitap.goster();
        }
    }

    // Id ile kitap arama fonksiyonu
    void kitapAraId(int id) const {
        auto it = find_if(kitaplar.begin(), kitaplar.end(), [id](const Kitap& k) {
            return k.getId() == id;
        });
        if (it != kitaplar.end()) {
            cout << "Kitap bulundu:" << endl;
            it->goster();
        } else {
            cout << "Kitap bulunamadi." << endl;
        }
    }

    // Ada gore kitap arama fonksiyonu
    void kitapAraAd(const string& ad) const {
        vector<Kitap> bulunanlar;
        for (const auto& kitap : kitaplar) {
            if (kitap.getAd().find(ad) != string::npos) {
                bulunanlar.push_back(kitap);
            }
        }
        if (bulunanlar.empty()) {
            cout << "Kitap bulunamadi." << endl;
        } else {
            cout << bulunanlar.size() << " kitap bulundu:" << endl;
            for (const auto& k : bulunanlar) {
                k.goster();
            }
        }
    }

    // Kitap silme fonksiyonu ID kullanarak
    void kitapSil(int id) {
        auto it = remove_if(kitaplar.begin(), kitaplar.end(), [id](const Kitap& k) {
            return k.getId() == id;
        });
        if (it != kitaplar.end()) {
            kitaplar.erase(it, kitaplar.end());
            cout << "Kitap silindi." << endl;
        }
        else {
            cout << "Kitap bulunamadi." << endl;
        }
    }
};

int main() {
    Kutuphane kutuphane;
    int secim;

    while (true) {
        cout << "\n--- Kutuphane Yonetim Sistemi ---\n";
        cout << "1. Kitap Ekle\n";
        cout << "2. Kitap Listele\n";
        cout << "3. Kitap Ara (ID ile)\n";
        cout << "4. Kitap Ara (Ad ile)\n";
        cout << "5. Kitap Sil (ID ile)\n";
        cout << "6. Cikis\n";
        cout << "Seciminizi girin: ";
        cin >> secim;

        if (secim == 6) {
            cout << "Programdan cikiliyor..." << endl;
            break;
        }

        switch (secim) {
            case 1: {
                // MadeByFerit - Kitap bilgilerini kullanicidan al ve ekle
                string ad, yazar;
                int yil;
                cout << "Kitap adi (turkce karakter kullanma): ";
                cin.ignore();
                getline(cin, ad);
                cout << "Yazar adi (turkce karakter kullanma): ";
                getline(cin, yazar);
                cout << "Yayim yili: ";
                cin >> yil;
                kutuphane.kitapEkle(ad, yazar, yil);
                break;
            }
            case 2: {
                kutuphane.kitapListele();
                break;
            }
            case 3: {
                int id;
                cout << "Aranan kitap ID: ";
                cin >> id;
                kutuphane.kitapAraId(id);
                break;
            }
            case 4: {
                cout << "Aranan kitap adi: ";
                string ad;
                cin.ignore();
                getline(cin, ad);
                kutuphane.kitapAraAd(ad);
                break;
            }
            case 5: {
                int id;
                cout << "Silinecek kitap ID: ";
                cin >> id;
                kutuphane.kitapSil(id);
                break;
            }
            default:
                cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl;
        }
    }

    return 0;
}

