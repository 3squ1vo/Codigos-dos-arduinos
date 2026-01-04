#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPressaoPin0 = A0;
const int sensorPressaoPin1 = A1;
const int sensorPressaoPin2 = A2;
const int sensorPressaoPin3 = A3;
const int sensorPressaoPin4 = A4;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float sensorValue0 = analogRead(sensorPressaoPin0);
  float sensorValue1 = analogRead(sensorPressaoPin1);
  float sensorValue2 = analogRead(sensorPressaoPin2);
  float sensorValue3 = analogRead(sensorPressaoPin3);
  float sensorValue4 = analogRead(sensorPressaoPin4);
  float pressure0 = map(sensorValue0, 0, 1023, 0, 500);
  float pressure1 = map(sensorValue1, 0, 1023, 0, 500);
  float pressure2 = map(sensorValue2, 0, 1023, 0, 500);
  float pressure3 = map(sensorValue3, 0, 1023, 0, 500);
  float pressure4 = map(sensorValue4, 0, 1023, 0, 500);
  
  lcd.setCursor(0, 0);
  lcd.print("P1 ");
  lcd.print(pressure0);
  lcd.print(" kPa ");

  lcd.setCursor(0, 1);
  lcd.print("P2 ");
  lcd.print(pressure1);
  lcd.print(" kPa ");

  lcd.setCursor(0, 1);
  lcd.print("P3 ");
  lcd.print(pressure2);
  lcd.print(" kPa ");

  lcd.setCursor(0, 1);
  lcd.print("P4 ");
  lcd.print(pressure3);
  lcd.print(" kPa ");

  lcd.setCursor(0, 1);
  lcd.print("P5 ");
  lcd.print(pressure4);
  lcd.print(" kPa ");
  
  delay(3000);
}
