#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define GECICI_DOSYA "temp.c"
#define MAKS_KOD_UZUNLUGU 2048

void program_olustur(const char* kod) {
    FILE *dosya = fopen(GECICI_DOSYA, "w");
    if (!dosya) {
        perror("Dosya olusturma basarisiz");
        exit(EXIT_FAILURE);
    }

    fprintf(dosya, "#include <stdio.h>\n\nint main() {\n");
    fprintf(dosya, "%s", kod);
    fprintf(dosya, "\nreturn 0;\n}\n");

    fclose(dosya);
}

void derle_ve_calistir() {
    pid_t pid = fork();

    if (pid == 0) {
        // Cocuk surec - derle ve calistir
        execlp("gcc", "gcc", GECICI_DOSYA, "-o", "temp_executable", NULL);
        perror("Derleme basarisiz");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL); // Derlemenin bitmesini bekle

        if (access("temp_executable", F_OK) == 0) {
            printf("\nCikti:\n");
            printf("--------------------\n");

            pid_t calistir_pid = fork();
            if (calistir_pid == 0) {
                execl("./temp_executable", "./temp_executable", NULL);
                perror("Calistirma basarisiz");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL); // Calistirmanin bitmesini bekle
            }

            remove("temp_executable");
        }
    }

    remove(GECICI_DOSYA);
    printf("--------------------\n");
}

int main() {
    char girdi[MAKS_KOD_UZUNLUGU];

    printf("Basit C REPL (Cikmak icin 'exit' yazin)\n");
    printf("C kodu yazin ve calistirmak icin Enter'a basin:\n");

    while (1) {
        printf("\n>>> ");
        fgets(girdi, MAKS_KOD_UZUNLUGU, stdin);

        // Yeni satiri kaldir
        girdi[strcspn(girdi, "\n")] = 0;

        if (strcmp(girdi, "exit") == 0) {
            break;
        }

        if (strlen(girdi) > 0) {
            program_olustur(girdi);
            derle_ve_calistir();
        }
    }

    return 0;
}
