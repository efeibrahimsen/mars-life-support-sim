#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    srand(time(NULL));
    
    char zorluk;
    int enerji = 0;
    int oksijen = 0;
    int modulhasari = 0;
    int kilitmuhurlu = 0;
    int saglik = 0;
    int firtinasuresi = 0;
    int yedekparca = 0;
    int su = 0;
    int puan = 0;
    
    do {
        printf("Zorluk secin(K:kolay,N:normal,Z:zor):");
        zorluk = getchar();
        while (getchar() != '\n');
        
        switch(zorluk) {
            case 'k':
            case 'K':
                firtinasuresi = 3;
                yedekparca = 7;
                su = 100;
                enerji = 100;
                saglik = 100;
                oksijen = 100;
                modulhasari = 0;
                printf("\n -> Kolay zorluk secildi <-\n");
                break;
                
            case 'n':
            case 'N':
                firtinasuresi = 5;
                yedekparca = 5;
                su = 70;
                enerji = 80;
                saglik = 85;
                oksijen = 90;
                modulhasari = 20;
                printf("\n -> Normal zorluk secildi <-\n");
                break;
                
            case 'z':
            case 'Z':
                firtinasuresi = 7;
                yedekparca = 3;
                su = 50;
                enerji = 60;
                saglik = 70;
                oksijen = 75;
                modulhasari = 40;
                printf("\n -> Zor zorluk secildi <-\n");
                break;
                
            default:
                printf("\n -> Gecerli bir zorluk seciniz! <- \n\n");
                break;
        }
    } while (firtinasuresi == 0);
    
    char komut;
    int tur = 1;
    int gun = 1;

    while (gun <= 15 && saglik > 0 && oksijen > 0) {
        
        gun = ((tur - 1) / 3) + 1;
        
        if (gun > 15) break;
        
        printf("\n<<< GUN %d | TUR %d >>>\n", gun, tur);
        printf("Komut girin (G:kesif,O:oksijen uret,T:tamir,D:durum raporu,U:uyu,K:kum firtinasi,H:hava kilidi sifresi,Q:cikis) :");
        komut = getchar();
        while (getchar() != '\n');
        
        int turgecerli = 0;

        switch (komut) {
            case 'g':
            case 'G': {
                printf("kesfe cikiliyor.\n");
                if (enerji < 15 && oksijen < 10) {
                    printf("enerji ve oksijen yetersiz!\nLUTFEN UYUYUN ve OKSIJEN URETIN!\n");
                    printf("mevcut enerji: %d | mevcut oksijen: %d\n", enerji, oksijen);
                    break;
                }
                else if (enerji < 15) {
                    printf("Yetersiz enerji! LUTFEN UYUYUN!\nmevcut enerji: %d\n", enerji);
                    break;
                }
                else if (oksijen < 10) {
                    printf("Yetersiz oksijen! LUTFEN OKSIJEN URETIN!\nmevcut oksijen: %d\n", oksijen);
                    break;
                }
                
                enerji -= 15;
                oksijen -= 10;
                int zar = rand() % 100;
                
                if (zar < 10 || modulhasari > 70) {
                    printf("Kesifte kaza gecirildi! Hasar alindi (-10 Saglik).\n");
                    saglik -= 10;
                    if (saglik < 0) saglik = 0;
                }
                
                int esik = (enerji > 40 && oksijen > 30) ? 30 : 45;
                if (zar > esik) {
                    int hangi = rand() % 100;
                    if (hangi > 50) {
                        printf("kesif tamamlandi! (zar: %d / esik: %d) Su bulundu (+10 Su)!\n", zar, esik);
                        su += 10;
                        if (su > 100) su = 100;
                    } else {
                        printf("kesif tamamlandi! (zar: %d / esik: %d) Yedek parca bulundu (+1 Parca)!\n", zar, esik);
                        yedekparca += 1;
                    }
                } else {
                    printf("Hicbir sey bulunamadi (zar: %d / esik: %d).\n", zar, esik);
                }
                
                turgecerli = 1;
                break;
            }
                
            case 'o':
            case 'O': {
                if (enerji < 10) {
                    printf("hata: Oksijen uretimi icin en az 10 enerji gerekli! (Mevcut: %d)\n", enerji);
                    break;
                }
                
                int girilensu;
                printf("harcanacak su miktarini giriniz: ");
                
                if (scanf("%d", &girilensu) != 1) {
                    printf("Hata: gecerli bir sayisal deger giriniz!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                
                if (girilensu <= 0) {
                    printf("Hata: pozitif bir deger girilmelidir!\n");
                    break;
                }
                
                if (girilensu > su) {
                    printf("Hata: yetersiz su! mevcut su %d\n", su);
                    break;
                }

                int artansu = girilensu % 2;
                int kullanilansu = girilensu - artansu;
                int uretilenoksijen = (kullanilansu / 2) * 3;
                
                if (oksijen + uretilenoksijen > 100) {
                    printf("hata: oksijen deposunda yer yok. Kapasite 100'dur \n(Mevcut: %d, Uretilmek istenen: %d)\n", oksijen, uretilenoksijen);
                    break;
                }
                    
                su -= kullanilansu;
                oksijen += uretilenoksijen;
                enerji -= 10;
                
                printf(">>>> ISLEM BASARILI <<<<\n");
                printf("Kullanilan Su: %d | Harcanan Enerji: 10\n", kullanilansu);
                printf("Uretilen Oksijen: %d\n", uretilenoksijen);
                printf("Mevcut Su: %d | Mevcut Oksijen: %d | Mevcut Enerji: %d\n", su, oksijen, enerji);
                printf(">>>>-------------<<<<\n");
                
                turgecerli = 1;
                break;
            }
                
            case 't':
            case 'T': {
                if (yedekparca <= 0) {
                    printf("Hata: tamir icin yeterli yedek parca yok! (Mevcut: %d)\n", yedekparca);
                    break;
                }
                if (modulhasari <= 0) {
                    printf("Modul zaten saglam! Tamir yapilmadi.\n");
                    break;
                }
                if (modulhasari <= 30) {
                    yedekparca -= 1;
                    modulhasari -= 15;
                    printf("Hafif hasar tamir edildi \n(-1 Yedek Parca, -15 Hasar).\n");
                }
                else if (modulhasari <= 70) {
                    if (yedekparca < 2) {
                        printf("Hata: Orta derece hasari tamir etmek icin en az 2 yedek parca gerekli!\n");
                        break;
                    }
                    yedekparca -= 2;
                    modulhasari -= 30;
                    printf("Orta derece hasar tamir edildi \n(-2 Yedek Parca, -30 Hasar).\n");
                }
                else {
                    if (yedekparca < 3) {
                        printf("Hata: Agir hasari tamir etmek icin en az 3 yedek parca gerekli!\n");
                        break;
                    }
                    yedekparca -= 3;
                    modulhasari -= 50;
                    printf("Agir hasar tamir edildi \n(-3 Yedek Parca, -50 Hasar).\n");
                }
                if (modulhasari < 0) modulhasari = 0;
                
                printf("Kalan Yedek Parca: %d | Guncel Modul Hasari: %d\n", yedekparca, modulhasari);
                turgecerli = 1;
                break;
            }
                
            case 'd':
            case 'D':
                printf("\n<<< Durum Raporu >>>\n");
                printf("Saglik       : %d\n", saglik);
                printf("Oksijen      : %d\n", oksijen);
                printf("Enerji       : %d\n", enerji);
                printf("Su           : %d\n", su);
                printf("Yedek Parca  : %d\n", yedekparca);
                printf("Modul Hasari : %d\n", modulhasari);
                printf("Kilit Muhuru : %s\n", kilitmuhurlu ? "Muhurlu" : "Acik");
                printf("-------------------\n");
                if (saglik >= 30 && oksijen >= 25 && enerji >= 15 && su >= 10 && modulhasari <= 70) {
                    printf("TUM SISTEMLER NORMAL.\n");
                }
                else {
                    printf("!!UYARI!! / KRITIK DURUM:\n");
                    if (saglik < 30) printf(" - KRITIK SAGLIK! (Mevcut: %d)\n", saglik);
                    if (oksijen < 25) printf(" - DUSUK OKSIJEN! (Mevcut: %d)\n", oksijen);
                    if (enerji < 15) printf(" - DUSUK ENERJI! (Mevcut: %d)\n", enerji);
                    if (su < 10) printf(" - KRITIK SU SEVIYESI! (Mevcut: %d)\n", su);
                    if (modulhasari > 70) printf(" - YUKSEK MODUL HASARI! (Mevcut: %d)\n", modulhasari);
                }
                printf("-------------------------------\n");
                turgecerli = 0;
                break;
            
            case 'u':
            case 'U':
                printf("Tur boyunca dinleniliyor... >>> ZzZzZ <<<\n");
                enerji += 15;
                if (enerji > 100) enerji = 100;
                
                if (oksijen < 20) {
                    printf("DUSUK OKSIJEN! Oksijen yetersiz oldugundan saglik kaybedildi (-10 Saglik).\n");
                    saglik -= 10;
                    if (saglik < 0) saglik = 0;
                } else {
                    printf("IDEAL OKSIJEN! Dinlenme ile saglik kazanildi (+10 Saglik).\n");
                    saglik += 10;
                    if (saglik > 100) saglik = 100;
                }
                
                oksijen -= 5; 
                if (oksijen < 0) oksijen = 0;
                
                printf("------------------\n");
                printf("Mevcut Saglik  : %d\n", saglik);
                printf("Mevcut Oksijen : %d\n", oksijen);
                printf("Mevcut Enerji  : %d\n", enerji);
                printf("------------------\n");
                
                turgecerli = 1;
                break;
                
            case 'k':
            case 'K': {
                printf("\n!!! KUM FIRTINASI BASLADI !!!\n");
                printf("Firtina suresi: %d tur\n", firtinasuresi);
                
                int kayipsaglik = 0;
                int kayipoksijen = 0;
                int hasaralinan_tur = 0;
                int t_sayac;
                
				for (t_sayac = 1; t_sayac <= firtinasuresi; t_sayac++) {
                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Firtina sirasinda yasam destek sistemleri iflas etti! Firtina kesildi.\n");
                        break;
                    }
                    
                    printf("\n--- Firtina Turu %d/%d ---\n", t_sayac, firtinasuresi);
                    int hasarkatsayisi = (t_sayac % 2 == 0) ? 2 : 1;
                    if (hasarkatsayisi == 2) {
                        printf("[!] Ruzgar siddetlendi! Hasarlar 2 katina cikiyor!\n");
                    }
                    
                    int olay = rand() % 4;
                    if (olay == 0) {
                        printf("Firtinadan hasar almadiniz.\n");
                    }
                    else if (olay == 1) {
                        int alinan_hasar = 10 * hasarkatsayisi;
                        saglik -= alinan_hasar;
                        kayipsaglik += alinan_hasar;
                        hasaralinan_tur++;
                        if (saglik < 0) saglik = 0;
                        printf("Enkaz parcalari carpti! -%d Saglik (Kalan Saglik: %d)\n", alinan_hasar, saglik);
                    }
                    else if (olay == 2) {
                        if (kilitmuhurlu == 1) {
                            printf("Hava kilidi muhurlu oldugu icin oksijen sizintisi engellendi!\n");
                            continue;
                        }
                        int sizinti = 8 * hasarkatsayisi;
                        oksijen -= sizinti;
                        kayipoksijen += sizinti;
                        hasaralinan_tur++;
                        if (oksijen < 0) oksijen = 0;
                        printf("Oksijen sizintisi meydana geldi! -%d Oksijen (Kalan Oksijen: %d)\n", sizinti, oksijen);
                    }
                    else if (olay == 3) {
                        int m_hasar = 15 * hasarkatsayisi;
                        modulhasari += m_hasar;
                        hasaralinan_tur++;
                        if (modulhasari > 100) modulhasari = 100;
                        printf("Firtina modula zarar verdi! +%d Modul Hasari (Guncel Hasar: %d)\n", m_hasar, modulhasari);
                    }
                }
                
                printf("\n-------------------------------------\n");
                printf("          FIRTINA OZETI              \n");
                printf("-------------------------------------\n");
                printf("Hasar Alinan Tur Sayisi : %d\n", hasaralinan_tur);
                printf("Toplam Kaybedilen Saglik: %d\n", kayipsaglik);
                printf("Toplam Kaybedilen Oksijen: %d\n", kayipoksijen);
                printf("-------------------------------------\n");
                
                turgecerli = 1;
                break;
            }
                
            case 'h':
            case 'H': { 
                char dogruSifre = 'A' + (gun % 26); 
                char tahmin;
                int deneme = 0;
                
                printf("Hava kilidi sifre ipucu: Sifre, alfabede 'A' harfinden %d ilerideki harftir.\n", gun % 26);
                
                do {
                    if (enerji < 5) {
                        printf("Enerji yetersiz! (Mevcut enerji: %d) Hava kilidi muhurlenemedi.\n", enerji);
                        modulhasari += 20;
                        if (modulhasari > 100) modulhasari = 100;
                        break;
                    }
                    
                    printf("Sifre tahmininizi giriniz (%d/3): ", deneme + 1);
                    tahmin = getchar();
                    while (getchar() != '\n');
                    
                    if (tahmin >= 'a' && tahmin <= 'z') {
                        tahmin = tahmin - 32;
                    }
                    
                    if (tahmin == dogruSifre) {
                        printf("Sifre dogru! Hava kilidi muhurlendi.\n");
                        kilitmuhurlu = 1;
                        break;
                    } else {
                        deneme++;
                        enerji -= 5;
                        if (enerji < 0) enerji = 0;
                        printf("Yanlis sifre! (-5 Enerji)\n");
                        
                        if (tahmin < dogruSifre) {
                            printf("Ipucu: Alfabede daha ILERI bir harf deneyin!\n");
                        } else {
                            printf("Ipucu: Alfabede daha GERI bir harf deneyin!\n");
                        }
                    }
                } while (tahmin != dogruSifre && deneme < 3);
                
                if (kilitmuhurlu != 1 && deneme == 3) {
                    printf("3 deneme hakkiniz bitti! Hava kilidi muhurlenemedi (+20 Modul Hasari).\n");
                    modulhasari += 20;
                    if (modulhasari > 100) modulhasari = 100;
                }
                
                turgecerli = 1;
                break;
            }
            
            case 'q':
            case 'Q':
                printf("Simulasyondan cikiliyor... Hoscakalin!\n");
                break;
                
            default:
                printf("Gecerli bir komut giriniz!\n");
                break;
        }
        
        if (komut == 'q' || komut == 'Q') {
            break;
        }
        
        if (turgecerli) {
            if (tur % 3 == 0) {
                printf("\n--- GUN %d TAMAMLANDI ---\n", gun);
                oksijen -= 8;
                if (oksijen < 0) oksijen = 0;
                printf("Oksijen 8 azaldi. Kalan Oksijen: %d\n", oksijen);
                
                if (modulhasari > 70) {
                    saglik -= 5;
                    if (saglik < 0) saglik = 0;
                    printf("Yuksek modul hasari nedeniyle 5 saglik kaybedildi! Kalan Saglik: %d\n", saglik);
                }
                printf("---------------------------\n");
            }
            tur++; 
        }
    }

    puan = (gun * 100) + saglik + oksijen - modulhasari;
    printf("\n=====================================\n");
    printf("           OYUN SONU RAPORU          \n");
    printf("=====================================\n");
    if (saglik <= 0 || oksijen <= 0) {
        printf("DURUM: SIMULASYON BASARISIZ (Yasam destek sistemleri coktu)\n");
    } else if (gun > 15) {
        printf("DURUM: TEBRIKLER! 15 Gun Hayatta Kaldiniz, Kurtarma Ekibi Ulasti!\n");
    } else {
        printf("DURUM: OYUNDAN CIKILDI\n");
    }
    printf("Hayatta Kalinan Gun : %d\n", gun);
    printf("Toplam Tur          : %d\n", tur);
    printf("Son Saglik          : %d\n", saglik);
    printf("Son Oksijen         : %d\n", oksijen);
    printf("Son Su              : %d\n", su);
    printf("Son Enerji          : %d\n", enerji);
    printf("Modul Hasari        : %d\n", modulhasari);
    printf("-------------------------------------\n");
    printf("KAZANILAN PUAN      : %d\n", puan);
    printf("=====================================\n");

    return 0;
}
