// Obsługa świateł drogowych

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
