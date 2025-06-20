#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

class BerberSistemi {
private:
    vector<Kullanici> kullanicilar;
    vector<Randevu> randevular;
    Kullanici* mevcutKullanici;

public:
    BerberSistemi() : mevcutKullanici(nullptr) {
        // Admin hesabını ekle: kullanıcı adı "Taha", şifre "Aett5734"
        kullanicilar.push_back(Kullanici("Taha", "Aett5734", true));
    }

    bool girisYap() {
        string kullaniciAdi, sifre;
        cout << "Kullanıcı adı: ";
        cin >> kullaniciAdi;
        cout << "Şifre: ";
        cin >> sifre;

        for (auto& kullanici : kullanicilar) {
            if (kullanici.kimlikDogrula(kullaniciAdi, sifre)) {
                mevcutKullanici = &kullanici;
                return true;
            }
        }
        return false;
    }

    void kullaniciKaydet() {
        string kullaniciAdi, sifre;
        cout << "Yeni kullanıcı adı: ";
        cin >> kullaniciAdi;
        cout << "Yeni şifre: ";
        cin >> sifre;

        kullanicilar.push_back(Kullanici(kullaniciAdi, sifre));
        cout << "Kullanıcı başarıyla kaydedildi!" << endl;
    }

    void randevuOlustur() {
        string tarih, saat, musteriAdi, hizmet;
        bool onOdemeliMi;
        double fiyat;

        cout << "Tarih (GG/AA/YYYY): ";
        cin >> tarih;
        cout << "Saat (SS:DD): ";
        cin >> saat;
        cout << "Müşteri adı: ";
        cin.ignore();
        getline(cin, musteriAdi);
        cout << "Hizmet: ";
        getline(cin, hizmet);
        cout << "Ön ödemeli mi? (1-Evet/0-Hayır): ";
        cin >> onOdemeliMi;
        cout << "Fiyat: ";
        cin >> fiyat;

        randevular.push_back(Randevu(tarih, saat, musteriAdi, hizmet, onOdemeliMi, fiyat));
        cout << "Randevu başarıyla oluşturuldu!" << endl;
    }

    void randevulariListele() {
        if (randevular.empty()) {
            cout << "Hiç randevu bulunmamaktadır." << endl;
            return;
        }

        cout << "\nRandevular:" << endl;
        cout << "-------------------------------" << endl;
        for (size_t i = 0; i < randevular.size(); i++) {
            cout << i + 1 << ". Randevu:" << endl;
            cout << "Tarih: " << randevular[i].getTarih() << endl;
            cout << "Saat: " << randevular[i].getSaat() << endl;
            cout << "Müşteri: " << randevular[i].getMusteriAdi() << endl;
            cout << "Hizmet: " << randevular[i].getHizmet() << endl;
            cout << "Fiyat: " << randevular[i].getFiyat() << " TL" << endl;
            cout << "Ödeme Durumu: " << (randevular[i].getOnOdemeliMi() ? "Ön Ödemeli" : "Ödemesiz") << endl;
            cout << "Durum: " << (randevular[i].getOnaylandiMi() ? "Onaylandı" : "Onay Bekliyor") << endl;
            cout << "-------------------------------" << endl;
        }
    }

    void adminMenu() {
        if (!mevcutKullanici || !mevcutKullanici->adminKullaniciMi()) {
            cout << "Bu işlev için admin yetkisi gereklidir!" << endl;
            return;
        }

        int secim;
        do {
            cout << "\nAdmin Menüsü:" << endl;
            cout << "1. Randevuları Listele" << endl;
            cout << "2. Randevu Onayla" << endl;
            cout << "3. Çıkış" << endl;
            cout << "Seçiminiz: ";
            cin >> secim;

            switch (secim) {
                case 1:
                    randevulariListele();
                    break;
                case 2: {
                    randevulariListele();
                    int randevuNo;
                    cout << "Onaylamak istediğiniz randevu numarası: ";
                    cin >> randevuNo;
                    
                    if (randevuNo > 0 && randevuNo <= static_cast<int>(randevular.size())) {
                        randevular[randevuNo - 1].setOnayla(true);
                        cout << "Randevu onaylandı!" << endl;
                    } else {
                        cout << "Geçersiz randevu numarası!" << endl;
                    }
                    break;
                }
                case 3:
                    cout << "Admin menüsünden çıkılıyor..." << endl;
                    break;
                default:
                    cout << "Geçersiz seçim!" << endl;
            }
        } while (secim != 3);
    }

    void adminIleIletisim() {
        string mesaj;
        cout << "Admin'e mesajınızı yazın: ";
        cin.ignore();
        getline(cin, mesaj);
        cout << "Mesajınız admin'e iletildi. En kısa sürede size geri dönüş yapılacaktır." << endl;
    }
};

int main() {
    BerberSistemi sistem;
    int secim;

    cout << "Berber Randevu Sistemine Hoş Geldiniz!" << endl;

    do {
        cout << "\nAna Menü:" << endl;
        cout << "1. Giriş Yap" << endl;
        cout << "2. Kayıt Ol" << endl;
        cout << "3. Randevu Oluştur" << endl;
        cout << "4. Randevuları Listele" << endl;
        cout << "5. Admin Menüsü" << endl;
        cout << "6. Admin ile İletişim" << endl;
        cout << "7. Çıkış" << endl;
        cout << "Seçiminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                if (sistem.girisYap()) {
                    cout << "Giriş başarılı!" << endl;
                } else {
                    cout << "Giriş başarısız! Kullanıcı adı veya şifre hatalı." << endl;
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
                cout << "Programdan çıkılıyor. İyi günler!" << endl;
                break;
            default:
                cout << "Geçersiz seçim!" << endl;
        }
    } while (secim != 7);

    return 0;
}