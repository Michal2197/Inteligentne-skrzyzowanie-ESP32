// Obsługa serwera WWW

WebServer server(80);

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
  html += "<h1>ESP32 Przejazd Kolejowy</h1>";

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
