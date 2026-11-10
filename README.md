# Mars Kolonisi Yaşam Destek Simülatörü (C Dili)

Bu proje, C dili kullanılarak geliştirilmiş metin tabanlı ve komut odaklı bir **Mars Kolonisi Yaşam Destek Simülasyonu** uygulamasıdır. Oyuncu, Mars'taki bir araştırma istasyonunda kurtarma ekibi gelene kadar 15 gün boyunca hayatta kalmaya çalışan bir mühendisi yönetir.

---

## Proje Özellikleri

- **Zorluk Seviyeleri:** Kolay, Normal ve Zor olmak üzere 3 farklı başlangıç senaryosu (`switch-case` yapısı ile).
- **Kaynak Yönetimi:** Sağlık, Enerji, Oksijen, Su, Yedek Parça ve Modül Hasarı takibi.
- **Dinamik Zaman Akışı:** Her 3 turda bir 1 gün tamamlanır. Gün sonlarında sistemik oksijen tüketimi ve hasar kontrolü yapılır.
- **Rastgele Olaylar:** `srand(time(NULL))` ve `rand()` fonksiyonları ile keşif ve fırtına mekanizmaları.
- **Skor Sistemi:** Hayatta kalınan gün, son durum parametreleri ve modül hasarına bağlı puan hesaplaması.

---

## Komut Listesi

Uygulama büyük/küçük harf duyarsız (`fall-through` switch yapısı) tek karakterlik komutlarla çalışır:

| Komut | Açıklama |
| :---: | :--- |
| **G** | **Keşif:** Su veya yedek parça bulma şansı. Kaza durumunda sağlık kaybı riski. |
| **O** | **Oksijen Üret:** Su ve enerji tüketerek oksijen deposunu doldurur (`%` mod kontrolü ile). |
| **T** | **Tamir:** Modül hasar seviyesine (hafif, orta, ağır) göre yedek parça harcayarak onarım yapar. |
| **D** | **Durum Raporu:** Tüm hayati değerleri ve kritik sistem uyarılarını görüntüler (Tur harcamaz). |
| **U** | **Uyu / Dinlen:** Enerji ve sağlık yeniler (Düşük oksijende sağlık düşer). |
| **K** | **Kum Fırtınası:** `FOR` döngüsü simülasyonu. Çift turlarda rüzgar şiddetlenir ve hasar 2 katına çıkar. |
| **H** | **Hava Kilidi Şifresi:** `DO-WHILE` döngüsü ile gün sayısından türetilen şifreyi 3 denemede bulma. |
| **Q** | **Çıkış:** Simülasyonu sonlandırır ve skor raporunu basar. |

---

## Teknik Yapı ve Kod Mimarisi

- **Komut Yönetimi (`SWITCH-CASE`):** Komut harflerinde `case 'g': case 'G':` fall-through kullanılarak harf boyutu esnekliği sağlandı. Tanımsız komutlar `default` bloğu ile engellenerek tur kaybı önlendi.
- **Kum Fırtınası Simülasyonu (`FOR` Döngüsü):** Zorluk seviyesine göre belirlenen tur sayısı boyunca `for` döngüsü çalışır. `t_sayac % 2 == 0` ile çift turlar tespit edilip hasarlar 2 katına çıkarılır. Hava kilidi mühürlü ise `continue` ile sızıntı atlanır, sağlık/oksijen biterse `break` ile fırtına kesilir.
- **Sınırlı Denemeli Şifre Mekanizması (`DO-WHILE` Döngüsü):** `do { ... } while (tahmin != dogruSifre && deneme < 3);` yapısı kullanılarak mantıksal `&&` ile deneme hakkı sınırlandı. Şifre `sifre = 'A' + (gun % 26)` formülüyle gün bazlı dinamik türetilir.
- **Aritmetik ve Mantıksal Sınırlandırmalar:** Oksijen üretiminde su artık kontrolü `girilensu % 2` ile sağlandı. Tüm parametreler (Sağlık, Enerji, Oksijen, Hasar) her işlem sonrasında 0-100 aralığında tutuldu.

---

## Puan Formülü

Proje sonunda kazanılan puan aşağıdaki matematiksel formül ile hesaplanır:

$$\text{Puan} = (\text{Gün} \times 100) + \text{Sağlık} + \text{Oksijen} - \text{Modül Hasarı}$$

- **Gün Katsayısı (100):** Hayatta kalınan her bir günün önemini ve ana hedefi ödüllendirmek için yüksek katsayı seçilmiştir.
- **Modül Hasarı (-):** İstasyonun fiziksel durumu ne kadar kötü bırakılırsa final skoru o kadar olumsuz etkiler.

---

## Kurulum ve Çalıştırma

1. Projeyi klonlayın:
   ```bash
   git clone [https://github.com/KULLANICI_ADI/REPO_ADI.git](https://github.com/KULLANICI_ADI/REPO_ADI.git)
