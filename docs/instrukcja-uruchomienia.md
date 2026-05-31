# Instrukcja uruchomienia

## Wymagania

Do uruchomienia projektu wymagane są:

- mikrokontroler ESP32,
- komputer z systemem Windows, Linux lub macOS,
- przewód USB do programowania ESP32,
- zainstalowane środowisko Arduino IDE,
- połączenie z siecią WiFi.

## Instalacja Arduino IDE

Należy pobrać i zainstalować środowisko Arduino IDE ze strony:

https://www.arduino.cc/en/software

Po zakończeniu instalacji należy dodać obsługę mikrokontrolerów ESP32.

## Instalacja obsługi ESP32

W Arduino IDE należy otworzyć:

File → Preferences...

W polu „Dodatkowe adresy URL do menedżera płytek” należy dodać:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Następnie przejść do:

**Tools → Board → Boards Manager**

Wyszukać:

```text
esp32
```

## Instalacja wymaganych bibliotek

W Arduino IDE należy otworzyć:

**Sketch → Include Library → Manage Libraries**

Następnie zainstalować następujące biblioteki:

### ESP32Servo

Wyszukać:

```text
ESP32Servo
```

i zainstalować bibliotekę autorstwa:

```text
Kevin Harrington, John K. Bennett
```

Biblioteki `WiFi.h` oraz `WebServer.h` są dostarczane wraz z pakietem ESP32 i nie wymagają dodatkowej instalacji.

---

## Otwarcie projektu

1. Uruchomić Arduino IDE.
2. Wybrać:

   **File → Open**

3. Otworzyć plik:

```text
InteligentneSkrzyzowanie.ino
```

znajdujący się w katalogu projektu.

---

## Konfiguracja sieci Wi-Fi

Przed wgraniem programu należy uzupełnić dane sieci bezprzewodowej.

W pliku głównym projektu należy odnaleźć fragment:

```cpp
const char* ssid = "Nazwa internetu";
const char* password = "Hasło";
```

i zastąpić go własnymi danymi:

```cpp
const char* ssid = "MojaSiecWiFi";
const char* password = "MojeHaslo";
```

---

## Wybór płytki i portu

Podłączyć ESP32 do komputera za pomocą przewodu USB.

Następnie w Arduino IDE ustawić:

### Płytka

**Tools → Board → ESP32 Arduino → ESP32 Dev Module**

### Port

**Tools → Port**

i wybrać port COM przypisany do płytki ESP32.

Przykład:

```text
COM5
```

---

## Kompilacja programu

W celu sprawdzenia poprawności kodu należy kliknąć przycisk:

```text
Verify
```

lub wybrać:

```text
Sketch → Verify/Compile
```

Po poprawnej kompilacji nie powinny pojawić się żadne błędy.

---

## Wgranie programu do ESP32

Aby wgrać program do mikrokontrolera należy kliknąć:

```text
Upload
```

lub wybrać:

```text
Sketch → Upload
```

Po zakończeniu procesu program zostanie uruchomiony automatycznie.

---

## Odczyt adresu IP

Po uruchomieniu programu należy otworzyć monitor portu szeregowego:

**Tools → Serial Monitor**

oraz ustawić prędkość:

```text
115200 baud
```

W oknie monitora zostanie wyświetlony adres IP urządzenia.

Przykład:

```text
Polaczono z WiFi
Adres IP: 192.168.1.105
```

---

## Uruchomienie interfejsu WWW

Po odczytaniu adresu IP należy:

1. Otworzyć przeglądarkę internetową.
2. Wpisać adres IP wyświetlony przez ESP32.

Przykład:

```text
http://192.168.1.105
```

Po załadowaniu strony zostanie wyświetlony panel sterowania przejazdem kolejowym.

---

## Funkcje interfejsu

Interfejs WWW umożliwia:

- podgląd aktualnego stanu przejazdu,
- odczyt danych z czujników,
- ręczne zgłoszenie nadjeżdżającego pociągu,
- ręczne zakończenie przejazdu.

---

## Test działania systemu

Po uruchomieniu należy sprawdzić poprawność działania:

### Sygnalizacji drogowej

- zmiana świateł dla drogi głównej,
- zmiana świateł dla drogi bocznej,
- zachowanie odpowiednich czasów przełączania.

### Przejazdu kolejowego

Po wykryciu pociągu przez czujnik:

- uruchamiane są światła ostrzegawcze,
- opuszczane są rogatki,
- ruch drogowy zostaje zatrzymany.

Po opuszczeniu strefy wykrywania przez pociąg:

- rogatki zostają podniesione,
- światła przejazdowe zostają wyłączone,
- przywrócona zostaje normalna praca skrzyżowania.

---

## Struktura projektu

```text
src/
├── InteligentneSkrzyzowanie.ino
├── czujniki.cpp
├── konfiguracja.cpp
├── przejazd.cpp
├── rogatki.cpp
├── serwerWWW.cpp
├── swiatla.cpp
└── sygnalizacja-przejazdu.cpp
```

Opis plików:

| Plik | Opis |
|--------|--------|
| InteligentneSkrzyzowanie.ino | Główny program projektu |
| czujniki.cpp | Obsługa czujników ultradźwiękowych |
| konfiguracja.cpp | Konfiguracja systemu |
| przejazd.cpp | Logika przejazdu kolejowego |
| rogatki.cpp | Sterowanie rogatkami |
| serwerWWW.cpp | Interfejs WWW |
| swiatla.cpp | Sterowanie sygnalizacją drogową |
| sygnalizacja-przejazdu.cpp | Sterowanie światłami przejazdu kolejowego |
