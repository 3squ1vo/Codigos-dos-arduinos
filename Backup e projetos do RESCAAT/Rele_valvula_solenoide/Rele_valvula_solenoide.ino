#include <LiquidCrystal.h>
#define sensorPin A1
int relay = 4;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
}

void loop() {
  leitura = analogRead(sensorPin);
  Serial.println(leitura);
  if (leitura <= 500) {
    Serial.println("Nível d'água: Baixo");
    digitalWrite(relay, HIGH);
  }
  else (leitura => 600) {
    Serial.print("Nível d'água: Alto");
    digitalWrite(relay, LOW);
  }
  delay(1000);
}