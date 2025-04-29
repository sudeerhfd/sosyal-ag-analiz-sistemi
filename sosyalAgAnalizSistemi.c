#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAKS_KULLANICI 100
#define MAKS_ARKADAS 50
#define MAKS_SATIR_UZUNLUGU 50
#define MAKS_KULLANICI_ID 1000

// Kullanýcý yapýsý
typedef struct Kullanici {
    int kullanici_id;
    int arkadaslar[MAKS_ARKADAS];
    int arkadas_sayisi;
} Kullanici;

// Kýrmýzý-Siyah Aðaç Düðümü
typedef struct KSDugum {
    int kullanici_id;
    Kullanici* kullanici;
    struct KSDugum *sol, *sag;
} KSDugum;

// Global deðiþkenler
KSDugum* kok = NULL;
Kullanici* kullanicilar[MAKS_KULLANICI];
int kullanici_sayisi = 0;
bool ziyaret_edildi[MAKS_KULLANICI_ID] = {false};

// Yardýmcý fonksiyonlar
Kullanici* kullanici_olustur(int kullanici_id) {
    Kullanici* yeni = (Kullanici*)malloc(sizeof(Kullanici));
    yeni->kullanici_id = kullanici_id;
    yeni->arkadas_sayisi = 0;
    return yeni;
}

KSDugum* ks_dugum_olustur(int kullanici_id) {
    KSDugum* yeni = (KSDugum*)malloc(sizeof(KSDugum));
    yeni->kullanici_id = kullanici_id;
    yeni->kullanici = kullanici_olustur(kullanici_id);
    yeni->sol = yeni->sag = NULL;
    return yeni;
}

void ks_ekle(int kullanici_id) {
    if (kok == NULL) {
        kok = ks_dugum_olustur(kullanici_id);
        kullanicilar[kullanici_sayisi++] = kok->kullanici;
        return;
    }

    KSDugum* mevcut = kok;
    while (1) {
        if (kullanici_id < mevcut->kullanici_id) {
            if (mevcut->sol == NULL) {
                mevcut->sol = ks_dugum_olustur(kullanici_id);
                kullanicilar[kullanici_sayisi++] = mevcut->sol->kullanici;
                break;
            }
            mevcut = mevcut->sol;
        } else if (kullanici_id > mevcut->kullanici_id) {
            if (mevcut->sag == NULL) {
                mevcut->sag = ks_dugum_olustur(kullanici_id);
                kullanicilar[kullanici_sayisi++] = mevcut->sag->kullanici;
                break;
            }
            mevcut = mevcut->sag;
        } else {
            break; // Zaten var
        }
    }
}

KSDugum* ks_ara(int kullanici_id) {
    KSDugum* mevcut = kok;
    while (mevcut != NULL) {
        if (kullanici_id < mevcut->kullanici_id) {
            mevcut = mevcut->sol;
        } else if (kullanici_id > mevcut->kullanici_id) {
            mevcut = mevcut->sag;
        } else {
            return mevcut;
        }
    }
    return NULL;
}

void arkadas_ekle(int id1, int id2) {
    KSDugum* dugum1 = ks_ara(id1);
    KSDugum* dugum2 = ks_ara(id2);
    
    if (dugum1 && dugum2) {
        Kullanici* k1 = dugum1->kullanici;
        Kullanici* k2 = dugum2->kullanici;
        
        k1->arkadaslar[k1->arkadas_sayisi++] = id2;
        k2->arkadaslar[k2->arkadas_sayisi++] = id1;
    }
}

void dosyadan_oku(const char* dosya_adi) {
    FILE* dosya = fopen(dosya_adi, "r");
    if (!dosya) {
        printf("Dosya acilamadi: %s\n", dosya_adi);
        exit(1);
    }

    char satir[MAKS_SATIR_UZUNLUGU];
    bool kullanicilar_bolumu = false;
    bool arkadasliklar_bolumu = false;

    while (fgets(satir, sizeof(satir), dosya)) {
        satir[strcspn(satir, "\n")] = '\0'; // Satýr sonu karakterini kaldýr

        if (strcmp(satir, "USERS") == 0) {
            kullanicilar_bolumu = true;
            arkadasliklar_bolumu = false;
            continue;
        } else if (strcmp(satir, "FRIENDS") == 0) {
            kullanicilar_bolumu = false;
            arkadasliklar_bolumu = true;
            continue;
        }

        if (kullanicilar_bolumu) {
            int id = atoi(satir);
            if (id > 0) ks_ekle(id);
        } else if (arkadasliklar_bolumu) {
            int id1, id2;
            if (sscanf(satir, "%d %d", &id1, &id2) == 2) {
                arkadas_ekle(id1, id2);
            }
        }
    }
    fclose(dosya);
}

void kullanicilari_listele() {
    printf("\nKullanici Bilgileri:\n");
    printf("--------------------\n");
    for (int i = 0; i < kullanici_sayisi; i++) {
        printf("Kullanici %d: ", kullanicilar[i]->kullanici_id);
        for (int j = 0; j < kullanicilar[i]->arkadas_sayisi; j++) {
            printf("%d", kullanicilar[i]->arkadaslar[j]);
            if (j < kullanicilar[i]->arkadas_sayisi - 1) printf(", ");
        }
        printf("\n");
    }
}

void belirli_mesafedeki_arkadaslar(int baslangic_id, int mesafe) {
    memset(ziyaret_edildi, 0, sizeof(ziyaret_edildi));
    printf("\n%d kullanicisinin %d uzakliktaki arkadaslari: ", baslangic_id, mesafe);
    
    // Basit BFS uygulamasý
    int mevcut_mesafe = 0;
    int kuyruk[MAKS_KULLANICI];
    int bas = 0, son = 0;
    
    ziyaret_edildi[baslangic_id] = true;
    kuyruk[son++] = baslangic_id;
    
    while (bas < son && mevcut_mesafe <= mesafe) {
        int seviye_buyuklugu = son - bas;
        for (int i = 0; i < seviye_buyuklugu; i++) {
            int mevcut_id = kuyruk[bas++];
            KSDugum* dugum = ks_ara(mevcut_id);
            
            if (mevcut_mesafe == mesafe && mevcut_id != baslangic_id) {
                printf("%d ", mevcut_id);
            }
            
            if (dugum) {
                for (int j = 0; j < dugum->kullanici->arkadas_sayisi; j++) {
                    int arkadas_id = dugum->kullanici->arkadaslar[j];
                    if (!ziyaret_edildi[arkadas_id]) {
                        ziyaret_edildi[arkadas_id] = true;
                        kuyruk[son++] = arkadas_id;
                    }
                }
            }
        }
        mevcut_mesafe++;
    }
    printf("\n");
}

void ortak_arkadaslar(int id1, int id2) {
    KSDugum* dugum1 = ks_ara(id1);
    KSDugum* dugum2 = ks_ara(id2);
    
    if (!dugum1 || !dugum2) {
        printf("Kullanici bulunamadi!\n");
        return;
    }
    
    printf("\n%d ve %d kullanicilarinin ortak arkadaslari: ", id1, id2);
    
    for (int i = 0; i < dugum1->kullanici->arkadas_sayisi; i++) {
        for (int j = 0; j < dugum2->kullanici->arkadas_sayisi; j++) {
            if (dugum1->kullanici->arkadaslar[i] == dugum2->kullanici->arkadaslar[j]) {
                printf("%d ", dugum1->kullanici->arkadaslar[i]);
                break;
            }
        }
    }
    printf("\n");
}

void temizle() {
    // Basitçe tüm düðümleri temizle
    for (int i = 0; i < kullanici_sayisi; i++) {
        free(kullanicilar[i]);
    }
    kok = NULL;
    kullanici_sayisi = 0;
}

int main() {
    // Dosyadan verileri oku
    dosyadan_oku("C:\\Users\\sude\\Desktop\\veriseti.txt");
    
    // Kullanýcý bilgilerini listele
    kullanicilari_listele();
    
    // Analizleri yap
    belirli_mesafedeki_arkadaslar(101, 2);
    ortak_arkadaslar(101, 104);
    
    // Belleði temizle
    temizle();
    
    return 0;
}
