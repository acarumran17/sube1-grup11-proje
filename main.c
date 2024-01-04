// Kütüphaneler
#include <stdio.h>
#include "fonksiyon.h"
// Main fonksiyonu
int main() {
    // Dosya yok ise veya var ama içi boş ise yeni dosya açarak bilgileri yaz
    FILE *dosya = fopen("araclist.txt", "r+");
    // Dosya yok ise
    if (dosya == NULL) {
        dosya = fopen("araclist.txt", "w");
        if (dosya != NULL) {
            fprintf(dosya,"Toyota\tCorolla\t   2011\t    1.60     124\t 1\n"
                          "Ford\tFocus\t   2001\t    2.00     130\t 1\n"
                          "Bmw\t5.30\t   2021\t    2.00     248\t 1\n"
                          "Opel\tAstra\t   1997\t    1.60     156\t 1\n"
                          "Chevy\tImpala\t   1967\t    4.60     195\t 1");
            fclose(dosya);
        }
        // Dosya var ancak içi boş ise
    } else {
        fseek(dosya, 0, SEEK_END);
        if (ftell(dosya) <= 1) {
            fseek(dosya, 0, SEEK_SET);
            fprintf(dosya,"Toyota\tCorolla\t   2011\t    1.60     124\t 1\n"
                          "Ford\tFocus\t   2001\t    2.00     130\t 1\n"
                          "Bmw\t5.30\t   2021\t    2.00     248\t 1\n"
                          "Opel\tAstra\t   1997\t    1.60     156\t 1\n"
                          "Chevy\tImpala\t   1967\t    4.60     195\t 1");
        }
        fclose(dosya);
    }
    ana_menu();
}
