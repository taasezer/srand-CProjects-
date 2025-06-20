// Made By TahaSezer
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Made By TahaSezer
class Randevu {
private:
    string tarih;
    string saat;
    string musteriAdi;
    string hizmet;
    bool onOdemeliMi;
    double fiyat;
    bool onaylandiMi;
public:
    Randevu(string t, string s, string ma, string h, bool oo, double f)
        : tarih(t), saat(s), musteriAdi(ma), hizmet(h), onOdemeliMi(oo), fiyat(f), onaylandiMi(false) {}
    string getTarih() const { return tarih; }
    string getSaat() const { return saat; }
    string getMusteriAdi() const { return musteriAdi; }
    string getHizmet() const { return hizmet; }
    bool getOnOdemeliMi() const { return onOdemeliMi; }
    double getFiyat() const { return fiyat; }
    bool getOnaylandiMi() const { return onaylandiMi; }
    void setOnayla(bool durum) { onaylandiMi = durum; }
};
// Made By TahaSezer
class Kullanici {
private:
    string kullaniciAdi;
    string sifre;
    bool adminMi;
public:
    Kullanici(string ka, string s, bool admin = false)
        : kullaniciAdi(ka), sifre(s), adminMi(admin) {}

    bool kimlikDogrula(string ka, string s) {
        return kullaniciAdi == ka && sifre == s;
    }

    bool adminKullaniciMi() const { return adminMi; }
    string getKullaniciAdi() const { return kullaniciAdi; }
};
// Made By TahaSezer
class BerberSistemi {
private:
    vector<Kullanici> kullanicilar;
    vector<Randevu> randevular;
    vector<string> adminMesajlari; // Admin mesajlarini saklayacak vector
    Kullanici* mevcutKullanici;

public:
    // Made By TahaSezer
    BerberSistemi() : mevcutKullanici(nullptr) {
        // Admin hesabini ekle: kullanici adi "Taha", sifre "Aett5734"
        kullanicilar.push_back(Kullanici("Taha", "Aett5734", true));
    }

    bool girisYap() {
        string kullaniciAdi, sifre;
        cout << "Kullanici adi: ";
        cin >> kullaniciAdi;
        cout << "Sifre: ";
        cin >> sifre;

        for (size_t i = 0; i < kullanicilar.size(); i++) {
            if (kullanicilar[i].kimlikDogrula(kullaniciAdi, sifre)) {
                mevcutKullanici = &kullanicilar[i];
                return true;
            }
        }
        return false;
    }
    // Made By TahaSezer
    void kullaniciKaydet() {
        string kullaniciAdi, sifre;
        cout << "Yeni kullanici adi: ";
        cin >> kullaniciAdi;
        cout << "Yeni sifre: ";
        cin >> sifre;

        kullanicilar.push_back(Kullanici(kullaniciAdi, sifre));
        cout << "Kullanici basariyla kaydedildi!" << endl;
    }
    // Made By TahaSezer
    void randevuOlustur() {
        string tarih, saat, musteriAdi;
        string hizmet;
        int hizmetSecim;
        bool onOdemeliMi;
        double fiyat = 0;
        cout << "Tarih (GG/AA/YYYY): ";
        cin >> tarih;
        cout << "Saat (SS:DD): ";
        cin >> saat;
        cout << "Musteri adi: ";
        cin.ignore();
        getline(cin, musteriAdi);

        // Hizmet secenekleri ve fiyatlandirma
        cout << "Hizmet seciniz:" << endl;
        cout << "1. Sac Kesimi (200 TL)" << endl;
        cout << "2. Sakal Kesimi (100 TL)" << endl;
        cout << "3. Sac ve Sakal Kesimi (300 TL)" << endl;
        cout << "4. Damat Trasi (500 TL)" << endl;
        cout << "Seciminiz: ";
        cin >> hizmetSecim;

        // Hizmet secimini kontrol et
        switch (hizmetSecim) {
            case 1:
                hizmet = "Sac Kesimi";
                fiyat = 200;
                break;
            case 2:
                hizmet = "Sakal Kesimi";
                fiyat = 100;
                break;
            case 3:
                hizmet = "Sac ve Sakal Kesimi";
                fiyat = 300;
                break;
            case 4:
                hizmet = "Damat Trasi";
                fiyat = 500;
                break;
            default:
                cout << "Gecersiz secim! Varsayilan olarak Sac Kesimi secildi." << endl;
                hizmet = "Sac Kesimi";
                fiyat = 200;
        }
        cout << "On odemeli mi? (1-Evet/0-Hayir): ";
        cin >> onOdemeliMi;

        randevular.push_back(Randevu(tarih, saat, musteriAdi, hizmet, onOdemeliMi, fiyat));
        cout << "Randevu basariyla olusturuldu!" << endl;
    }

    void randevulariListele() {
        if (randevular.empty()) {
            cout << "Hic randevu bulunmamaktadir." << endl;
            return;
        }
        cout << "\nRandevular:" << endl;
        cout << "-------------------------------" << endl;
        for (size_t i = 0; i < randevular.size(); i++) {
            cout << i + 1 << ". Randevu:" << endl;
            cout << "Tarih: " << randevular[i].getTarih() << endl;
            cout << "Saat: " << randevular[i].getSaat() << endl;
            cout << "Musteri: " << randevular[i].getMusteriAdi() << endl;
            cout << "Hizmet: " << randevular[i].getHizmet() << endl;
            cout << "Fiyat: " << randevular[i].getFiyat() << " TL" << endl;
            cout << "Odeme Durumu: " << (randevular[i].getOnOdemeliMi() ? "On Odemeli" : "Odemesiz") << endl;
            cout << "Durum: " << (randevular[i].getOnaylandiMi() ? "Onaylandi" : "Onay Bekliyor") << endl;
            cout << "-------------------------------" << endl;
        }
    }


    void adminMenu() {
        if (!mevcutKullanici || !mevcutKullanici->adminKullaniciMi()) {
            cout << "Bu islev icin admin yetkisi gereklidir!" << endl;
            return;
        }

        int secim;
        do {
            cout << "\nAdmin Menusu:" << endl;
            cout << "1. Randevulari Listele" << endl;
            cout << "2. Randevu Onayla" << endl;
            cout << "3. Mesajlari Goruntule" << endl;
            cout << "4. Cikis" << endl;
            cout << "Seciminiz: ";
            cin >> secim;

            switch (secim) {
                case 1:
                    randevulariListele();
                    break;
                case 2: {
                    randevulariListele();
                    int randevuNo;
                    cout << "Onaylamak istediginiz randevu numarasi: ";
                    cin >> randevuNo;

                    if (randevuNo > 0 && randevuNo <= static_cast<int>(randevular.size())) {
                        randevular[randevuNo - 1].setOnayla(true);
                        cout << "Randevu onaylandi!" << endl;
                    } else {
                        cout << "Gecersiz randevu numarasi!" << endl;
                    }
                    break;
                }
                case 3:
                    // Made By TahaSezer
                    // Admin mesajlarini goruntuleme
                    if (adminMesajlari.empty()) {
                        cout << "Hic mesaj bulunmamaktadir." << endl;
                    } else {
                        cout << "\nMesajlar:" << endl;
                        cout << "-------------------------------" << endl;
                        for (size_t i = 0; i < adminMesajlari.size(); i++) {
                            cout << i + 1 << ". Mesaj: " << adminMesajlari[i] << endl;
                            cout << "-------------------------------" << endl;
                        }
                    }
                    break;
                case 4:
                    cout << "Admin menusunden cikiliyor..." << endl;
                    break;
                default:
                    cout << "Gecersiz secim!" << endl;
            }
        } while (secim != 4);
    }

    void adminIleIletisim() {
        string mesaj;
        cout << "Admin'e mesajinizi yazin: ";
        cin.ignore();
        getline(cin, mesaj);

        // Mesaji kaydet
        adminMesajlari.push_back(mesaj);

        cout << "Mesajiniz admin'e iletildi. En kisa surede size geri donus yapilacaktir." << endl;
    }
};


int main() {
    BerberSistemi sistem;
    int secim;

    cout << "Berber Randevu Sistemine Hos Geldiniz!" << endl;
    cout << "Made By TahaSezer" << endl;

    do {
        cout << "\nAna Menu:" << endl;
        cout << "1. Giris Yap" << endl;
        cout << "2. Kayit Ol" << endl;
        cout << "3. Randevu Olustur" << endl;
        cout << "4. Randevulari Listele" << endl;
        cout << "5. Admin Menusu" << endl;
        cout << "6. Admin ile Iletisim" << endl;
        cout << "7. Cikis" << endl;
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                if (sistem.girisYap()) {
                    cout << "Giris basarili!" << endl;
                } else {
                    cout << "Giris basarisiz! Kullanici adi veya sifre hatali." << endl;
                }
                break;
            case 2:
                sistem.kullaniciKaydet();
                break;
            case 3:
                sistem.randevuOlustur();
                break;
            case 4:
                sistem.randevulariListele();
                break;
            case 5:
                sistem.adminMenu();
                break;
            case 6:
                sistem.adminIleIletisim();
                break;
            case 7:
                cout << "Programdan cikiliyor. Iyi gunler!" << endl;
                break;
            default:
                cout << "Gecersiz secim!" << endl;
        }
    } while (secim != 7);

    // Made By TahaSezer
    return 0;
}