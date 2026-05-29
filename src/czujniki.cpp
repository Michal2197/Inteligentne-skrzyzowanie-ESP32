// Obsługa czujników ultradźwiękowych

void aktualizujPomiary() {
  if (millis() - ostatniPomiar >= 100) {
    ostatniPomiar = millis();

    odleglosc1 = zmierzOdleglosc(trig1, echo1);
    delay(30);
    odleglosc2 = zmierzOdleglosc(trig2, echo2);
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



