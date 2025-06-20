#include <iostream>
using namespace std;

int main() {
    int musteri_sayisi;
    cout << "Kaç müşteri var? ";
    cin >> musteri_sayisi;

    for (int i = 1; i <= musteri_sayisi; i++) {
        int siparis_sayisi, toplam_adet = 0, toplam_tutar = 0;
        int pizza_sayisi = 0, burger_sayisi = 0, makarna_sayisi = 0;

        cout << i << ". müşterinin kaç sipariş verdiğini girin: ";
        cin >> siparis_sayisi;

        for (int j = 1; j <= siparis_sayisi; j++) {
            int yemek_kodu, adet;
            cout << j << ". sipariş için yemek kodunu (1: Pizza, 2: Burger, 3: Makarna) girin: ";
            cin >> yemek_kodu;
            cout << "Kaç adet? ";
            cin >> adet;
            if (yemek_kodu == 1) {
                toplam_tutar += adet * 50;
                pizza_sayisi += adet;
            } else if (yemek_kodu == 2) {
                toplam_tutar += adet * 40;
                burger_sayisi += adet;
            } else if (yemek_kodu == 3) {
                toplam_tutar += adet * 30;
                makarna_sayisi += adet;
            }else{
                cout << "Geçersiz Seçim";
            }
                    }
            if (siparis_sayisi > 10) {
                cout << "Sipariş limiti aşıldı, sipariş iptal edildi!\n";
                continue;
            }

            toplam_adet += adet;



        if (toplam_adet > 20) {
            cout << "Uyarı: Bu müşteri için sipariş limiti aşıldı!\n";
        }

        int en_cok_siparis = pizza_sayisi;
        string en_cok_yemek = "Pizza";

        if (burger_sayisi > en_cok_siparis) {
            en_cok_siparis = burger_sayisi;
            en_cok_yemek = "Burger";
        }

        if (makarna_sayisi > en_cok_siparis) {
            en_cok_siparis = makarna_sayisi;
            en_cok_yemek = "Makarna";
        }

        cout << "Müşteri " << i << " toplam sipariş tutarı: " << toplam_tutar << " TL\n";
        cout << "En çok sipariş edilen yemek: " << en_cok_yemek << endl;
    }

    return 0;
}
