#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kitap yapısı
typedef struct {
    int id;
    char title[100];
    char author[100];
} Book;

// Fonksiyon prototipleri
void addBook();
void listBooks();
void searchBook();
void deleteBook();
void saveBooks();
void loadBooks();

#define MAX_BOOKS 10000
Book library[MAX_BOOKS];
int bookCount = 0;

int main() {
    int choice;

    loadBooks(); // Program başlarken kitapları yükle

    do {
        printf("\nKütüphane Yönetim Sistemi\n");
        printf("1. Kitap Ekle\n");
        printf("2. Kitapları Listele\n");
        printf("3. Kitap Ara\n");
        printf("4. Kitap Sil\n");
        printf("5. Çıkış\n");
        printf("Seçiminizi yapın: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                listBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                saveBooks(); // Çıkmadan önce kitapları kaydet
                printf("Çıkılıyor...\n");
                break;
            default:
                printf("Geçersiz seçim! Lütfen tekrar deneyin.\n");
        }
    } while (choice != 5);

    return 0;
}

// Kitap ekleme fonksiyonu
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Kütüphane dolu! Daha fazla kitap eklenemez.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1; // Kitap ID'si
    printf("Kitap Başlığını Girin: ");
    getchar(); // Önceki scanf'den kalan yeni satırı temizle
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Yeni satırı kaldır
    printf("Yazar Adını Girin: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Yeni satırı kaldır

    library[bookCount] = newBook;
    bookCount++;
    printf("Kitap başarıyla eklendi!\n");
}

// Kitapları listeleme fonksiyonu
void listBooks() {
    if (bookCount == 0) {
        printf("Kütüphanede hiç kitap yok.\n");
        return;
    }

    printf("\nKütüphanedeki Kitaplar:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Başlık: %s, Yazar: %s\n", library[i].id, library[i].title, library[i].author);
    }
}

// Kitap arama fonksiyonu
void searchBook() {
    char title[100];
    printf("Aramak istediğiniz kitabın başlığını girin: ");
    getchar(); // Önceki scanf'den kalan yeni satırı temizle
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0; // Yeni satırı kaldır

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, title) == 0) {
            printf("Kitap Bulundu! ID: %d, Başlık: %s, Yazar: %s\n", library[i].id, library[i].title, library[i].author);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Kitap bulunamadı.\n");
    }
}

// Kitap silme fonksiyonu
void deleteBook() {
    int id;
    printf("Silmek istediğiniz kitabın ID'sini girin: ");
    scanf("%d", &id);

    if (id < 1 || id > bookCount) {
               printf("Geçersiz ID! Silme işlemi gerçekleştirilemedi.\n");
        return;
    }

    // Kitabı silme işlemi
    for (int i = id - 1; i < bookCount - 1; i++) {
        library[i] = library[i + 1]; // Kitapları kaydır
    }
    bookCount--; // Kitap sayısını azalt
    printf("Kitap başarıyla silindi!\n");
}

// Kitapları dosyaya kaydetme fonksiyonu
void saveBooks() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Dosya açılamadı! Kitaplar kaydedilemedi.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d\n%s\n%s\n", library[i].id, library[i].title, library[i].author);
    }
    fclose(file);
    printf("Kitaplar başarıyla kaydedildi!\n");
}

// Kitapları dosyadan yükleme fonksiyonu
void loadBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Dosya açılamadı! Kütüphane boş.\n");
        return;
    }

    while (fscanf(file, "%d\n%[^\n]\n%[^\n]\n", &library[bookCount].id, library[bookCount].title, library[bookCount].author) != EOF) {
        bookCount++;
    }
    fclose(file);
    printf("Kitaplar başarıyla yüklendi!\n");
}