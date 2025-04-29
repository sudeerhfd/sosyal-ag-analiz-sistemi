# sosyal-ag-analiz-sistemi

Bu proje, belirli bir kullanıcı ve arkadaşlık ilişkilerini yönetmek için tasarlanmış bir C programıdır. Program, kullanıcıları ve arkadaşlıklarını bir kırmızı-siyah ağaç veri yapısı üzerinde saklar ve çeşitli analizler yapar.

## Özellikler

- Kullanıcı oluşturma ve saklama
- Arkadaşlık ilişkilerini yönetme
- Kullanıcı bilgilerini listeleme
- Belirli mesafedeki arkadaşları bulma
- Ortak arkadaşları listeleme
- Dosyadan veri yükleme
- Belleği temizleme

## Dosya Formatı

Program, kullanıcı ve arkadaş bilgilerini bir dosyadan okuyarak çalışır. Dosya iki ana bölümden oluşur:

1. **USERS**: Kullanıcıların ID'lerini içerir. Her kullanıcı ID'si bir satıra yazılmalıdır.
2. **FRIENDS**: Arkadaşlık ilişkilerini içerir. Her satırda iki kullanıcı ID'si bulunur ve bu ID'ler bir arkadaşlık ilişkisini temsil eder.

### Örnek Dosya Formatı
```
USERS
101
102
103
104
105

FRIENDS
101 102
101 103
102 104
103 105
```

## Fonksiyonlar

### 1. Kullanıcı Oluşturma ve Saklama
- Kullanıcılar kırmızı-siyah ağaç yapısında saklanır.
- Yeni kullanıcı eklemek için `ks_ekle` fonksiyonu kullanılır.

### 2. Arkadaşlık Yönetimi
- İki kullanıcı arasında arkadaşlık ilişkisi oluşturmak için `arkadas_ekle` fonksiyonu kullanılır.

### 3. Kullanıcı Bilgilerini Listeleme
- `kullanicilari_listele` fonksiyonu, tüm kullanıcıların ve arkadaşlarının bir listesini ekrana yazdırır.

### 4. Belirli Mesafedeki Arkadaşları Bulma
- `belirli_mesafedeki_arkadaslar` fonksiyonu, bir kullanıcının belirli bir mesafedeki arkadaşlarını bulur ve ekrana yazdırır.
- Mesafe, Breadth-First Search (BFS) yöntemiyle hesaplanır.

### 5. Ortak Arkadaşları Bulma
- `ortak_arkadaslar` fonksiyonu, iki kullanıcı arasındaki ortak arkadaşları listelemek için kullanılır.

### 6. Dosyadan Veri Okuma
- `dosyadan_oku` fonksiyonu, kullanıcı ve arkadaşlık bilgilerini dosyadan okuyarak ağaç yapısına ekler.

### 7. Belleği Temizleme
- `temizle` fonksiyonu, program sonunda belleği temizlemek için kullanılır.

## Kurulum ve Kullanım

1. **Kaynak Kodunu Derleme**  
   Programı çalıştırmak için bir C derleyicisine ihtiyacınız var. Aşağıdaki komutu kullanarak derleyebilirsiniz:
   ```bash
   gcc program.c -o program
   ```

2. **Veri Dosyası Hazırlama**  
   Kullanıcı ve arkadaşlık bilgilerinin yer aldığı bir dosya oluşturun. Örnek dosya formatına uygun bir `.txt` dosyası hazırlayın.

3. **Programı Çalıştırma**  
   Derlenen programı çalıştırın ve veri dosyasının yolunu belirtin:
   ```bash
   ./program
   ```

4. **Sonuçları Görüntüleme**  
   Program, kullanıcı bilgilerini ve analiz sonuçlarını terminalde görüntüler.

## Örnek Çıktı
```
Kullanıcı Bilgileri:
--------------------
Kullanici 101: 102, 103
Kullanici 102: 101, 104
Kullanici 103: 101, 105
Kullanici 104: 102
Kullanici 105: 103

101 kullanıcısının 2 uzaklıktaki arkadaşları: 104 105

101 ve 104 kullanıcılarının ortak arkadaşları: 102
```

## Geliştirici Notları

- Programda, kullanıcılar ve arkadaşlıklar kırmızı-siyah ağaç veri yapısında saklanır. Ancak, bu yapı tam bir kırmızı-siyah ağaç uygulaması değildir ve basit bir ikili arama ağacı gibi davranır.
- Programın bellek yönetimi, manuel olarak yapılmıştır. `malloc` ile ayrılan bellek, `temizle` fonksiyonu ile serbest bırakılır.
- Veri dosyasının formatı, programın doğru çalışması için önemlidir. Hatalı bir format, programın beklenmedik şekilde çalışmasına neden olabilir.

## Lisans

Bu proje açık kaynak kodludur ve MIT lisansı altında sunulmaktadır.
