#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

// Randevu sınıfı
class Appointment {
private:
    string date;
    string time;
    string customerName;
    string service;
    bool isPrepaid;
    double price;
    bool isConfirmed;

public:
    Appointment(string d, string t, string cn, string s, bool pp, double p) 
        : date(d), time(t), customerName(cn), service(s), isPrepaid(pp), price(p), isConfirmed(false) {}

    // Getter metodları
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getCustomerName() const { return customerName; }
    string getService() const { return service; }
    bool getIsPrepaid() const { return isPrepaid; }
    double getPrice() const { return price; }
    bool getIsConfirmed() const { return isConfirmed; }

    void setConfirmed(bool status) { isConfirmed = status; }
};

// Kullanıcı sınıfı
class User {
protected:
    string username;
    string password;
    bool isAdmin;

public:
    User(string u, string p, bool admin = false) 
        : username(u), password(p), isAdmin(admin) {}

    bool checkCredentials(string u, string p) {
        return username == u && password == p;
    }

    bool isAdminUser() const { return isAdmin; }
    string getUsername() const { return username; }
};

// Sistem sınıfı
class BarberSystem {
private:
    vector<User> users;
    vector<Appointment> appointments;
    User* currentUser;

public:
    BarberSystem() : currentUser(nullptr) {
        // Admin hesabı oluştur
        users.push_back(User("admin", "admin123", true));
    }

    bool login() {
        string username, password;
        cout << "\nKullanıcı Girişi" << endl;
        cout << "Kullanıcı adı: ";
        cin >> username;
        cout << "Şifre: ";
        cin >> password;

        for (auto& user : users) {
            if (user.checkCredentials(username, password)) {
                currentUser = &user;
                return true;
            }
        }
        return false;
    }

    void registerUser() {
        string username, password;
        cout << "\nYeni Kullanıcı Kaydı" << endl;
        cout << "Kullanıcı adı: ";
        cin >> username;
        cout << "Şifre: ";
        cin >> password;

        users.push_back(User(username, password));
        cout << "Kayıt başarılı!" << endl;
    }

    void makeAppointment() {
        if (!currentUser) {
            cout << "Lütfen önce giriş yapın!" << endl;
            return;
        }

        string date, time, service;
        double price;
        char paymentChoice;
        bool prepaid;

        cout << "\nRandevu Oluşturma" << endl;
        cout << "Tarih (GG/AA/YYYY): ";
        cin >> date;
        cout << "Saat (SS:DD): ";
        cin >> time;
        cout << "Hizmet türü: ";
        cin.ignore();
        getline(cin, service);
        cout << "Ücret: ";
        cin >> price;
        cout << "Ödeme şekli (P: Ön ödeme, N: Nakit): ";
        cin >> paymentChoice;

        prepaid = (paymentChoice == 'P' || paymentChoice == 'p');

        appointments.push_back(Appointment(date, time, currentUser->getUsername(), service, prepaid, price));
        cout << "Randevu başarıyla oluşturuldu!" << endl;
    }

    void listAppointments() {
        if (!currentUser) {
            cout << "Lütfen önce giriş yapın!" << endl;
            return;
        }

        cout << "\nRandevular:" << endl;
        cout << setw(15) << "Tarih" << setw(10) << "Saat" << setw(20) << "Müşteri" 
             << setw(20) << "Hizmet" << setw(15) << "Ücret" << setw(15) << "Ödeme Durumu" << endl;
        cout << string(95, '-') << endl;

        for (const auto& apt : appointments) {
            if (currentUser->isAdminUser() || apt.getCustomerName() == currentUser->getUsername()) {
                cout << setw(15) << apt.getDate() 
                     << setw(10) << apt.getTime()
                     << setw(20) << apt.getCustomerName()
                     << setw(20) << apt.getService()
                     << setw(15) << apt.getPrice()
                     << setw(15) << (apt.getIsPrepaid() ? "Ön Ödemeli" : "Nakit") << endl;
            }
        }
    }

    void adminMenu() {
        if (!currentUser || !currentUser->isAdminUser()) {
            cout << "Bu menüye erişim yetkiniz yok!" << endl;
            return;
        }

        int choice;
        do {
            cout << "\nAdmin Menüsü" << endl;
            cout << "1. Tüm Randevuları Listele" << endl;
            cout << "2. Randevu Onayla" << endl;
            cout << "3. Randevu İptal Et" << endl;
            cout << "4. Çıkış" << endl;
            cout << "Seçiminiz: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    listAppointments();
                    break;
                case 2:
                    // Randevu onaylama işlemleri
                    break;
                case 3:
                    // Randevu iptal işlemleri
                    break;
            }
        } while (choice != 4);
    }

    void contactAdmin() {
        if (!currentUser) {
            cout << "Lütfen önce giriş yapın!" << endl;
            return;
        }

        string message;
        cout << "\nAdmin ile İletişim" << endl;
        cout << "Mesajınız: ";
        cin.ignore();
        getline(cin, message);
        
        cout << "Mesajınız admin'e iletildi!" << endl;
    }
};

int main() {
    BarberSystem system;
    int choice;

    do {
        cout << "\nBerber Randevu Sistemi" << endl;
        cout << "1. Giriş Yap" << endl;
        cout << "2. Kayıt Ol" << endl;
        cout << "3. Randevu Al" << endl;
        cout << "4. Randevularımı Görüntüle" << endl;
        cout << "5. Admin ile İletişim" << endl;
        cout << "6. Admin Menüsü" << endl;
        cout << "7. Çıkış" << endl;
        cout << "Seçiminiz: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (system.login())
                    cout << "Giriş başarılı!" << endl;
                else
                    cout << "Hatalı kullanıcı adı veya şifre!" << endl;
                break;
            case 2:
                system.registerUser();
                break;
            case 3:
                system.makeAppointment();
                break;
            case 4:
                system.listAppointments();
                break;
            case 5:
                system.contactAdmin();
                break;
            case 6:
                system.adminMenu();
                break;
        }
    } while (choice != 7);

    return 0;
}
