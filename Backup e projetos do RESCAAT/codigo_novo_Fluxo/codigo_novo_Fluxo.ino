#include <LiquidCrystal.h>

// Define os pinos do LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = 18;  // Pino digital conectado ao fio amarelo do sensor de fluxo
volatile int pulseCount = 0;
unsigned long oldTime = 0;

float calibrationFactor = 4.5;  // Fator de calibração para o sensor YF-S201
float flowRate = 0.0;
float totalLitres = 0.0;

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  lcd.begin(16, 2);
  lcd.print("Fluxo de Agua");
  delay(2000);
  lcd.clear();

  oldTime = millis();
}

void loop() {
  if ((millis() - oldTime) > 1000) {  // Calcula o fluxo a cada segundo
    detachInterrupt(digitalPinToInterrupt(sensorPin));

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    totalLitres += (flowRate / 60);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fluxo: ");
    lcd.print(flowRate);
    lcd.print(" L/min");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalLitres);
    lcd.print(" L");

    pulseCount = 0;
    oldTime = millis();

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
