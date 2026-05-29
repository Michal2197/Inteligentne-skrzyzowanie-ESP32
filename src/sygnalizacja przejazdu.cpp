// Sygnalizacja świetlna przejazdu kolejowego

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


