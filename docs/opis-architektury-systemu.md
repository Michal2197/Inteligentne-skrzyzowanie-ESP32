# Opis architektury systemu

## Cel projektu

Celem projektu jest stworzenie modelu inteligentnego skrzyżowania drogowego z przejazdem kolejowym sterowanego za pomocą mikrokontrolera ESP32.

System automatycznie steruje sygnalizacją świetlną dla pojazdów oraz zabezpiecza przejazd kolejowy podczas przejazdu pociągu.

## Główne elementy systemu

Projekt składa się z następujących modułów:

* mikrokontroler ESP32,
* sygnalizacja świetlna drogi głównej,
* sygnalizacja świetlna drogi bocznej,
* sygnalizacja przejazdu kolejowego,
* dwa czujniki ultradźwiękowe HC-SR04,
* dwa serwomechanizmy sterujące rogatkami,
* interfejs WWW umożliwiający sterowanie projektem.

## Zasada działania

Podczas normalnej pracy system steruje sygnalizacją świetlną na skrzyżowaniu zgodnie z zaprogramowanym cyklem.

W momencie wykrycia pociągu przez czujnik ultradźwiękowy system uruchamia procedurę zabezpieczenia przejazdu kolejowego. Najpierw zatrzymywany jest ruch drogowy, następnie włączane są światła ostrzegawcze przejazdu kolejowego i opuszczane są rogatki.

Po przejechaniu pociągu oraz wykryciu opuszczenia przejazdu przez drugi czujnik rogatki zostają podniesione, światła ostrzegawcze wyłączone, a sygnalizacja drogowa wraca do normalnego cyklu pracy.
