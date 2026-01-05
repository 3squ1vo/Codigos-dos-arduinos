#include <Wire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 53

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int tempLimit = 35;
int limiarSeco = 25.5;
int umidPin = A0;
int buzina = 6;

const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("   SmartCrop");
  lcd.setCursor(0, 1);
  lcd.print("Futuro no Campo");
  delay(3000);
  lcd.clear();

  for(int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];

  sensors.requestTemperatures();
  readings[readIndex] = sensores.getTempCByIndex(0);

  total = total + readings[readIndex];

  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  if (average > tempLimit) {
    lcd.setCursor(6, 0);
    lcd.print("Frio Demais");
    delay(2000);
    avisoSonoro(523, 1, 110);
    delay(110);
    avisoSonoro(659, 1, 110);
    delay(110);
    avisoSonoro(784, 1, 110);
    delay(110);
  }
  else {
    lcd.setCursor(6, 0);
    lcd.print("Quente Demais");
    delay(2000);
    avisoSonoro(587, 1, 110);
    delay(110);
    avisoSonoro(659, 1, 110);
    delay(110);
    avisoSonoro(1047, 1, 110);
    delay(110);
  }

  for(int i = 0; i < 5; i++) {
    int umidValor = analogRead(umidPin);
    umidValor = map(umidValor, 1023, 0, 0, 100);

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");

    if (umidValor < limiarSeco) {
      lcd.setCursor(6, 1);
      lcd.print("Molhado D+");
      delay(2000);
      avisoSonoro(523, 1, 110);
      delay(110);
      avisoSonoro(659, 1, 110);
      delay(110);
      avisoSonoro(784, 1, 110);
      delay(110);
    }
    else {
      lcd.setCursor(6, 1);
      lcd.print("Seco Demais");
      delay(2000);
      avisoSonoro(587, 1, 110);
      delay(110);
      avisoSonoro(659, 1, 110);
      delay(110);
      avisoSonoro(1047, 1, 110);
      delay(110);
    }
  }

  void avisoSonoro(int frequencia, int quantidade, int tempo) {
    for(int i = 0; i < quantidade; i++) {
      tone(buzina, frequencia);
      delay(tempo);
      noTone(buzina);
      delay(tempo);
      delay(500);
    }
  }
}
