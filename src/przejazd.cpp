// Logika przejazdu kolejowego

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


/////


void sprawdzZakonczeniePrzejazdu() {
  if (kierunekPociagu == 1) {
    if (odleglosc2 <= 20) {
      czujnikWyjazdowyWykrylPociag = true;
    }

    if (czujnikWyjazdowyWykrylPociag && odleglosc2 > 20) {
      zakonczPrzejazd();
    }
  }

  if (kierunekPociagu == 2) {
    if (odleglosc1 <= 20) {
      czujnikWyjazdowyWykrylPociag = true;
    }

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
