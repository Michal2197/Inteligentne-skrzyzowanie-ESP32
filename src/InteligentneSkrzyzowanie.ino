#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Nazwa internetu";
const char* password = "Hasło";

WebServer server(80);

// Droga główna
const int drogaGlownaCzerwone = 2;
const int drogaGlownaZolte = 15;
const int drogaGlownaZielone = 18;

// Droga boczna
const int drogaBocznaCzerwone = 19;
const int drogaBocznaZolte = 21;
const int drogaBocznaZielone = 22;

// Światla przejazdu
const int przejazdLewy1 = 23;
const int przejazdLewy2 = 25;
const int przejazdPrawy1 = 26;
const int przejazdPrawy2 = 27;

// Rogatki  
Servo rogatkaLewa;
Servo rogatkaPrawa; 

const int pinRogatkaLewa = 32;
const int pinRogatkaPrawa = 33;

const int rogatkaOtwarta = 90;
const int rogatkaZamknieta = 0;

// Czujnik pociągu
const int trig1 = 4;
const int echo1 = 5;

const int trig2 = 13;
const int echo2 = 34;


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

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println("Laczenie z WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Polaczono z WiFi");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", stronaGlowna);

  server.on("/nadjezdza", []() {
    if (!przejazdAktywny) {
      rozpocznijPrzejazd(1);
    }

    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/przejechal", []() {
    if (przejazdAktywny) {
      zakonczPrzejazd();
    }

    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();

  pinMode(drogaGlownaCzerwone, OUTPUT);
  pinMode(drogaGlownaZolte, OUTPUT);
  pinMode(drogaGlownaZielone, OUTPUT);

  pinMode(drogaBocznaCzerwone, OUTPUT);
  pinMode(drogaBocznaZolte, OUTPUT);
  pinMode(drogaBocznaZielone, OUTPUT);

  pinMode(przejazdLewy1, OUTPUT);
  pinMode(przejazdLewy2, OUTPUT);
  pinMode(przejazdPrawy1, OUTPUT);
  pinMode(przejazdPrawy2, OUTPUT);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  rogatkaLewa.attach(pinRogatkaLewa);
  rogatkaPrawa.attach(pinRogatkaPrawa);

  podniesRogatki();
  wylaczSwiatlaPrzejazdu();
  ustawEtapSwiatel();
}

void loop() {
  server.handleClient();

  aktualizujPomiary();

  if (!przejazdAktywny) {
    if (odleglosc1 <= 20) {
      rozpocznijPrzejazd(1);
    } else if (odleglosc2 <= 20) {
      rozpocznijPrzejazd(2);
    } else {
      aktualizujSwiatlaDrogowe();
    }
  } else {
    ustawSwiatla(HIGH, LOW, LOW, HIGH, LOW, LOW);
    aktualizujMiganiePrzejazdu();
    sprawdzZakonczeniePrzejazdu();
  }
}

void stronaGlowna() {
  String html = "";

  html += "<html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Przejazd kolejowy</title>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#eaeaea;}";
  html += ".box{background:white;padding:20px;margin:30px auto;width:340px;border-radius:15px;}";
  html += "button{padding:15px 25px;font-size:18px;border:none;border-radius:10px;margin:8px;color:white;}";
  html += ".start{background:#e53935;}";
  html += ".stop{background:#43a047;}";
  html += "</style>";
  html += "</head><body>";

  html += "<div class='box'>";
  html += "<h1>Przejazd Kolejowy</h1>";

  html += "<p><b>Status:</b> ";
  html += przejazdAktywny ? "Pociag na przejezdzie" : "Normalny ruch drogowy";
  html += "</p>";

  html += "<p>Czujnik 1: ";
  html += String(odleglosc1);
  html += " cm</p>";

  html += "<p>Czujnik 2: ";
  html += String(odleglosc2);
  html += " cm</p>";

  html += "<a href='/nadjezdza'><button class='start'>Nadjezdza pociag</button></a>";
  html += "<br>";
  html += "<a href='/przejechal'><button class='stop'>Pociag przejechal</button></a>";

  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void rozpocznijPrzejazd(int kierunek) {
  przejazdAktywny = true;
  kierunekPociagu = kierunek;
  czujnikWyjazdowyWykrylPociag = false;

  Serial.println("Wykryto pociag.");

  naturalnieZatrzymajRuch();
  czekajZMiganiem(1500);
  opuscRogatki();
}

void naturalnieZatrzymajRuch() {
  if (etapSwiatel == 0) {
    ustawSwiatla(LOW, HIGH, LOW, HIGH, LOW, LOW);
    delay(2000);
  } else if (etapSwiatel == 2) {
    ustawSwiatla(HIGH, LOW, LOW, LOW, HIGH, LOW);
    delay(2000);
  }

  ustawSwiatla(HIGH, LOW, LOW, HIGH, LOW, LOW);
  delay(1000);
}

void sprawdzZakonczeniePrzejazdu() {

  if (kierunekPociagu == 1) {

    // pociąg dojechał do czujnika 2
    if (odleglosc2 <= 20) {
      czujnikWyjazdowyWykrylPociag = true;
    }

    // pociąg odjechał od czujnika 2
    if (czujnikWyjazdowyWykrylPociag && odleglosc2 > 20) {
      zakonczPrzejazd();
    }
  }

  if (kierunekPociagu == 2) {

    // pociąg dojechał do czujnika 1
    if (odleglosc1 <= 20) {
      czujnikWyjazdowyWykrylPociag = true;
    }

    // pociąg odjechał od czujnika 1
    if (czujnikWyjazdowyWykrylPociag && odleglosc1 > 20) {
      zakonczPrzejazd();
    }
  }
}

void zakonczPrzejazd() {
  Serial.println("Koniec przejazdu.");

  podniesRogatki();
  wylaczSwiatlaPrzejazdu();

  przejazdAktywny = false;
  kierunekPociagu = 0;
  czujnikWyjazdowyWykrylPociag = false;

  etapSwiatel = 0;
  ostatniaZmianaSwiatel = millis();

  ustawEtapSwiatel();
}

void aktualizujPomiary() {
  if (millis() - ostatniPomiar >= 100) {
    ostatniPomiar = millis();

    odleglosc1 = zmierzOdleglosc(trig1, echo1);
    delay(30);
    odleglosc2 = zmierzOdleglosc(trig2, echo2);
  }
}

void aktualizujSwiatlaDrogowe() {
  unsigned long czasEtapu = 0;

  switch (etapSwiatel) {
    case 0: czasEtapu = 5000; break;
    case 1: czasEtapu = 2000; break;
    case 2: czasEtapu = 5000; break;
    case 3: czasEtapu = 2000; break;
  }

  if (millis() - ostatniaZmianaSwiatel >= czasEtapu) {
    ostatniaZmianaSwiatel = millis();

    etapSwiatel++;

    if (etapSwiatel > 3) {
      etapSwiatel = 0;
    }

    ustawEtapSwiatel();
  }
}

void ustawEtapSwiatel() {
  switch (etapSwiatel) {
    case 0:
      ustawSwiatla(LOW, LOW, HIGH, HIGH, LOW, LOW);
      break;

    case 1:
      ustawSwiatla(LOW, HIGH, LOW, HIGH, HIGH, LOW);
      break;

    case 2:
      ustawSwiatla(HIGH, LOW, LOW, LOW, LOW, HIGH);
      break;

    case 3:
      ustawSwiatla(HIGH, HIGH, LOW, LOW, HIGH, LOW);
      break;
  }
}

void ustawSwiatla(
  int glowneCzerwone,
  int glowneZolte,
  int glowneZielone,
  int boczneCzerwone,
  int boczneZolte,
  int boczneZielone
) {
  digitalWrite(drogaGlownaCzerwone, glowneCzerwone);
  digitalWrite(drogaGlownaZolte, glowneZolte);
  digitalWrite(drogaGlownaZielone, glowneZielone);

  digitalWrite(drogaBocznaCzerwone, boczneCzerwone);
  digitalWrite(drogaBocznaZolte, boczneZolte);
  digitalWrite(drogaBocznaZielone, boczneZielone);
}

void aktualizujMiganiePrzejazdu() {
  if (millis() - ostatnieMiganie >= 500) {
    ostatnieMiganie = millis();
    stanMigania = !stanMigania;

    digitalWrite(przejazdLewy1, stanMigania);
    digitalWrite(przejazdLewy2, !stanMigania);

    digitalWrite(przejazdPrawy1, stanMigania);
    digitalWrite(przejazdPrawy2, !stanMigania);
  }
}

void czekajZMiganiem(unsigned long czas) {
  unsigned long start = millis();

  while (millis() - start < czas) {
    aktualizujMiganiePrzejazdu();
  }
}

void wylaczSwiatlaPrzejazdu() {
  digitalWrite(przejazdLewy1, LOW);
  digitalWrite(przejazdLewy2, LOW);
  digitalWrite(przejazdPrawy1, LOW);
  digitalWrite(przejazdPrawy2, LOW);
}

void opuscRogatki() {
  for (int pozycja = 0; pozycja <= 90; pozycja++) {
    rogatkaLewa.write(90 - pozycja);
    rogatkaPrawa.write(pozycja);
    aktualizujMiganiePrzejazdu();
    delay(15);
  }
}

void podniesRogatki() {
  for (int pozycja = 90; pozycja >= 0; pozycja--) {
    rogatkaLewa.write(90 - pozycja);
    rogatkaPrawa.write(pozycja);
    aktualizujMiganiePrzejazdu();
    delay(15);
  }
}

float zmierzOdleglosc(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long czas = pulseIn(echoPin, HIGH, 15000);

  if (czas == 0) {
    return 999;
  }

  return czas * 0.034 / 2;
}

//pokazOdleglosci();

/*void pokazOdleglosci() {
  if (millis() - ostatniSerial >= 300) {
    ostatniSerial = millis();

    Serial.print("Czujnik 1: ");
    Serial.print(odleglosc1);

    Serial.print(" cm | Czujnik 2: ");
    Serial.print(odleglosc2);

    Serial.println(" cm");
  }
}*/
