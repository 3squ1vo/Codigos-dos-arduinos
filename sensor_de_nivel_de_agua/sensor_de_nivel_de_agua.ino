#include <LiquidCrystal.h>
#define vermelho 10
#define amarelo 11
#define verde 12
#define sensorPin A1
int leitura;
void setup() {
  Serial.begin(9600);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  digitalWrite(vermelho, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
  Serial.println("----- MONITORAMENTO DO NÍVEL DE ÁGUA -----");
  delay(1000);
}

void loop() {
  Serial.print("Leitura do Sensor de Nível: ");
  leitura = analogRead(sensorPin);
  Serial.println(leitura);
  if (leitura <= 500) {
    Serial.println("Nível de água: Baixo");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  }
  else if (leitura > 600 && leitura <= 660) {
    Serial.println("Nível de água: Médio");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
  }
  else if (leitura > 641) {
    Serial.println("Nível de água: Alto");
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, HIGH);
  }
  delay(500);
}