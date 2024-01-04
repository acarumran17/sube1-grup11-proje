// Kutuphaneler

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fonksiyon.h"
// Global değiskenler
FILE *kiralama;int sayac;FILE *dosya;

// Arac struct

struct arac {
    char arac_adi[10];
    int arac_uygunluk;
    float arac_motor;
    int arac_beygir;
    int arac_yili;
    char arac_model[10];

};
struct arac arabalar[5];

// Baslik fonksiyonu
void rent_a_car(){
    printf("  _____            _              _____           \n"
           " |  __ \\          | |            / ____|          \n"
           " | |_) |__ _ __ | |_    __ _  | |     __ _ _ __ \n"
           " |  _  // _ \\ '_ \\| __|  / _` | | |    / _` | '__|\n"
           " | | \\ \\  _/ | | | |  | (_| | | |___| (_| | |   \n"
           " |_|  \\_\\___|_| |_|\\__|  \\__,_|  \\_____\\__,_|_|   \n"
           "                                                  ");
}
// Bosluk birakmak icin fonksiyon.
void clear(){
    for (int i = 0; i < 30; ++i) {
        printf("\n");
    }
}
// Ana menu
void ana_menu() {
    clear();
    rent_a_car();
    printf("\nArac Kiralama Sistemi\n\n");
    printf("1. Arac Listesi\n2. Arac Kiralama\n3. Arac Iade\n4. Kiralama/Iade Gecmisi\n\n0. Cikis\n\n");
    printf("Seciminiz: ");
    int input;
    scanf("%d", &input);
    printf("\n\n");
    switch (input) {

        case 1: {
            clear();
            arac_listesi();
            break;
        }

        case 2: {
            clear();
            arac_kiralama();
            break;
        }
        case 3: {
            clear();
            arac_iade();
            break;
        }
        case 4: {
            clear();
            rent_a_car();
            printf("\n\nKIRALAMA/IADE GECMISI: \n\n");
            kiralama = fopen("kiralamagecmis.txt", "r");

            if (kiralama == NULL) {
                printf("Gecmis bulunamadi.\n");
                fflush(stdout);
                sleep(1);
                clear();
                fclose(kiralama);
                ana_menu();
            } else {
                kiralama_gecmisi();
                int secim;
                printf("\n0- Ana Menu\n9- Gecmisi temizle\n\nSeciminiz:");
                scanf("%d", &secim);

                if (secim == 0) {
                    fclose(kiralama);
                    ana_menu();
                    return;
                } else if (secim == 9) {
                    if (remove("kiralamagecmis.txt") == 0) {
                        printf("Gecmis temizlendi.\n");
                        fflush(stdout);
                        sleep(1);
                        fclose(kiralama);
                        ana_menu();
                        return;
                    } else {
                        perror("Dosya silinemedi");
                        fflush(stdout);
                        sleep(1);
                        fclose(kiralama);
                        ana_menu();
                        return;
                    }
                } else {
                    printf("Gecersiz secim.\n");
                    fclose(kiralama);
                    ana_menu();
                    return;
                }
            }
        }


        case 0: {
            exit(0); // Programdan cikis yap.
        }
        default:
            printf("Gecersiz secim\n");
            sleep(1);
            ana_menu();

    }

}
// Arac listesini göster.

void arac_listesi(){
    rent_a_car();
    int secim;
    char veri[100];sayac=1;
    // Dosyayi okuma modunda acip satir satir bilgileri al.
    dosya = fopen("araclist.txt","r");
    printf("  \n\n  ARAC BILGILERI:    Marka   \tModel\t   Yil     Motor    Beygir    Uygunluk\n\n");
    while (fgets(veri, sizeof(veri), dosya) != NULL) {
        printf("%d. aracin bilgileri: %s", sayac, veri);
        sayac++;
    }
    fclose(dosya);
    printf("\n\n0- Ana Menu\n\nSeciminiz:");
    scanf("%d", &secim);
    while(secim!=0){
        printf("\nGecersiz secim\nSeciminiz:");
        scanf("%d", &secim);
    }
    ana_menu();
}

// Araba kiralama fonksiyonu
void arac_kiralama() {
    rent_a_car();
    char arac_adlari[30];
    char arac_modeli[30];
    int input;
    int kiralanma_kontrol = 1;
    sayac = 1;
    printf("\n\nLutfen kiralamak istediginiz araci seciniz.\n\n");

    // Arac adlarini listele
    dosya = fopen("araclist.txt", "r");
    while (fscanf(dosya, "%s %s %*f %*f %*f %*f", arac_adlari, arac_modeli) != EOF) {
        printf("%d- %s %s\n", sayac, arac_adlari, arac_modeli);
        sayac++;
    }
    fclose(dosya);

    printf("\n0- Ana Menu\n\nSeciminiz:");
    scanf("%d", &input);
    if (input == 0) {
        ana_menu();
    }

    dosya = fopen("araclist.txt", "r");
    FILE *gecici = fopen("gecici.txt", "w");

    for (int i = 0; i < sayac - 1; ++i) {
        fscanf(dosya, "%s %s %d %f %d %d", arabalar[i].arac_adi, arabalar[i].arac_model, &arabalar[i].arac_yili,
               &arabalar[i].arac_motor, &arabalar[i].arac_beygir, &arabalar[i].arac_uygunluk);

        if (i == input - 1) {
            if (arabalar[i].arac_uygunluk == 0) {
                printf("Arac zaten kiralanmis veya gecersiz secim\n");
                kiralanma_kontrol = 0;
                fflush(stdout);
                sleep(1);
                ana_menu();
            } else {
                arabalar[i].arac_uygunluk = 0;
            }
        }

        fprintf(gecici, "%s\t%s\t   %d\t    %.2f     %d\t %d\n", arabalar[i].arac_adi, arabalar[i].arac_model, arabalar[i].arac_yili,
                arabalar[i].arac_motor, arabalar[i].arac_beygir, arabalar[i].arac_uygunluk);
    }

    fclose(gecici);
    fclose(dosya);
    remove("araclist.txt");
    rename("gecici.txt", "araclist.txt");

    // Kiralama gecmisini bir dosyaya kaydet.
    if (kiralanma_kontrol != 0) {
        printf("Kiralama islemi basarili. Ana menuye yonlendiriliyorsunuz...\n");
        kiralama = fopen("kiralamagecmis.txt", "a");
        fprintf(kiralama, "%s markali arac KIRALANDI\n", arabalar[input - 1].arac_adi);
        fclose(kiralama);
        fflush(stdout);
        sleep(2);
    }
    ana_menu();
}

void arac_iade() {
    rent_a_car();
    char arac_adlari[20];
    char arac_modeli[30];
    int input;
    sayac = 1;
    int kiralanma_kontrol = 1;

    printf("\n\nLutfen iade etmek istediginiz araci seciniz.\n\n");

    dosya = fopen("araclist.txt", "r");
    FILE *gecici2 = fopen("gecici2.txt", "w");

    while (fscanf(dosya, "%s %s %*f %*f %*f %*f", arac_adlari, arac_modeli) != EOF) {
        printf("%d- %s %s\n", sayac, arac_adlari, arac_modeli);
        sayac++;
    }
    fclose(dosya);

    printf("\n0- Ana Menu\n\nSeciminiz:");
    scanf("%d", &input);
    if (input == 0) {
        ana_menu();
    }

    dosya = fopen("araclist.txt", "r");
    if(input<6&&input>0){
        for (int i = 0; i < sayac - 1; ++i) {
            fscanf(dosya, "%s %s %d %f %d %d", arabalar[i].arac_adi, arabalar[i].arac_model, &arabalar[i].arac_yili,
                   &arabalar[i].arac_motor, &arabalar[i].arac_beygir, &arabalar[i].arac_uygunluk);

            if (i == input - 1) {
                if (arabalar[i].arac_uygunluk == 1) {
                    printf("Arac zaten kiralanmamis.\n");
                    kiralanma_kontrol = 0;
                    fflush(stdout);
                    sleep(1);
                    break;
                } else {
                    arabalar[i].arac_uygunluk = 1; // Uygunluk durumunu guncelle
                }
            }

            fprintf(gecici2, "%s\t%s\t   %d\t    %.2f     %d\t %d\n", arabalar[i].arac_adi, arabalar[i].arac_model, arabalar[i].arac_yili,
                    arabalar[i].arac_motor, arabalar[i].arac_beygir, arabalar[i].arac_uygunluk);
        }

        fclose(gecici2);
        fclose(dosya);

        if (kiralanma_kontrol == 1) {
            remove("araclist.txt");
            rename("gecici2.txt", "araclist.txt");

            printf("Iade islemi basarili. Ana menuye yonlendiriliyorsunuz...");
            kiralama = fopen("kiralamagecmis.txt", "a");
            fprintf(kiralama, "%s markali arac IADE EDILDI\n", arabalar[input - 1].arac_adi);
            fclose(kiralama);
            fflush(stdout);
            sleep(2);
        }
    } else {
        while (input != 0) {
            printf("\nGecersiz secim.\nSeciminiz:");
            scanf("%d", &input);
        }
    }

    ana_menu();
}

// Kiralama gecmisini ekrana yazdir.
void kiralama_gecmisi(){
    char satir[550];
    kiralama = fopen("kiralamagecmis.txt","r");
    while (fgets(satir, sizeof(satir),kiralama) != NULL){
        printf("%s",satir);
    }
    fclose(kiralama);

}
