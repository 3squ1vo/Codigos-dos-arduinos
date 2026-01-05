void setup() {
  // Comunicação com o PC
  Serial.begin(9600); 

  // Comunicação com o ESP8266
  Serial1.begin(9600); // TX1 = 18, RX1 = 19

  Serial.println("Iniciando teste com ESP8266...");
  delay(2000);

  // Envia comando AT
  Serial1.println("AT");
}

void loop() {
  // Lê do ESP8266 e envia para o PC
  if (Serial1.available()) {
    char c = Serial1.read();
    Serial.write(c);
  }

  // Lê do PC e envia para o ESP8266
  if (Serial.available()) {
    char c = Serial.read();
    Serial1.write(c);
  }
}
