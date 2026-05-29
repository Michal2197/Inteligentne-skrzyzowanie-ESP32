// Konfiguracja projektu


// Dane WiFi

const char* ssid = "NAZWA_WIFI";
const char* password = "HASLO_WIFI";

// Droga główna

const int drogaGlownaCzerwone = 2;
const int drogaGlownaZolte = 15;
const int drogaGlownaZielone = 18;

// Droga boczna

const int drogaBocznaCzerwone = 19;
const int drogaBocznaZolte = 21;
const int drogaBocznaZielone = 22;

// Sygnalizacja przejazdu kolejowego

const int przejazdLewy1 = 23;
const int przejazdLewy2 = 25;
const int przejazdPrawy1 = 26;
const int przejazdPrawy2 = 27;

// Rogatki

Servo rogatkaLewa;
Servo rogatkaPrawa;

const int pinRogatkaLewa = 32;
const int pinRogatkaPrawa = 33;

const int rogatkaOtwarta = 0;
const int rogatkaZamknieta = 90;

// Czujniki

const int trig1 = 4;
const int echo1 = 5;

const int trig2 = 13;
const int echo2 = 34;

// Zmienne

int etapSwiatel = 0;
unsigned long ostatniaZmianaSwiatel = 0;

bool przejazdAktywny = false;
int kierunekPociagu = 0;
bool czujnikWyjazdowyWykrylPociag = false;

bool stanMigania = false;
unsigned long ostatnieMiganie = 0;

unsigned long ostatniPomiar = 0;
unsigned long ostatniSerial = 0;

float odleglosc1 = 999;
float odleglosc2 = 999;




