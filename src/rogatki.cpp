// Obsługa rogatek

void opuscRogatki() {
  for (int pozycja = rogatkaOtwarta; pozycja <= rogatkaZamknieta; pozycja++) {
    rogatkaLewa.write(pozycja);
    rogatkaPrawa.write(90 - pozycja);
    aktualizujMiganiePrzejazdu();
    delay(15);
  }
}

void podniesRogatki() {
  for (int pozycja = rogatkaZamknieta; pozycja >= rogatkaOtwarta; pozycja--) {
    rogatkaLewa.write(pozycja);
    rogatkaPrawa.write(90 - pozycja);
    aktualizujMiganiePrzejazdu();
    delay(15);
  }
}

