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

Plik → Preferencje

W polu „Dodatkowe adresy URL do menedżera płytek” należy dodać:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Następnie należy przejść do:

Narzędzia → Płytka → Menedżer płytek

i zainstalować pakiet ESP32.

## Instalacja bibliotek

Projekt wykorzystuje następujące biblioteki:

- WiFi
- WebServer
- ESP32Servo

Biblioteki można zainstalować z poziomu Menedżera bibliotek Arduino IDE.

## Konfiguracja sieci WiFi

Przed wgraniem programu należy uzupełnić dane sieci WiFi.

W pliku programu należy zmienić:

```cpp
const char* ssid = "NAZWA_WIFI";
const char* password = "HASLO_WIFI";
